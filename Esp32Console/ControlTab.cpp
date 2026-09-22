#include <Arduino.h>
#include <BleGamepad.h>
#include "ControlTab.h"
#include "I2SAudio.h"
#include "display.h"
#include "MyFonts.h"
#include "AudioHandler.h"
#include "ButtonManager.h"
#include "SettingsManager.h"
#include "Mpu6050Handler.h"
#include "Preferences.h"
#include "JoystickHandler.h"
#include "SpriteManager.h"

BleGamepad bleGamepad("Jojo's", "JojoTheAmazing", 100);
BleGamepadConfiguration bleGamepadConfig;

BleGamepad bleSteering("Jojo's steering", "JojoTheAmazing", 100);
BleGamepadConfiguration bleSteeringConfig;

static bool gamepadStarted = false;
static bool steeringStarted = false;
static bool calibratingMpu = false;
static const int ROW_Y[] = { 52, 88, 124, 160, 196, 232 };


uint8_t getGamepadButtonNum(ButtonID id) {
  switch (id) {
    case BTN_UP: return 13;
    case BTN_DOWN: return 14;
    case BTN_LEFT: return 15;
    case BTN_RIGHT: return 16;

    case BTN_A: return 1;
    case BTN_B: return 2;
    case BTN_X: return 3;
    case BTN_Y: return 4;

    case BTN_L: return 8;
    case BTN_R: return 7;
    case BTN_START: return 10;
    case BTN_SEL: return 9;

    case BTN_VOL_UP: return 13;
    case BTN_VOL_DOWN: return 14;
    case BTN_EXTRA1: return 12;
    case BTN_EXTRA2: return 11;

    default: return 0;
  }
}

int prevJoystickPos1[2][2] = {
  { 0, 0 },  // Left joystick(x, y)
  { 0, 0 }   // right joystick (x, y)
};



/*void onGamepadInput(ButtonID btn, InputEvent evt) {
  if (evt == EVT_RELEASED) {
    bleGamepad.release(getGamepadButtonNum(btn));
  }
  if (evt == EVT_PRESSED) {
    bleGamepad.press(getGamepadButtonNum(btn));
  }
}*/

#include <WiFi.h>

void ControlTab::startGamepad() {
  Serial.println("Starting gamepad");
  deinitI2SAudio();
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  //esp_wifi_deinit();
  delay(200);

  bleGamepadConfig.setButtonCount(16);
  bleGamepadConfig.setHatSwitchCount(0);

  bleGamepadConfig.setIncludeXAxis(true);
  bleGamepadConfig.setIncludeYAxis(true);
  bleGamepadConfig.setIncludeZAxis(true);
  bleGamepadConfig.setIncludeRxAxis(true);
  bleGamepadConfig.setIncludeRyAxis(true);
  bleGamepadConfig.setIncludeRzAxis(true);

  bleGamepadConfig.setIncludeSlider1(false);
  bleGamepadConfig.setIncludeSlider2(false);
  bleGamepadConfig.setIncludeRudder(false);
  bleGamepadConfig.setIncludeThrottle(false);
  bleGamepadConfig.setIncludeAccelerator(false);
  bleGamepadConfig.setIncludeBrake(false);
  bleGamepadConfig.setIncludeSteering(false);
  bleGamepadConfig.setAxesMin(-100);
  bleGamepadConfig.setAxesMax(100);
  //bleGamepad.begin();
  bleGamepad.begin(&bleGamepadConfig);
  gamepadStarted = true;
  Serial.println("Started gamepad");
}

void ControlTab::startSteering() {
  steeringStarted = true;
  drawSteering();
  deinitI2SAudio();
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  createCanvas("Steering", 300, 180, TFT_TRANSPARENT);
  //esp_wifi_deinit();
  delay(200);

  bleSteeringConfig.setAutoReport(false);
  bleSteeringConfig.setControllerType(CONTROLLER_TYPE_GAMEPAD);  // CONTROLLER_TYPE_JOYSTICK, CONTROLLER_TYPE_GAMEPAD (DEFAULT), CONTROLLER_TYPE_MULTI_AXIS
  bleSteeringConfig.setButtonCount(10);
  bleSteeringConfig.setWhichAxes(false, false, false, false, false, false, false, false);  // Can also be done per-axis individually. All are true by default
  bleSteeringConfig.setWhichSimulationControls(false, false, true, true, true);            // Can also be done per-control individually. All are false by default
  bleSteeringConfig.setHatSwitchCount(0);                                                  // 1 by default
  bleSteeringConfig.setSimulationMin(0x8000);
  bleSteeringConfig.setSimulationMax(0x7FFF);
  bleSteering.begin(&bleSteeringConfig);
  bleSteering.setSteering(0x00);

  // Set brake and accelerator to min
  bleSteering.setBrake(0x00);
  bleSteering.setAccelerator(0x7FFF);

  bleSteering.sendReport();
  loadSprite("Wheel", "/Assets/UIImages/ControlTab/SteeringWheel.bmp");
}

