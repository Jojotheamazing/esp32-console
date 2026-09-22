local charX = 0
local charY = 0
local gameName = "Lil town"
local lastMoved = 0
local prevCharX = 0
local prevCharY = 0
local charLoaded = false

local layers = {
["ground"] = {
overlay = false,
map = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,24,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,24,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,24,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,24,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,36,42,37,37,37,37,38,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,24,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,24,1,1,1,1,1,1,1,1,1,1,1,1,1},
},
},
["decor"] = {
overlay = true,
map = {
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,29,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,29,-1,-1,-1,17,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,17,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,29,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
},
},
["collectibles"] = {
overlay = true,
map = {
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,93,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,93,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,93,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,93,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,93,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,93,-1,-1,-1,-1,-1},
},
},
["top"] = {
overlay = false,
map = {
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,48,51,49,49,50,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,60,61,61,63,62,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,44,72,84,73,85,75,46,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,56,-1,-1,-1,-1,-1,58,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,56,-1,-1,-1,-1,-1,58,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,68,81,81,82,-1,80,70,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
},
},
["overlay"] = {
overlay = true,
map = {
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,6,19,20,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,18,19,19,8,-1},
{-1,7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,18,19,32,31,-1},
{-1,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,31,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,7,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,16,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
},
},
}

local hasAxe = false
local coins = 0

local itemTypes = {
coin = {
imagePath = "tile_0093",
onPickup = function()
coins = coins + 1
end
},

axe = {
sprite = "tile_0127",
onPickup = function()
hasAxe = true
end
}
}

local collectibles = {
{x = 2, y = 5, type = "axe"},
{x = 2, y = 2, type = "coin"},
{x = 2, y = 3, type = "coin"}
}



local drawOrder = { "ground", "decor", "top", "overlay" }

function tilePath(num)
  return "/games/" .. gameName .. "/assets/tile_" .. string.format("%04d", num) .. ".bmp"
end

function drawTile(num, gx, gy, transparent)
  if num == -1 then return end
  local x = (gx - 1) * 16
  local y = (gy - 1) * 16
  if transparent then
    drawBmpTransparent(tilePath(num), x, y, 0xF81F)
  else
    drawBmp(tilePath(num), x, y)
  end
end

function redrawTileStack(gx, gy)
  -- redraws all layers at a grid position from scratch
  for _, layerName in ipairs(drawOrder) do
    local layer = layers[layerName]
    local tile = layer.map[gy] and layer.map[gy][gx]
    if tile and tile ~= -1 then
      drawTile(tile, gx, gy, layer.overlay)
    end
  end
end

function drawMap()
  clearScreen(0x0000)
  for _, layerName in ipairs(drawOrder) do
    local layer = layers[layerName]
    for gy = 1, #layer.map do
      for gx = 1, #layer.map[gy] do
        drawTile(layer.map[gy][gx], gx, gy, true)
      end
    end
  end
  for i = 1, #collectibles do
    local c = collectibles[i]
    local def = itemTypes[c.type]

    drawBmpTransparent(
    def.imagePath,
    (c.x - 1) * 16,
    (c.y - 1) * 16
    )
  end
end

function checkExists(gx, gy, layer)
  if not layer or not layer.map then return false end
  if not layer.map[gy] then return false end
  local t = layer.map[gy][gx]
  return t ~= nil and t ~= -1
end

-- draw map once
drawMap()

-- load character as sprite so no SD read every move
loadSprite("char", "/games/" .. gameName .. "/assets/character1_16x16.bmp")

-- save background under starting position
saveRegion("charBg", charX, charY, 16, 16)

-- draw character first time
drawSprite("char", charX, charY,0xF81F)

function update()
  if millis() - lastMoved <= 200 then return end

  local newX = charX
  local newY = charY

  if btnIsDown("RIGHT") and newX < 304 then newX = newX + 16 end
  if btnIsDown("LEFT")  and newX > 0   then newX = newX - 16 end
  if btnIsDown("DOWN")  and newY < 224  then newY = newY + 16 end
  if btnIsDown("UP")    and newY > 0    then newY = newY - 16 end

  if newX == charX and newY == charY then return end

  local gx = math.floor(newX / 16) + 1
  local gy = math.floor(newY / 16) + 1

  -- collision
  if checkExists(gx, gy, layers["top"]) then return end

  lastMoved = millis()

  local pgx = math.floor(charX / 16) + 1
  local pgy = math.floor(charY / 16) + 1

  -- restore old position by redrawing all tile layers there
  -- this is reliable regardless of readRect working or not
  redrawTileStack(pgx, pgy)

  -- collect collectible at new position
  if checkExists(gx, gy, layers["collectibles"]) then
    layers["collectibles"].map[gy][gx] = -1
  end

  -- save background at new position BEFORE drawing character
  saveRegion("charBg", newX, newY, 16, 16)

  charX = newX
  charY = newY
  prevCharX = charX
  prevCharY = charY

  -- draw character from RAM sprite
  drawSprite("char", charX, charY,0xF81F)

  -- comment this out temporarily
  --for _, layerName in ipairs(drawOrder) do
    --  local layer = layers[layerName]
    --  if layer.overlay and checkExists(gx, gy, layer) then
      --    drawTile(layer.map[gy][gx], gx, gy, true)
      --  end
      --end

    end