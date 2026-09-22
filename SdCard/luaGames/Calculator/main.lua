-- ============================================================================
--  calculator.lua
--  A basic calculator for the console, navigated with the D-pad.
--
--  Controls:
--    D-pad   : move the selection cursor around the keypad
--    A       : press the selected key
--    B       : backspace (shortcut, same as the DEL key)
--    START   : clear everything (shortcut, same as the C key)
--
--  Drop this file on your SD card and run it like any other Lua script.
-- ============================================================================

-- ---------------------------------------------------------------------------
-- Theme (purple) — tweak these to restyle the whole app
-- ---------------------------------------------------------------------------
local function rgb565(r, g, b)
  -- Lua 5.1 has no native bitwise operators, so build the 16-bit
  -- RGB565 value with plain arithmetic instead of >>, <<, |.
  local r5 = math.floor(r / 8)   -- 5 bits (0-31)
  local g6 = math.floor(g / 4)   -- 6 bits (0-63)
  local b5 = math.floor(b / 8)   -- 5 bits (0-31)
  return r5 * 2048 + g6 * 32 + b5   -- r5<<11 | g6<<5 | b5
end

local COLOR_BG        = rgb565(16, 10, 26)    -- app background
local COLOR_DISP_BG   = rgb565(28, 16, 44)    -- display panel background
local COLOR_DISP_TXT  = rgb565(235, 220, 255) -- display text
local COLOR_KEY_BG    = rgb565(42, 24, 66)    -- number key background
local COLOR_KEY_ALT   = rgb565(58, 32, 88)    -- C / +- / % / DEL background
local COLOR_KEY_OP    = rgb565(120, 60, 200)  -- operator background
local COLOR_KEY_EQ    = rgb565(160, 80, 235)  -- equals background
local COLOR_TXT       = rgb565(240, 235, 250) -- key label text
local COLOR_CURSOR    = rgb565(200, 130, 255) -- selection border

-- ---------------------------------------------------------------------------
-- Layout (computed from the real screen size, so it adapts automatically)
-- ---------------------------------------------------------------------------
local sw, sh = screenWidth(), screenHeight()
local margin = 6

local dispH = math.floor(sh * 0.22)
local dispX, dispY, dispW = margin, margin, sw - margin * 2

local cols, rows = 4, 5
local gridX = margin
local gridY = dispY + dispH + margin
local gridW = sw - margin * 2
local gridH = sh - gridY - margin
local cellW = math.floor((gridW - (cols - 1) * margin) / cols)
local cellH = math.floor((gridH - (rows - 1) * margin) / rows)

-- key grid: label + type ("digit" | "alt" | "op" | "eq")
local KEYS = {
  { {"C","alt"},   {"+/-","alt"}, {"%","alt"},   {"/","op"} },
  { {"7","digit"}, {"8","digit"}, {"9","digit"}, {"*","op"} },
  { {"4","digit"}, {"5","digit"}, {"6","digit"}, {"-","op"} },
  { {"1","digit"}, {"2","digit"}, {"3","digit"}, {"+","op"} },
  { {"DEL","alt"}, {"0","digit"}, {".","digit"}, {"=","eq"} },
}

local function keyColor(kind)
  if kind == "op" then return COLOR_KEY_OP end
  if kind == "eq" then return COLOR_KEY_EQ end
  if kind == "alt" then return COLOR_KEY_ALT end
  return COLOR_KEY_BG
end

local function cellRect(r, c)
  local x = gridX + (c - 1) * (cellW + margin)
  local y = gridY + (r - 1) * (cellH + margin)
  return x, y, cellW, cellH
end

-- ---------------------------------------------------------------------------
-- Calculator state
-- ---------------------------------------------------------------------------
local display   = "0"
local acc        = nil     -- accumulated value
local pendingOp  = nil      -- "+", "-", "*", "/"
local freshEntry = true     -- next digit starts a new number
local errorState = false

local cursorRow, cursorCol = 2, 1  -- start on "7"

local function formatNum(n)
  if n ~= n then return "Error" end          -- NaN
  if n == math.huge or n == -math.huge then return "Error" end
  if n == math.floor(n) and math.abs(n) < 1e12 then
    return string.format("%d", n)
  end
  local s = string.format("%.8g", n)
  return s
end

local function compute(a, b, op)
  if op == "+" then return a + b end
  if op == "-" then return a - b end
  if op == "*" then return a * b end
  if op == "/" then
    if b == 0 then return 0/0 end
    return a / b
  end
  return b
end

local function clearAll()
  display = "0"
  acc = nil
  pendingOp = nil
  freshEntry = true
  errorState = false
end