void ControlTab::redrawSteering(float steerValue, int16_t yValue) {
  TFT_eSprite* steeringCanvas = getCanvas("Steering");

  // Wheel
  steeringCanvas->setPivot(85, 90);
  drawSpriteRotated("Wheel", 80, 80, steerValue, TFT_RED, steeringCanvas);

  // Grey background bar
  steeringCanvas->fillRect(235, 27, 22, 126, COLOR_HINT);

  // Accel/brake overlay
  yValue = constrain(yValue, (int16_t)-100, (int16_t)100);
  const int16_t barX = 237, barW = 18;
  const int16_t midY = 27 + 126 / 2;  // 90
  const int16_t halfH = 122 / 2;      // 63

  int16_t barHeight = (int16_t)((abs(yValue) * halfH) / 100);

  if (yValue >= 0) {
    steeringCanvas->fillRect(barX, midY - barHeight, barW, barHeight, COLOR_SELECTED);
  } else {
    steeringCanvas->fillRect(barX, midY, barW, barHeight, COLOR_SELECTED);
  }
  steeringCanvas->fillRect(235, midY - 1, 22, 2, TFT_WHITE);
  drawTextTo("Acceleration", 246, 25, COLOR_TEXT, COLOR_BG,
             &FONT_SMALL, BC_DATUM, steeringCanvas);
  drawTextTo("Brake", 246, 151, COLOR_TEXT, COLOR_BG,
             &FONT_SMALL, TC_DATUM, steeringCanvas);
  pushCanvas("Steering", 10, 40, false);
  clearCanvas("Steering");
}


static unsigned long lastSteeringUpdate = 0;
static int16_t lastSteeringValue = INT16_MIN;
const unsigned long STEERING_INTERVAL_MS = 14;

void ControlTab::update() {
  switch (_state) {
    case State::GAMEPAD:
      if (bleGamepad.isConnected()) {
        int lx = getLX(), ly = getLY(), rx = getRX(), ry = getRY();

        bool changed = (prevJoystickPos1[0][0] != lx) || (prevJoystickPos1[0][1] != ly) || (prevJoystickPos1[1][0] != rx) || (prevJoystickPos1[1][1] != ry);

        if (changed) {
          bleGamepad.setLeftThumb(lx, ly);
          bleGamepad.setRightThumb(rx, ry);
          bleGamepad.sendReport();

          prevJoystickPos1[0][0] = lx;
          prevJoystickPos1[0][1] = ly;
          prevJoystickPos1[1][0] = rx;
          prevJoystickPos1[1][1] = ry;
        }
      }
      break;
    case State::STEERING_MODE:
      if (millis() - lastSteeringUpdate >= STEERING_INTERVAL_MS && steeringStarted) {
        lastSteeringUpdate = millis();

        MPUData d = getMPUData();
        const float ROLL_MIN = -64.0;
        const float ROLL_MAX = 64.0;

        float rollClamped = constrain(d.roll, ROLL_MIN, ROLL_MAX);

        int16_t steeringValue = (int16_t)map(
          (long)(rollClamped * 100),
          (long)(ROLL_MIN * 100),
          (long)(ROLL_MAX * 100),
          -32767,
          32767);

        if (abs(steeringValue) < 400) steeringValue = 0;
        int yValue = -getLY();
        int16_t acceleratorValue = 0;
        int16_t brakeValue = 0;
        if (yValue > 0) {
          acceleratorValue = (int16_t)map(yValue, 0, 100, 0, 32767);
        } else if (yValue < 0) {
          brakeValue = (int16_t)map(-yValue, 0, 100, 0, 32767);
        }


        Serial.printf("roll: %.2f  clamped: %.2f  steering: %d\n", d.roll, rollClamped, steeringValue);
        if (abs(steeringValue - lastSteeringValue) > 100 | yValue != 0) {
          const float VISUAL_SCALE = 180.0 / ROLL_MAX;
          float visualAngle = rollClamped * VISUAL_SCALE;

          redrawSteering(visualAngle, -yValue);
        }

        if (bleSteering.isConnected()) {
          bleSteering.setSteering(steeringValue);



          bleSteering.setAccelerator(acceleratorValue);
          bleSteering.setBrake(brakeValue);
          bleSteering.sendReport();
        }

        lastSteeringValue = steeringValue;
      }
      break;
  }
}



void ControlTab::onEnter() {
  //goTo(State.Menu);
  draw();
}
void ControlTab::onExit() {}

void ControlTab::draw() {
  switch (_state) {
    case State::MENU: drawMenu(); break;
    case State::GAMEPAD: drawGamepad(); break;
    case State::STEERING_MODE: drawSteering(); break;
  }
}

void ControlTab::drawMenu() {
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(&FONT_TITLE);
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(COLOR_TEXT, COLOR_BG);
  tft.drawString("Control", tft.width() / 2, 10);

  tft.setFreeFont(&FONT_BODY);
  tft.setTextDatum(TL_DATUM);

  tft.setTextColor(_selected == 0 ? COLOR_SELECTED : COLOR_TEXT, COLOR_BG);
  tft.drawString("Gamepad", 18, ROW_Y[0]);

  tft.setTextColor(_selected == 1 ? COLOR_SELECTED : COLOR_TEXT, COLOR_BG);
  tft.drawString("Steering Wheel", 18, ROW_Y[1]);
}

