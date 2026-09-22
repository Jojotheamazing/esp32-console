#include "ButtonManager.h"
#include "esp_log.h"

InputManager Input;

static const char* const BTN_NAMES[BTN_COUNT] = {
  "RIGHT","UP","DOWN","LEFT",
  "A","B","X","Y",
  "L","R","START","SEL",
  "VOL+","VOL-","EXTRA1","EXTRA2"
};


static void IRAM_ATTR _mcpISR() { Input._isrFired = true; }


void InputManager::begin()
{
  _initMCP();

  pinMode(INPUT_INT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INPUT_INT_PIN), _mcpISR, FALLING);

  Serial.println("[Input] InputManager ready");
}


void InputManager::_initMCP()
{
  esp_log_level_set("i2c.master", ESP_LOG_NONE);

  Wire.begin(INPUT_SDA_PIN, INPUT_SCL_PIN);
  Wire.setClock(400000);

  while (!_mcp.begin_I2C(INPUT_MCP_ADDR, &Wire)) {
    Serial.println("[Input] MCP23017 not found — retrying...");
    delay(500);
  }
  Serial.println("[Input] MCP23017 found at 0x20");

  for (int i = 0; i < 16; i++)
    _mcp.pinMode(i, INPUT_PULLUP);

  _mcp.setupInterrupts(true, false, LOW);

  for (int i = 0; i < 16; i++)
    _mcp.setupInterruptPin(i, CHANGE);

  _rawState  = _mcp.readGPIOAB();
  _lastState = _rawState;
  _mcp.clearInterrupts();
}

void InputManager::update()
{

  for (int i = 0; i < BTN_COUNT; i++) {
    _btn[i].pressedEdge = false;
    _btn[i].relEdge     = false;
    _btn[i].repeated    = false;
  }

  if (_isrFired) {
    _isrFired = false;
    delay(DEBOUNCE_MS);

    uint16_t current = _mcp.readGPIOAB();
    _processChanges(current);
    _lastState = current;
    _rawState  = current;
    _mcp.clearInterrupts();
  }

  uint32_t now = millis();
  for (int i = 0; i < BTN_COUNT; i++) {
    BtnState& b = _btn[i];
    if (!b.down) continue;

    uint32_t elapsed = now - b.downSince;

    if (!b.heldFired && elapsed >= HOLD_MS) {
      b.heldFired = true;
      b.lastRepeat = now;
      _fireCb((ButtonID)i, EVT_HELD);
    }

    if (b.heldFired && (now - b.lastRepeat) >= REPEAT_MS) {
      b.lastRepeat = now;
      b.repeated   = true;
      _fireCb((ButtonID)i, EVT_REPEAT);
    }
  }
}

void InputManager::notify() { update(); }

void InputManager::_processChanges(uint16_t current)
{
  uint16_t changed = current ^ _lastState;

  for (int i = 0; i < BTN_COUNT; i++) {
    uint16_t mask = (1u << i);
    if (!(changed & mask)) continue;

    bool nowDown = !(current & mask);

    _btn[i].down = nowDown;

    if (nowDown) {
      _btn[i].pressedEdge = true;
      _btn[i].heldFired   = false;
      _btn[i].repeated    = false;
      _btn[i].downSince   = millis();
      _fireCb((ButtonID)i, EVT_PRESSED);
    } else {
      _btn[i].relEdge     = true;
      _btn[i].heldFired   = false;
      _fireCb((ButtonID)i, EVT_RELEASED);
    }
  }
}

void InputManager::_fireCb(ButtonID id, InputEvent evt)
{
  for (int i = 0; i < MAX_LISTENERS; i++)
    if (_listeners[i]) _listeners[i](id, evt);
}

bool InputManager::pressed (ButtonID b) const { return _btn[b].pressedEdge; }
bool InputManager::released(ButtonID b) const { return _btn[b].relEdge;     }
bool InputManager::isDown  (ButtonID b) const { return _btn[b].down;        }
bool InputManager::held    (ButtonID b) const { return _btn[b].heldFired;   }
bool InputManager::repeated(ButtonID b) const { return _btn[b].repeated;    }

bool InputManager::anyPressed() const {
  for (int i = 0; i < BTN_COUNT; i++)
    if (_btn[i].pressedEdge) return true;
  return false;
}

bool InputManager::addListener(InputCallback cb) {
  for (int i = 0; i < MAX_LISTENERS; i++) {
    if (!_listeners[i]) { _listeners[i] = cb; return true; }
  }
  Serial.println("[Input] addListener: no free slots");
  return false;
}

bool InputManager::removeListener(InputCallback cb) {
  for (int i = 0; i < MAX_LISTENERS; i++) {
    if (_listeners[i] == cb) { _listeners[i] = nullptr; return true; }
  }
  return false;
}
const char* InputManager::buttonName(ButtonID btn) const {
  if (btn >= BTN_COUNT) return "??";
  return BTN_NAMES[btn];
}

void InputManager::printState() const {
  Serial.print("[Input] down: ");
  bool any = false;
  for (int i = 0; i < BTN_COUNT; i++) {
    if (_btn[i].down) {
      Serial.printf("%s ", BTN_NAMES[i]);
      any = true;
    }
  }
  if (!any) Serial.print("(none)");
  Serial.println();
}
