#include <Arduino.h>
#include "SettingsTab.h"
#include "display.h"
#include "MyFonts.h"
#include "AudioHandler.h"
#include "ButtonManager.h"
#include "SettingsManager.h"
#include "WiFiFileServer.h"
#include "Preferences.h"
#include "JoystickHandler.h"

// ── Items per state: MENU, DISP, AUDIO, BLUETOOTH, SYSTEM ────
const uint8_t SettingsTab::STATE_MAX_ITEMS[] = { 5, 1, 1, 1, 2, 1 };

// ── Layout ────────────────────────────────────────────────────
static const int LABEL_X = 18;
static const int VALUE_X = 155;
static const int ARROW_X = 8;
static const int TITLE_Y = 10;
static const int ROW_Y[] = { 52, 88, 124, 160, 196, 232 };
static const int BAR_W = 75;
static const int BAR_H = 7;
static const int ARROW_H = 10;

unsigned long joyLastMillis = 0;

int prevJoystickPos[2][2] = {
  { 0, 0 },  // Left joystick (x, y)
  { 0, 0 }   // Right joystick (x, y)
};

// =============================================================
//  LIFECYCLE
// =============================================================
void SettingsTab::onEnter() {
  _state = State::MENU;
  //_btState = BtState::MAIN;
  _filesState = FilesState::MAIN;
  _selected = 0;
  _maxItems = STATE_MAX_ITEMS[(int)State::MENU];
  /*if (settings.btEnabled == true && a2dp_source.is_connected() == false ) {
    a2dp_source.start();
    Serial.println("Bt started");
  }*/
  draw();
  Serial.println("[Settings] entered");
}

void SettingsTab::onExit() {
  Serial.println("[Settings] exited");

  /*if (!a2dp_source.is_connected()) {
    a2dp_source.end();
    Serial.println("Bt ended");
  }*/
}
int prevDeviceCount = 0;

void SettingsTab::update() {
  switch (_state) {
    case State::JOYSTICKS: redrawJoysticks(); break;
  }
}

void SettingsTab::goTo(State s) {
  _state = s;
  _selected = 0;
  _maxItems = STATE_MAX_ITEMS[(int)s];
  draw();
}

void SettingsTab::drawTitle(const char* text) {
  tft.setFreeFont(&FONT_TITLE);
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(COLOR_TEXT, COLOR_BG);
  tft.drawString(text, tft.width() / 2, TITLE_Y);
}

void SettingsTab::drawValueBar(int x, int y, int w, int h, int value, int maxVal, uint16_t color) {
  tft.fillRect(x, y, w, h, COLOR_HINT);
  if (maxVal == 0) return;
  int filled = constrain((value * w) / maxVal, 0, w);
  if (filled > 0) tft.fillRect(x, y, filled, h, color);
}

void SettingsTab::draw() {
  switch (_state) {
    case State::MENU: drawMenu(); break;
    case State::DISP: drawDisplay(); break;
    case State::AUDIO: drawAudio(); break;
    //case State::BLUETOOTH: drawBluetooth(); break;
    case State::SYSTEM: drawSystem(); break;
    case State::FILES: drawFiles(); break;
    case State::JOYSTICKS: drawJoystickCalibration(); break;
  }
}

void SettingsTab::drawMenu() {
  tft.fillScreen(COLOR_BG);
  drawTitle("Settings");


  const char* items[] = { "Display", "Audio", "System", "Files Config", "Joysticks" };
  tft.setFreeFont(&FONT_BODY);
  tft.setTextDatum(TL_DATUM);
  for (int i = 0; i < _maxItems; i++) {
    tft.setTextColor(_selected == i ? COLOR_SELECTED : COLOR_TEXT, COLOR_BG);
    tft.drawString(items[i], LABEL_X, ROW_Y[i]);
  }
}

void SettingsTab::drawJoystickCalibration() {
  tft.fillScreen(COLOR_BG);
  drawTitle("Joysticks");

  tft.setTextDatum(MC_DATUM);
  tft.setTextSize(1);
  tft.setTextColor(0xFFFF);
  //tft.setFreeFont(&FONT_SMALL);
  tft.setTextFont(1);
  // Right labels
  tft.setTextDatum(ML_DATUM);
  tft.drawString("100", 135, 112);
  tft.drawString("100", 295, 112);

  // Top labels
  tft.setTextDatum(BC_DATUM);
  tft.drawString("100", 80, 57);
  tft.drawString("100", 240, 57);

  // Left labels
  tft.setTextDatum(MR_DATUM);
  tft.drawString("-100", 25, 112);
  tft.drawString("-100", 185, 112);

  // Bottom labels
  tft.setTextDatum(TC_DATUM);
  tft.drawString("-100", 80, 167);
  tft.drawString("-100", 240, 167);

  // Center button
  tft.drawRoundRect(120, 217, 80, 17, 6, 0xFFFF);

  tft.setTextDatum(MC_DATUM);
  tft.drawString("Center", 160, 225);
  redrawJoysticks();
}

