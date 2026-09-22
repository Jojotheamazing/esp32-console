  #include <Arduino.h>
#include <Wire.h>
#include "hw_config.h"
#include "ButtonManager.h"
#include "JoystickHandler.h"

extern InputManager Input;

// NES gamepad bitmask
#define NES_A 0x01
#define NES_B 0x02
#define NES_SELECT 0x04
#define NES_START 0x08
#define NES_UP 0x10
#define NES_DOWN 0x20
#define NES_LEFT 0x40
#define NES_RIGHT 0x80

#define CONTROLLER_POLL_INTERVAL_MS 8
static uint32_t last_poll_time_ms = 0;


extern "C" void controller_init() {
  Serial.println("[Controller] Interfaced with ButtonManager safely.");
}

extern "C" int IRAM_ATTR nes_get_gamepad_state() {
  uint32_t now = millis();

  if (now - last_poll_time_ms >= CONTROLLER_POLL_INTERVAL_MS || Input._isrFired) {
    last_poll_time_ms = now;

    Input.update();
  }

  int state = 0;

  if (getLX() > 50) { state |= NES_RIGHT; }
  if (getLX() < -50) { state |= NES_LEFT; }
  if (getLY() > 50) { state |= NES_UP; }
  if (getLY() < -50) { state |= NES_DOWN; }

  if (Input.isDown(BTN_A)) state |= NES_A;
  if (Input.isDown(BTN_B)) state |= NES_B;
  if (Input.isDown(BTN_SEL)) state |= NES_SELECT;
  if (Input.isDown(BTN_START)) state |= NES_START;
  if (Input.isDown(BTN_UP)) state |= NES_UP;
  if (Input.isDown(BTN_DOWN)) state |= NES_DOWN;
  if (Input.isDown(BTN_LEFT)) state |= NES_LEFT;
  if (Input.isDown(BTN_RIGHT)) state |= NES_RIGHT;

  return state;
}