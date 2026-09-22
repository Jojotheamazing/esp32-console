#include <Arduino.h>
#include "PCTab.h"
#include "display.h"
#include "MyFonts.h"
#include "AudioHandler.h"
#include "ButtonManager.h"
#include "SettingsManager.h"
#include "WiFiFileServer.h"
#include "Preferences.h"
#include "PCBridge.h"

static const int LABEL_X = 18;
static const int VALUE_X = 155;
static const int ARROW_X = 8;
static const int TITLE_Y = 10;
static const int ROW_Y[] = { 52, 88, 124, 160, 196, 232 };
static const int BAR_W = 75;
static const int BAR_H = 7;
static const int ARROW_H = 10;
bool isMenuShown = false;

void PcTab::onEnter() {
  _state = State::MENU;
  _selected = 0;
  _pendingStart = PendingStart::NONE;

  _wifiBeginCalled = false;
  _wifiWaitShown = false;
  draw();
  Serial.println("[PcTab] entered");
}

void PcTab::onExit() {
  pcb_stop();
  _pendingStart = PendingStart::NONE;
  _wifiBeginCalled = false;
  _wifiWaitShown = false;
  WiFi.disconnect(true);
  Serial.println("[PcTab] exited");
}

void PcTab::update() {
  if (isMenuShown == true) {
    return;
  }

  if (_pendingStart != PendingStart::NONE) {
    if (WiFi.status() != WL_CONNECTED) {
      if (!_wifiBeginCalled) {
        Serial.printf("[PcTab] Connecting to WiFi: %s\n", settings.ssid);
        WiFi.mode(WIFI_STA);
        WiFi.begin(settings.ssid, settings.password);
        _wifiBeginCalled = true;
        _wifiConnectStart = millis();
      }

      if (!_wifiWaitShown) {
        tft.setFreeFont(&FONT_BODY);
        tft.setTextDatum(MC_DATUM);
        tft.setTextColor(TFT_YELLOW, TFT_BLACK);
        tft.drawString("Connecting to WiFi..", tft.width() / 2, tft.height() / 2 + 24);
        _wifiWaitShown = true;
      }

      if (millis() - _wifiConnectStart > 15000) {
        Serial.println("[PcTab] WiFi connect timed out");
        tft.fillScreen(TFT_BLACK);
        tft.setFreeFont(&FONT_BODY);
        tft.setTextDatum(MC_DATUM);
        tft.setTextColor(TFT_RED, TFT_BLACK);
        tft.drawString("WiFi connect failed", tft.width() / 2, tft.height() / 2);
        _pendingStart = PendingStart::NONE;
        _wifiBeginCalled = false;
        _wifiWaitShown = false;
      }
      return;
    }

    _wifiBeginCalled = false;
    _wifiWaitShown = false;
    _todo = _pendingStart;
    _pendingStart = PendingStart::NONE;

    switch (_todo) {
      case PendingStart::MIRROR:
        pcb_startMirror();
        break;
      case PendingStart::MIRROR_CTRL:
        pcb_startMirrorWithControl();
        break;
      default: break;
    }
  }

  if (_state != State::MENU) {
    pcb_update();
  }
}

void PcTab::draw() {
  switch (_state) {
    case State::MENU: drawMenu(); break;
    case State::SCREEN: drawScreenMirror(); break;
    case State::SCREEN_CONTROL: drawScreenMirrorControl(); break;
    default: break;
  }
}

void PcTab::drawTitle(const char* text) {
  tft.setFreeFont(&FONT_TITLE);
  tft.setTextColor(COLOR_TEXT, COLOR_BG);
  tft.setTextDatum(TC_DATUM);
  tft.drawString(text, tft.width() / 2, TITLE_Y);
}

void PcTab::drawMenu() {
  tft.fillScreen(COLOR_BG);
  drawTitle("P.C.");

  const char* items[] = { "Screen Mirror", "Controlled S.M." };
  tft.setFreeFont(&FONT_BODY);
  tft.setTextDatum(TL_DATUM);
  for (int i = 0; i < _maxItems; i++) {
    tft.setTextColor(_selected == i ? COLOR_SELECTED : COLOR_TEXT, COLOR_BG);
    tft.drawString(items[i], LABEL_X, ROW_Y[i]);
  }
}

void PcTab::drawScreenMirror() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  tft.setFreeFont(&FONT_BODY);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("Connecting..", tft.width() / 2, tft.height() / 2);
  _pendingStart = PendingStart::MIRROR;
}

void PcTab::drawScreenMirrorControl() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  tft.setFreeFont(&FONT_BODY);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("Connecting..", tft.width() / 2, tft.height() / 2);
  _pendingStart = PendingStart::MIRROR_CTRL;
}

void PcTab::onInput(ButtonID btn, InputEvent evt) {
  if (evt != EVT_PRESSED && evt != EVT_REPEAT) return;
  Serial.printf("A=%d B=%d\n", Input.isDown(BTN_A), Input.isDown(BTN_B));
  if (_todo != PendingStart::NONE) {
    Serial.println("SCREEN MIRRORING");
    if (Input.isDown(BTN_B) && Input.isDown(BTN_A) && isMenuShown == false) {
      isMenuShown = true;
      Serial.println("BOTH PRESSED");
      tft.fillRect(80, 60, 160, 120, TFT_BLACK);
      tft.drawRect(80, 60, 160, 120, TFT_WHITE);
      tft.setTextDatum(MC_DATUM);
      tft.setFreeFont(&FONT_BODY);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.drawString("A: Resume", tft.width() / 2, (tft.height() / 2) - 40);
      tft.drawString("B: EXIT", tft.width() / 2, (tft.height() / 2) + 40);
      return;
    }
    if (isMenuShown == true) {
      if (btn == BTN_B) {
        isMenuShown = false;
        _pendingStart = PendingStart::NONE;
        _todo = PendingStart::NONE;
        _wifiBeginCalled = false;
        _wifiWaitShown = false;
        WiFi.disconnect(true);
        pcb_stop();
        goTo(State::MENU);
      }
      if (btn == BTN_A) {
        isMenuShown = false;
      }
    }

    return;
  }
  if (_state == State::MENU) {
    if (btn == BTN_UP || btn == BTN_DOWN) {
      if (_maxItems == 0) return;
      int prev = _selected;
      if (btn == BTN_DOWN) _selected = (_selected + 1) % _maxItems;
      else _selected = (_selected - 1 + _maxItems) % _maxItems;
      if (prev != _selected) draw();
      return;
    }
  }

  switch (_state) {
    case State::MENU: handleMenuInput(btn, evt); break;
    case State::SCREEN: handleScreenMirrorInput(btn, evt); break;
    case State::SCREEN_CONTROL: handleScreenMirrorControlInput(btn, evt); break;
    default: break;
  }
}

void PcTab::goTo(State s) {
  _state = s;
  draw();
}

void PcTab::handleMenuInput(ButtonID btn, InputEvent evt) {
  if (btn == BTN_B && evt == EVT_PRESSED) {
    exit();
    onExit();
    return;
  }
  if (btn == BTN_A && evt == EVT_PRESSED) goTo((State)(_selected + 1));
}

void PcTab::handleScreenMirrorInput(ButtonID btn, InputEvent evt) {
  if (btn == BTN_B && evt == EVT_PRESSED) {
    pcb_stop();
    goTo(State::MENU);
  }
}

void PcTab::handleScreenMirrorControlInput(ButtonID btn, InputEvent evt) {
  if (btn == BTN_B && evt == EVT_PRESSED) {
    pcb_stop();
    goTo(State::MENU);
  }
}