void ControlTab::drawGamepad() {
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(&FONT_TITLE);
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(COLOR_TEXT, COLOR_BG);
  tft.drawString("GAMEPAD", tft.width() / 2, 10);
  if (!gamepadStarted) {
    startGamepad();
  }
}

void ControlTab::drawSteering() {
  if (!steeringStarted) {
    tft.fillScreen(COLOR_BG);
    tft.setTextDatum(TC_DATUM);
    tft.setFreeFont(&FONT_BODY);
    tft.setTextColor(COLOR_TEXT);
    tft.drawString("Steering Wheel Setup", 320 / 2, 10);
    tft.setFreeFont(&FONT_BODY);
    tft.drawString("Place console flat on a table", 320 / 2, 50);
    tft.setTextColor(TFT_YELLOW);
    tft.drawString("Press <A> to start calibration", 320 / 2, 170);
    tft.setTextColor(TFT_RED);
    tft.setFreeFont(&FONT_SMALL);
    tft.drawString("!DO NOT MOVE THE DEVICE", 320 / 2, 90);
    tft.drawString("DURING CALIBRATION!", 320 / 2, 120);
    return;
    //startSteering();
  }
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(&FONT_TITLE);
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(COLOR_TEXT, COLOR_BG);
  tft.drawString("STEERING WHEEL", tft.width() / 2, 10);
}



void ControlTab::goTo(State s) {
  _state = s;
  _selected = 0;
  draw();
}

void ControlTab::onInput(ButtonID btn, InputEvent evt) {

  switch (_state) {
    case State::MENU: handleMenuInput(btn, evt); break;
    case State::GAMEPAD: handleGamepadInput(btn, evt); break;
    case State::STEERING_MODE: handleSteeringInput(btn, evt); break;
  }
}

void ControlTab::handleMenuInput(ButtonID btn, InputEvent evt) {
  int _maxItems = 2;
  if ((btn == BTN_UP || btn == BTN_DOWN) && (evt == EVT_PRESSED || evt == EVT_HELD)) {
    if (_maxItems == 0) return;

    int prev = _selected;
    if (btn == BTN_DOWN) _selected = (_selected + 1) % _maxItems;
    else _selected = (_selected - 1 + _maxItems) % _maxItems;

    if (prev != _selected)
      draw();
    return;
  }

  if (btn == BTN_B && evt == EVT_PRESSED) {
    exit();
    onExit();
    return;
  }
  if (btn == BTN_A && evt == EVT_PRESSED) goTo((State)(_selected + 1));
}

void ControlTab::handleGamepadInput(ButtonID btn, InputEvent evt) {
  if (evt == EVT_PRESSED) {
    bleGamepad.press(getGamepadButtonNum(btn));
    bleGamepad.sendReport();
    Serial.println("handleGamepadInput reached");
  } else if (evt == EVT_RELEASED) {
    bleGamepad.release(getGamepadButtonNum(btn));
    bleGamepad.sendReport();
  }

  if (evt == EVT_PRESSED && Input.isDown(BTN_START) && Input.isDown(BTN_SEL)) {
    if (gamepadStarted) {
      bleGamepad.end();
      gamepadStarted = false;
    }
    goTo(State::MENU);
    return;
  }
}

void ControlTab::handleSteeringInput(ButtonID btn, InputEvent evt) {
  if (calibratingMpu) return;
  if (evt == EVT_PRESSED && Input.isDown(BTN_START) && Input.isDown(BTN_SEL)) {
    if (steeringStarted) {
      bleSteering.end();
      steeringStarted = false;
    }
    goTo(State::MENU);
    return;
  }
  if (evt == EVT_PRESSED) {
    if (!steeringStarted) {
      if (btn == BTN_A) {
        calibratingMpu = true;
        tft.fillScreen(COLOR_BG);
        tft.setTextDatum(TC_DATUM);
        tft.setFreeFont(&FONT_BODY);
        tft.setTextColor(COLOR_TEXT);
        tft.drawString("Calibrating IMU...", 320 / 2, 20);
        tft.setFreeFont(&FONT_SMALL);
        tft.setTextDatum(BL_DATUM);
        tft.drawString("This should take a few seconds!", 0, 240);
        delay(1000);
        calibrateMpu();
        delay(100);
        startSteering();
        calibratingMpu = false;
      }
      if (btn == BTN_B) {
        goTo(State::MENU);
      }
    }
  }
  if (evt == EVT_PRESSED) {
    bleSteering.press(getGamepadButtonNum(btn));
    bleSteering.sendReport();
    Serial.println("handleSteeringInput reached");
  } else if (evt == EVT_RELEASED) {
    bleSteering.release(getGamepadButtonNum(btn));
    bleSteering.sendReport();
  }
}
