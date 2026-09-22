#pragma once

#include <Arduino.h>

struct SettingsData {

  //int brightness = 80;
  int sleepTimeout = 30;

  int volume = 80;
  //int audioOutput = 1;

  /*bool autoConnect = false;
  bool btEnabled = true;
  String lastConnected = "";*/

  String ssid = "Vodafone2025";
  String password = "stelios123";

  //joysticks
  int centerLX = 2048;
  int centerRX = 2048;
  int centerLY = 2048;
  int centerRY = 2048;

  bool vibrationEnabled = true;
};

extern SettingsData settings;

bool loadSettings();
bool saveSettings();