void SettingsTab::drawDisplay() {
  tft.fillScreen(COLOR_BG);
  drawTitle("Display");

  tft.setFreeFont(&FONT_BODY);
  tft.setTextDatum(TL_DATUM);

  //tft.setTextColor(_selected == 0 ? COLOR_SELECTED : COLOR_TEXT, COLOR_BG);
  //tft.drawString("Brightness", LABEL_X, ROW_Y[0]);
  tft.setTextColor(_selected == 0 ? COLOR_SELECTED : COLOR_TEXT, COLOR_BG);
  tft.drawString("Sleep", LABEL_X, ROW_Y[0]);

  //drawSelector(_selected);
  redrawDisplayValues();
}

void SettingsTab::drawAudio() {
  tft.fillScreen(COLOR_BG);
  drawTitle("Audio");

  tft.setFreeFont(&FONT_BODY);
  tft.setTextDatum(TL_DATUM);
  tft.setTextColor(_selected == 0 ? COLOR_SELECTED : COLOR_TEXT, COLOR_BG);
  tft.drawString("Volume", LABEL_X, ROW_Y[0]);
  //tft.setTextColor(_selected == 1 ? COLOR_SELECTED : COLOR_TEXT, COLOR_BG);
  //tft.drawString("Output", LABEL_X, ROW_Y[1]);

  //drawSelector(_selected);
  redrawAudioValues();
}


void SettingsTab::drawSystem() {
  tft.fillScreen(COLOR_BG);
  drawTitle("System");

  tft.setFreeFont(&FONT_SMALL);
  tft.setTextDatum(TL_DATUM);
  tft.setTextColor(COLOR_TEXT, COLOR_BG);

  tft.drawString("Free heap:  " + String(ESP.getFreeHeap()) + " B", LABEL_X, ROW_Y[0]);
  tft.drawString("SD:       " + String(sdReady ? "Ready" : "Not found"), LABEL_X, ROW_Y[1]);
  tft.drawString("Uptime:     " + String(millis() / 1000) + "  s", LABEL_X, ROW_Y[2]);

  tft.setTextDatum(BC_DATUM);
  tft.setTextColor(COLOR_HINT, COLOR_BG);
  tft.drawString("[A] Refresh  [B] Back", tft.width() / 2, tft.height() - 4);
}

void SettingsTab::drawFiles() {
  tft.fillScreen(COLOR_BG);

  switch (_filesState) {
    case FilesState::MAIN:
      drawTitle("FILES CONFIG");
      tft.setFreeFont(&FONT_BODY);
      tft.setTextDatum(TL_DATUM);

      tft.setTextColor(_selected == 0 ? COLOR_SELECTED : COLOR_TEXT, COLOR_BG);
      tft.drawString("Start AP", LABEL_X, ROW_Y[0]);

      tft.setTextColor(_selected == 1 ? COLOR_SELECTED : COLOR_TEXT, COLOR_BG);
      tft.drawString("Start STA", LABEL_X, ROW_Y[1]);

      tft.setFreeFont(&FONT_SMALL);
      tft.setTextDatum(TR_DATUM);
      tft.setTextColor(COLOR_HINT, COLOR_BG);
      tft.drawString("(No wifi access)", tft.width(), ROW_Y[0]);
      tft.drawString("(wifi access)", tft.width(), ROW_Y[1]);

      tft.setTextDatum(BC_DATUM);
      tft.drawString("For STA set ssid and key in json", tft.width() / 2, tft.height());
      break;
    case FilesState::WIFI_AP:
      drawTitle("WIFI AP");

      tft.setFreeFont(&FONT_SMALL);
      tft.setTextDatum(TL_DATUM);
      tft.setTextColor(COLOR_TEXT, COLOR_BG);
      tft.drawString("1. Connect to 'ESP32 CONSOLE' network password:'12345678'", LABEL_X, ROW_Y[0]);
      tft.drawString("2. Head to 'http://192.168.4.1'", LABEL_X, ROW_Y[1]);
      tft.drawString("3. Configure SD files", LABEL_X, ROW_Y[2]);

      break;
    case FilesState::WIFI_STA:
      drawTitle("WIFI STA");

      tft.setFreeFont(&FONT_SMALL);
      tft.setTextDatum(TL_DATUM);
      tft.setTextColor(COLOR_TEXT, COLOR_BG);
      tft.drawString("1. Connect to your WiFi", LABEL_X, ROW_Y[0]);
      tft.drawString("2. Head to 'http://" + wfsIP() + "'", LABEL_X, ROW_Y[1]);
      tft.drawString("3. Configure SD files", LABEL_X, ROW_Y[2]);
      break;
  }
}

