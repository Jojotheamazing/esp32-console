#include "JoystickHandler.h"
#include "SettingsManager.h"

const int JOY_R_X = 11;
const int JOY_R_Y = 12;

const int JOY_L_X = 14;
const int JOY_L_Y = 13;

static int centerLX = 2048;
static int centerRX = 2048;
static int centerLY = 2048;
static int centerRY = 2048;

static JoystickData leftStick = { 0, 0 };
static JoystickData rightStick = { 0, 0 };

static int currentDeadzone = 150;
static int targetMaxValue = 100;

static int physicalLimitPadding = 400;

static int processAxis(int pin, int centerVal, bool invert = false) {
  int raw = analogRead(pin);

  int centered = raw - centerVal;

  if (abs(centered) < currentDeadzone) {
    return 0;
  }

  int mappedValue = 0;
  if (centered > 0) {
    int maxPossiblePos = 4095 - centerVal - physicalLimitPadding;
    mappedValue = map(centered, currentDeadzone, maxPossiblePos, 0, targetMaxValue);
  } else {
    int maxPossibleNeg = -centerVal + physicalLimitPadding;
    mappedValue = map(centered, -currentDeadzone, maxPossibleNeg, 0, -targetMaxValue);
  }

  mappedValue = constrain(mappedValue, -targetMaxValue, targetMaxValue);

  return invert ? -mappedValue : mappedValue;
}

void updateJoysticks() {
  leftStick.x = processAxis(JOY_L_X, settings.centerLX, true);
  leftStick.y = processAxis(JOY_L_Y, settings.centerLY, true);

  rightStick.x = processAxis(JOY_R_X, settings.centerRX);
  rightStick.y = processAxis(JOY_R_Y, settings.centerRY);

  Serial.printf("L raw: (%d,%d) center:(%d,%d) mapped:(%d,%d) | R raw: (%d,%d) center:(%d,%d) mapped:(%d,%d)\n",
                analogRead(JOY_L_X), analogRead(JOY_L_Y), settings.centerLX, settings.centerLY, leftStick.x, leftStick.y,
                analogRead(JOY_R_X), analogRead(JOY_R_Y), settings.centerRX, settings.centerRY, rightStick.x, rightStick.y);
}

void calculateOffsets() {
  centerLX = analogRead(JOY_L_X);
  centerRX = analogRead(JOY_R_X);
  centerLY = analogRead(JOY_L_Y);
  centerRY = analogRead(JOY_R_Y);

  settings.centerLX = centerLX;
  settings.centerRX = centerRX;
  settings.centerLY = centerLY;
  settings.centerRY = centerRY;
  saveSettings();

  Serial.print("Centers: ");
  Serial.print(centerLX);
  Serial.print(" ");
  Serial.print(centerRX);
  Serial.print(" ");
  Serial.print(centerLY);
  Serial.print(" ");
  Serial.println(centerRY);
}

int getLX() {
  leftStick.x = processAxis(JOY_L_X, settings.centerLX, true);
  return leftStick.x;
}
int getLY() {
  leftStick.y = processAxis(JOY_L_Y, settings.centerLY, true);
  return leftStick.y;
}
int getRX() {
  rightStick.x = processAxis(JOY_R_X, settings.centerRX);
  return rightStick.x;
}
int getRY() {
  rightStick.y = processAxis(JOY_R_Y, settings.centerRY);
  return rightStick.y;
}

void setDeadzone(int dz) {
  currentDeadzone = dz;
}
void setMaxValue(int maxVal) {
  targetMaxValue = maxVal;
}