#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MCP23X17.h>

#define INPUT_SDA_PIN 2
#define INPUT_SCL_PIN 1
#define INPUT_INT_PIN 42
#define INPUT_MCP_ADDR 0x20

enum ButtonID : uint8_t {

  BTN_UP = 3,
  BTN_DOWN = 7,
  BTN_LEFT = 6,
  BTN_RIGHT = 5,

  BTN_A = 10,
  BTN_B = 8,
  BTN_X = 9,
  BTN_Y = 11,

  BTN_L = 4,
  BTN_R = 13,
  BTN_START = 14,
  BTN_SEL = 15,

  BTN_VOL_UP = 0,
  BTN_VOL_DOWN = 1,
  BTN_EXTRA1 = 2,
  BTN_EXTRA2 = 12,

  BTN_COUNT = 16
};

enum InputEvent : uint8_t {
  EVT_PRESSED = 0,
  EVT_RELEASED = 1,
  EVT_HELD = 2,
  EVT_REPEAT = 3
};

using InputCallback = void (*)(ButtonID btn, InputEvent evt);

static constexpr uint16_t DEBOUNCE_MS = 20;  
static constexpr uint16_t HOLD_MS = 500; 
static constexpr uint16_t REPEAT_MS = 120;
static constexpr uint8_t MAX_LISTENERS = 4;

class InputManager {
public:

  void begin();
  void update();
  void notify();

  bool pressed(ButtonID btn) const;
  bool released(ButtonID btn) const;

  bool isDown(ButtonID btn) const;

  bool held(ButtonID btn) const;

  bool repeated(ButtonID btn) const;

  bool anyPressed() const;

  bool addListener(InputCallback cb);
  bool removeListener(InputCallback cb);


  void printState() const;
  const char* buttonName(ButtonID btn) const;


  volatile bool _isrFired = false;

private:
  Adafruit_MCP23X17 _mcp;

  uint16_t _rawState = 0xFFFF;
  uint16_t _lastState = 0xFFFF;

  struct BtnState {
    bool down = false;
    bool pressedEdge = false;
    bool relEdge = false;
    bool heldFired = false;
    bool repeated = false;
    uint32_t downSince = 0;
    uint32_t lastRepeat = 0;
  };
  BtnState _btn[BTN_COUNT];

  InputCallback _listeners[MAX_LISTENERS] = {};

  void _processChanges(uint16_t current);
  void _fireCb(ButtonID id, InputEvent evt);
  void _initMCP();
};

extern InputManager Input;