void SettingsTab::redrawDisplayValues() {
  tft.fillRect(VALUE_X, ROW_Y[0], tft.width() - VALUE_X, ROW_Y[1] - ROW_Y[0] + 36, COLOR_BG);

  //drawValueBar(VALUE_X, ROW_Y[0] + 6, BAR_W, BAR_H, settings.brightness, 100);
  drawValueBar(VALUE_X, ROW_Y[0] + 6, BAR_W, BAR_H, settings.sleepTimeout, 120);

  tft.setFreeFont(&FONT_SMALL);
  tft.setTextDatum(TL_DATUM);
  tft.setTextColor(COLOR_TEXT, COLOR_BG);
  //tft.drawString(String(settings.brightness) + "%",
  //               VALUE_X + BAR_W + 5, ROW_Y[0]);
  tft.drawString(settings.sleepTimeout == 0 ? "Never" : String(settings.sleepTimeout) + "s",
                 VALUE_X + BAR_W + 5, ROW_Y[0]);
}

void SettingsTab::redrawJoysticks() {
  if (prevJoystickPos[0][0] == getLX() && prevJoystickPos[0][1] == getLY() && prevJoystickPos[1][0] == getRX() && prevJoystickPos[1][1] == getRY()) {
    return;
  }
  if ((millis() - joyLastMillis) < 10) return;
  joyLastMillis = millis();

  tft.setTextSize(1);
  tft.setTextColor(COLOR_BG);
  tft.setFreeFont(&FONT_SMALL);

  tft.fillCircle(map(prevJoystickPos[0][0], -100, 100, 30, 130), map(prevJoystickPos[0][1] * -1, -100, 100, 62, 162), 3, COLOR_BG);

  tft.fillCircle(map(prevJoystickPos[1][0], -100, 100, 190, 290), map(prevJoystickPos[1][1] * -1, -100, 100, 62, 162), 3, COLOR_BG);

  // Left joystick
  tft.drawLine(30, 112, 130, 112, 0xFFFF);
  tft.drawLine(80, 62, 80, 162, 0xFFFF);

  // Right joystick
  tft.drawLine(190, 112, 290, 112, 0xFFFF);
  tft.drawLine(240, 62, 240, 162, 0xFFFF);
  tft.setTextFont(1);
  tft.setTextDatum(MC_DATUM);
  tft.drawString(String(prevJoystickPos[0][0]) + "," + String(prevJoystickPos[0][1]), 80, 189);
  tft.drawString(String(prevJoystickPos[1][0]) + "," + String(prevJoystickPos[1][1]), 240, 189);

  prevJoystickPos[0][0] = getLX();
  prevJoystickPos[0][1] = getLY();
  prevJoystickPos[1][0] = getRX();
  prevJoystickPos[1][1] = getRY();

  tft.setTextColor(COLOR_TEXT);
  tft.setTextColor(0xFFFF);

  tft.fillCircle(map(prevJoystickPos[0][0], -100, 100, 30, 130), map(prevJoystickPos[0][1] * -1, -100, 100, 62, 162), 3, COLOR_SELECTED);
  tft.fillCircle(map(prevJoystickPos[1][0], -100, 100, 190, 290), map(prevJoystickPos[1][1] * -1, -100, 100, 62, 162), 3, COLOR_SELECTED);

  tft.setTextDatum(MC_DATUM);
  tft.drawString(String(prevJoystickPos[0][0]) + "," + String(prevJoystickPos[0][1]), 80, 189);
  tft.drawString(String(prevJoystickPos[1][0]) + "," + String(prevJoystickPos[1][1]), 240, 189);
}

void SettingsTab::redrawAudioValues() {
  tft.fillRect(VALUE_X, ROW_Y[0], tft.width() - VALUE_X, ROW_Y[1] - ROW_Y[0] + 36, COLOR_BG);

  drawValueBar(VALUE_X, ROW_Y[0] + 6, BAR_W, BAR_H, settings.volume, 100);

  tft.setFreeFont(&FONT_SMALL);
  tft.setTextDatum(TL_DATUM);
  tft.setTextColor(COLOR_TEXT, COLOR_BG);
  tft.drawString(String(settings.volume) + "%", VALUE_X + BAR_W + 5, ROW_Y[0]);

  //tft.setTextColor(currentAudioOutput == 2 ? TFT_CYAN : COLOR_TEXT, COLOR_BG);
  //tft.drawString("Speaker", VALUE_X, ROW_Y[1]);
}

