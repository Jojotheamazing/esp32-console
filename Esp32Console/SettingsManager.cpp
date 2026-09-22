#include "SettingsManager.h"
#include <ArduinoJson.h>
#include <SD.h>

#define SETTINGS_FILE "/settings.json"

SettingsData settings;

bool saveSettings() {

  StaticJsonDocument<1024> doc;

  //Display
  //doc["display"]["brightness"] = settings.brightness;
  doc["display"]["sleepTimeout"] = settings.sleepTimeout;

  //audio
  doc["audio"]["volume"] = settings.volume;
  //doc["audio"]["output"] = settings.audioOutput;

  //bt
  /*doc["bluetooth"]["btEnabled"] = settings.btEnabled;
  doc["bluetooth"]["autoConnect"] = settings.autoConnect;
  doc["bluetooth"]["lastConnected"] = settings.lastConnected;*/

  doc["wifi"]["ssid"] = settings.ssid;
  doc["wifi"]["password"] = settings.password;

  doc["Joysticks"]["centerLX"] = settings.centerLX;
  doc["Joysticks"]["centerRX"] = settings.centerRX;
  doc["Joysticks"]["centerLY"] = settings.centerLY;
  doc["Joysticks"]["centerRY"] = settings.centerRY;

  doc["Haptics"]["VibrationEnabled"] = settings.vibrationEnabled;

  SD.remove(SETTINGS_FILE);

  File f = SD.open(SETTINGS_FILE, FILE_WRITE);

  if (!f) {
    Serial.println("[Settings] Failed to save.");
    return false;
  }

  serializeJsonPretty(doc, f);

  f.close();

  Serial.println("[Settings] Saved.");

  return true;
}

bool loadSettings() {

  if (!SD.exists(SETTINGS_FILE)) {

    Serial.println("[Settings] No settings file.");
    saveSettings();
    return true;
  }

  File f = SD.open(SETTINGS_FILE, FILE_READ);

  if (!f) {
    Serial.println("[Settings] Failed to open.");
    return false;
  }

  StaticJsonDocument<1024> doc;

  DeserializationError err = deserializeJson(doc, f);

  f.close();

  if (err) {
    Serial.println("[Settings] JSON parse failed.");
    return false;
  }

  //display
  //settings.brightness =
  //  doc["display"]["brightness"] | 80;

  settings.sleepTimeout =
    doc["display"]["sleepTimeout"] | 30;

  //audio
  settings.volume =
    doc["audio"]["volume"] | 80;

  //settings.audioOutput =
  //  doc["audio"]["output"] | 1;

  //bluetooth
  /*settings.btEnabled =
    doc["bluetooth"]["btEnabled"] | true;

  settings.autoConnect =
    doc["bluetooth"]["autoConnect"] | true;

  settings.lastConnected =
    String(doc["bluetooth"]["lastConnected"] | "");*/


  settings.ssid =
    String(doc["wifi"]["ssid"] | "");
  settings.password =
    String(doc["wifi"]["password"] | "");

  settings.centerLX = doc["Joysticks"]["centerLX"] | 2048;
  settings.centerRX = doc["Joysticks"]["centerRX"] | 2048;
  settings.centerLY = doc["Joysticks"]["centerLY"] | 2048;
  settings.centerRY = doc["Joysticks"]["centerRY"] | 2048;

  settings.vibrationEnabled = doc["Haptics"]["VibrationEnabled"] | true;


  Serial.println("[Settings] Loaded.");

  return true;
}