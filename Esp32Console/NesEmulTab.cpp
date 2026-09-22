// NesEmulTab.cpp
#include <Arduino.h>
#include "NesEmulTab.h"
#include "ButtonManager.h"
#include "sdCard.h"
#include "display.h"
#include "MyFonts.h"
#include "TabManager.h"
#include "Preferences.h"
#include "NesEmulator.h"

String stripExtension1(const char* filename) {
  String s = String(filename);
  int dot = s.lastIndexOf('.');
  return dot >= 0 ? s.substring(0, dot) : s;
}

void NesEmulTab::draw() {
  tft.fillScreen(COLOR_BG);
  const int maxVisible = 5;

  const int listYOffset = 70;
  const int itemHeight = (tft.height() - 60) / maxVisible;

  int scrollOffset = 0;
  if (_selectedNesGame >= maxVisible) scrollOffset = _selectedNesGame - maxVisible + 1;
  int displayStart = scrollOffset;
  int displayEnd = min(scrollOffset + maxVisible, _nesgameCount);

  tft.setFreeFont(&FONT_TITLE);
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(COLOR_TEXT);
  tft.drawString("NES GAMES", tft.width() / 2, 10);

  for (int i = displayStart; i < displayEnd; i++) {
    int screenIndex = i - scrollOffset;
    int yPos = listYOffset + itemHeight * screenIndex;
    bool isSelected = (i == _selectedNesGame);
    tft.setCursor(10, yPos);
    tft.setFreeFont(&FONT_BODY);
    tft.setTextColor(isSelected ? COLOR_SELECTED : COLOR_TEXT);
    tft.print(String(i + 1) + "." + stripExtension1(_nesgames[i]));
  }

  if (scrollOffset > 0) {
    tft.fillTriangle(
      tft.width() - 20, 15,
      tft.width() - 10, 15,
      tft.width() - 15, 5,
      COLOR_HINT);
  }
  if (displayEnd < _nesgameCount) {
    int downY = listYOffset + maxVisible * itemHeight;
    tft.fillTriangle(
      tft.width() - 20, tft.height() - 15,
      tft.width() - 10, tft.height() - 15,
      tft.width() - 15, tft.height() - 5,
      COLOR_HINT);
  }
  Serial.printf("[NES] draw — selected: %s\n", _nesgames[_selectedNesGame]);
}


void NesEmulTab::onInput(ButtonID btn, InputEvent evt) {
  if (evt != EVT_PRESSED && evt != EVT_REPEAT) return;
  if (runningNes == true) return;
  if (_nesgameCount == 0 && btn != BTN_B) return;

  if (btn == BTN_DOWN) {
    _selectedNesGame = (_selectedNesGame + 1) % _nesgameCount;
    draw();  //only redraws when something actually changed
  } else if (btn == BTN_UP) {
    _selectedNesGame = (_selectedNesGame - 1 + _nesgameCount) % _nesgameCount;
    draw();
  } else if (btn == BTN_A) {
    //launch game
    char path[128];
    snprintf(path, sizeof(path), "/nesGames/%s", _nesgames[_selectedNesGame]);
    launchGame(path);
    if (isGameRunning()) {
      runningNes = true;
    }
  } else if (btn == BTN_B && evt == EVT_PRESSED) {
    exit();
    onExit();
  }
}

void NesEmulTab::onEnter() {
  _selectedNesGame = 0;
  _nesgameCount = loadFileNames("/nesGames", _nesgames, MAX_NESGAMES, false);
  Serial.println(_nesgameCount);
  if (_nesgameCount == 0) {
    tft.setFreeFont(&FONT_TITLE);
    tft.setTextDatum(TC_DATUM);
    tft.setTextColor(COLOR_TEXT);
    tft.drawString("NES GAMES", tft.width() / 2, 10);
    tft.setTextColor(COLOR_DANGER);
    tft.setFreeFont(&FONT_BODY);
    tft.drawString("No games found in /nesGames", tft.width() / 2, 80);
  }
  draw();
  Serial.println("[NES] entered");
}

void NesEmulTab::onExit() {
  Serial.println("[NES] exited");
}

void NesEmulTab::update() {}