/*void SettingsTab::redrawBtStatus() {
  tft.fillRect(0, tft.height() - 22, tft.width(), 22, COLOR_BG);
  tft.setFreeFont(&FONT_SMALL);
  tft.setTextDatum(BC_DATUM);
  tft.setTextColor(connectedTo.isEmpty() ? COLOR_HINT : COLOR_SUCCESS, COLOR_BG);
  tft.drawString(connectedTo.isEmpty() ? "Not connected" : String("  ") + connectedTo,
                 tft.width() / 2, tft.height() - 2);
}*/

void SettingsTab::onInput(ButtonID btn, InputEvent evt) {
  if (evt != EVT_PRESSED && evt != EVT_REPEAT) return;

  if (btn == BTN_UP || btn == BTN_DOWN) {
    if (_maxItems == 0) return;
    //if (_state == State::BLUETOOTH && _btState == BtState::SCANNING) return;

    int prev = _selected;
    if (btn == BTN_DOWN) _selected = (_selected + 1) % _maxItems;
    else _selected = (_selected - 1 + _maxItems) % _maxItems;

    if (prev != _selected)
      draw();
    return;
  }

  switch (_state) {
    case State::MENU: handleMenuInput(btn, evt); break;
    case State::DISP: handleDisplayInput(btn, evt); break;
    case State::AUDIO: handleAudioInput(btn, evt); break;
    //case State::BLUETOOTH: handleBluetoothInput(btn, evt); break;
    case State::SYSTEM: handleSystemInput(btn, evt); break;
    case State::FILES: handleFilesInput(btn, evt); break;
    case State::JOYSTICKS: handleJoysticksInput(btn, evt); break;
  }
}

void SettingsTab::handleJoysticksInput(ButtonID btn, InputEvent evt) {
  if (btn == BTN_A && evt == EVT_PRESSED) {
    calculateOffsets();
  }
  if (btn == BTN_B && evt == EVT_PRESSED) {
    goTo(State::MENU);
    return;
  }
}

void SettingsTab::handleMenuInput(ButtonID btn, InputEvent evt) {
  if (btn == BTN_B && evt == EVT_PRESSED) {
    exit();
    onExit();
    return;
  }
  if (btn == BTN_A && evt == EVT_PRESSED) goTo((State)(_selected + 1));
}

void SettingsTab::handleDisplayInput(ButtonID btn, InputEvent evt) {
  if (btn == BTN_B && evt == EVT_PRESSED) {
    goTo(State::MENU);
    saveSettings();
    return;
  }

  /*if (_selected == 0) {
    if (btn == BTN_RIGHT) {
      settings.brightness = min(100, settings.brightness + 5);
    }
    if (btn == BTN_LEFT) {
      settings.brightness = max(0, settings.brightness - 5);
    }
    // TODO: analogWrite(BACKLIGHT_PIN, map(settings.brightness, 0, 100, 0, 255)); and hope it works currently not using a gpio for blacklight might add a transistor
  }*/
  if (_selected == 0) {
    if (btn == BTN_RIGHT) {
      settings.sleepTimeout = min(120, settings.sleepTimeout + 10);
    }
    if (btn == BTN_LEFT) {
      settings.sleepTimeout = max(0, settings.sleepTimeout - 10);
    }
  }
  if (btn == BTN_LEFT || btn == BTN_RIGHT) redrawDisplayValues();
}

void SettingsTab::handleAudioInput(ButtonID btn, InputEvent evt) {
  if (btn == BTN_B && evt == EVT_PRESSED) {
    goTo(State::MENU);
    saveSettings();
    return;
  }

  if (_selected == 0) {
    if (btn == BTN_RIGHT) {
      settings.volume = min(100, settings.volume + 2);
      volumeAdjust(settings.volume);
    }
    if (btn == BTN_LEFT) {
      settings.volume = max(0, settings.volume - 2);
      volumeAdjust(settings.volume);
    }
  }
  /*if (_selected == 1 && evt == EVT_PRESSED) {
    if (btn == BTN_A || btn == BTN_LEFT || btn == BTN_RIGHT)
      if (!a2dp_source.is_connected()) {
        changeOutput(1);
        return;
      }
    changeOutput(currentAudioOutput == 1 ? 2 : 1);
  }*/
  if (btn == BTN_LEFT || btn == BTN_RIGHT || btn == BTN_A) redrawAudioValues();
}