local function inputDigit(d)
  if errorState then clearAll() end
  if freshEntry then
    display = d
    freshEntry = false
  elseif display == "0" then
    display = d
  elseif #display < 12 then
    display = display .. d
  end
end

local function inputDot()
  if errorState then clearAll() end
  if freshEntry then
    display = "0."
    freshEntry = false
  elseif not display:find("%.") then
    display = display .. "."
  end
end

local function toggleSign()
  if errorState then return end
  if display:sub(1,1) == "-" then
    display = display:sub(2)
  elseif display ~= "0" then
    display = "-" .. display
  end
end

local function percent()
  if errorState then return end
  local n = tonumber(display) or 0
  display = formatNum(n / 100)
  freshEntry = true
end

local function backspace()
  if errorState then clearAll() return end
  if freshEntry then return end
  if #display <= 1 then
    display = "0"
    freshEntry = true
  else
    display = display:sub(1, -2)
    if display == "-" then display = "0" end
  end
end

local function setOp(op)
  if errorState then return end
  local b = tonumber(display)
  if acc and pendingOp and not freshEntry then
    acc = compute(acc, b, pendingOp)
    display = formatNum(acc)
    if display == "Error" then errorState = true end
  elseif not acc then
    acc = b
  end
  pendingOp = op
  freshEntry = true
end

local function equals()
  if errorState then return end
  if acc and pendingOp then
    local b = tonumber(display)
    local result = compute(acc, b, pendingOp)
    display = formatNum(result)
    if display == "Error" then errorState = true end
    acc = nil
    pendingOp = nil
    freshEntry = true
  end
end

local function pressKey(label)
  if label == "C" then clearAll()
  elseif label == "DEL" then backspace()
  elseif label == "+/-" then toggleSign()
  elseif label == "%" then percent()
  elseif label == "." then inputDot()
  elseif label == "=" then equals()
  elseif label == "+" or label == "-" or label == "*" or label == "/" then setOp(label)
  else inputDigit(label) end
end

-- ---------------------------------------------------------------------------
-- Haptic feedback on keypress
-- ---------------------------------------------------------------------------
local function clickHaptic()
  playVibPattern(0, { {130, 12} })
end

-- ---------------------------------------------------------------------------
-- Drawing
-- ---------------------------------------------------------------------------
local function drawDisplay()
  fillRect(dispX, dispY, dispW, dispH, COLOR_DISP_BG)
  drawRect(dispX, dispY, dispW, dispH, COLOR_KEY_OP)
  local text = errorState and "Error" or display
  showText(text, dispX + dispW - 10, dispY + math.floor(dispH / 2),
           COLOR_DISP_TXT, "FF19", "MR")
end

local function drawKeys()
  for r = 1, rows do
    for c = 1, cols do
      local key = KEYS[r][c]
      local label, kind = key[1], key[2]
      local x, y, w, h = cellRect(r, c)
      fillRect(x, y, w, h, keyColor(kind))
      if r == cursorRow and c == cursorCol then
        drawRect(x, y, w, h, COLOR_CURSOR)
        drawRect(x+1, y+1, w-2, h-2, COLOR_CURSOR)
      end
      showText(label, x + math.floor(w/2), y + math.floor(h/2), COLOR_TXT, "FF18", "MC")
    end
  end
end

local function drawAll()
  clearScreen(COLOR_BG)
  drawDisplay()
  drawKeys()
end

-- initial paint
drawAll()

-- ---------------------------------------------------------------------------
-- Main loop — called once per frame by the firmware
-- ---------------------------------------------------------------------------
function update()
  local dirty = false

  if btnPressed("UP") or btnRepeated("UP") then
    cursorRow = cursorRow - 1
    if cursorRow < 1 then cursorRow = rows end
    dirty = true
  elseif btnPressed("DOWN") or btnRepeated("DOWN") then
    cursorRow = cursorRow + 1
    if cursorRow > rows then cursorRow = 1 end
    dirty = true
  elseif btnPressed("LEFT") or btnRepeated("LEFT") then
    cursorCol = cursorCol - 1
    if cursorCol < 1 then cursorCol = cols end
    dirty = true
  elseif btnPressed("RIGHT") or btnRepeated("RIGHT") then
    cursorCol = cursorCol + 1
    if cursorCol > cols then cursorCol = 1 end
    dirty = true
  end

  if btnPressed("A") then
    local label = KEYS[cursorRow][cursorCol][1]
    pressKey(label)
    clickHaptic()
    dirty = true
  end

  if btnPressed("B") then
    backspace()
    clickHaptic()
    dirty = true
  end

  if btnPressed("START") then
    clearAll()
    clickHaptic()
    dirty = true
  end

  if dirty then
    drawAll()
  end
end