/*void SettingsTab::handleBluetoothInput(ButtonID btn, InputEvent evt) {
  if (evt != EVT_PRESSED) return;

  switch (_btState) {
    case BtState::MAIN:
      if (btn == BTN_B) {
        goTo(State::MENU);
        saveSettings();
        return;
      }
      if (btn == BTN_A) {
        if (_selected == 0) {
          // blocking scan — draws "Scanning..." then shows results
          //_btState = BtState::SCANNING;
          //_btState = BtState::DEVICE_LIST;
          //drawBluetooth();
          //getAvailableDevices(15000);
          _selected = 0;
          _maxItems = constrain(deviceCount, 1, 4);
          _btState = BtState::DEVICE_LIST;
          drawBluetooth();
        }
        if (_selected == 1 && !connectedTo.isEmpty()) {
          disconnectDevice();
          delay(100);
          redrawBtStatus();
        }
        if (_selected == 2) {
          settings.autoConnect = !settings.autoConnect;

          drawBluetooth();
        }
      }
      break;

    case BtState::SCANNING:
      break;

    case BtState::DEVICE_LIST:
      if (btn == BTN_B) {
        _btState = BtState::MAIN;
        _selected = 0;
        _maxItems = STATE_MAX_ITEMS[(int)State::BLUETOOTH];
        drawBluetooth();
        return;
      }
      if (btn == BTN_A && deviceCount > 0) {
        tft.fillScreen(COLOR_BG);
        drawTitle("Bluetooth");
        tft.setFreeFont(&FONT_TITLE);
        tft.setTextDatum(MC_DATUM);
        tft.setTextColor(COLOR_TEXT, COLOR_BG);
        tft.drawString("Connecting...", tft.width() / 2, tft.height() / 2 - 16);
        tft.setFreeFont(&FONT_SMALL);
        tft.setTextColor(TFT_CYAN, COLOR_BG);
        tft.drawString(availableDevices[_selected].name, tft.width() / 2, tft.height() / 2 + 16);

        connectToDevice(_selected);
        unsigned long start = millis();
        delay(100);
        while (a2dp_source.get_connection_state() == ESP_A2D_CONNECTION_STATE_CONNECTING) {
          if (Input.pressed(BTN_B)) {
            a2dp_source.disconnect();
            break;
          }
          if (millis() - start > 8000) {
            Serial.println("Timeout!");
            tft.setTextColor(TFT_RED, COLOR_BG);
            tft.setTextDatum(MC_DATUM);
            tft.drawString("Failed to connect :(", tft.width() / 2, tft.height() / 2);
            delay(3000);
            break;
          }
          delay(100);
        }
        _btState = BtState::MAIN;
        _selected = 0;
        _maxItems = STATE_MAX_ITEMS[(int)State::BLUETOOTH];
        drawBluetooth();
      }
      break;
  }
}*/

void SettingsTab::handleSystemInput(ButtonID btn, InputEvent evt) {
  if (btn == BTN_B && evt == EVT_PRESSED) {
    goTo(State::MENU);
    return;
  }
  if (btn == BTN_A && evt == EVT_PRESSED) drawSystem();
}

void SettingsTab::handleFilesInput(ButtonID btn, InputEvent evt) {
  if (evt != EVT_PRESSED) return;

  switch (_filesState) {
    case FilesState::MAIN:
      if (btn == BTN_B) {
        goTo(State::MENU);
        loadSettings();
        return;
      }
      if (btn == BTN_A) {
        if (_selected == 0) {
          _selected = 0;
          _maxItems = 0;
          _filesState = FilesState::WIFI_AP;
          wfsStop();
          wfsStart(WfsMode::AP, "Esp32 Console", "12345678");
          drawFiles();
        }
        if (_selected == 1) {
          _selected = 0;
          _maxItems = 0;
          _filesState = FilesState::WIFI_STA;
          wfsStop();
          wfsStart(WfsMode::STA, settings.ssid.c_str(), settings.password.c_str());
          drawFiles();
        }
      }
      break;
    case FilesState::WIFI_AP:
      if (btn == BTN_B) {
        _maxItems = 2;
        wfsStop();
        _filesState = FilesState::MAIN;
        drawFiles();
        return;
      }
      break;
    case FilesState::WIFI_STA:
      if (btn == BTN_B) {
        _maxItems = 2;
        wfsStop();
        _filesState = FilesState::MAIN;
        drawFiles();
        return;
      }
      break;
  }
}