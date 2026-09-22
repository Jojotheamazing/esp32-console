#include <Arduino.h>
#include "GamesTab.h"
#include "ButtonManager.h"
#include "sdCard.h"
#include "display.h"
#include "MyFonts.h"
#include "TabManager.h"
#include "LuaEngine.h"
#include "Preferences.h"
#include <ArduinoJson.h>

void GamesTab::redrawGameSelect() {
  tft.fillRect(0, 32, 310, 60, TFT_BLACK);
  tft.fillRect(0, 93, 310, 60, TFT_BLACK);
  tft.fillRect(0, 155, 310, 60, TFT_BLACK);
  tft.fillRect(310, 28, 10, 190, TFT_BLACK);
  tft.fillRect(275, 218, 45, 22, TFT_BLACK);

  tft.setTextColor(COLOR_TEXT);
  tft.setFreeFont(&FF17);
  tft.setTextDatum(BR_DATUM);
  tft.drawString(String(_selectedGame + 1) + "/" + String(_gameCount), 320, 240);

  const int maxVisible = 3;
  const int totalSliderLength = 183;

  const int listYOffset = 40;
  const int itemHeight = 62;  //(tft.height() - 60) / maxVisible;

  int scrollOffset = 0;
  if (_selectedGame >= maxVisible) scrollOffset = _selectedGame - maxVisible + 1;
  int displayStart = scrollOffset;
  int displayEnd = min(scrollOffset + maxVisible, _gameCount);

  for (int i = displayStart; i < displayEnd; i++) {
    int screenIndex = i - scrollOffset;
    int yPos = listYOffset + itemHeight * screenIndex;
    bool isSelected = (i == _selectedGame);

    tft.setTextDatum(TL_DATUM);
    tft.setFreeFont(&FF22);
    tft.setTextColor(COLOR_TEXT);
    tft.drawString(String(_games[i]), 60, yPos);

    String iconPathStr = "/luaGames/" + String(_games[i]) + "Icon.bmp";
    const char* iconPath = iconPathStr.c_str();

    drawBmp(SD.exists(iconPath) ? iconPath : "/Assets/UIImages/GamesTab/NoIcon.bmp", 11, 40 + screenIndex * itemHeight);

    String jsonPathStr = "/luaGames/" + String(_games[i]) + "/meta.json";
    File metaFile = SD.open(jsonPathStr.c_str(), FILE_READ);

    if (metaFile) {
      StaticJsonDocument<512> doc;
      DeserializationError error = deserializeJson(doc, metaFile);
      metaFile.close();

      if (!error) {
        const char* authorName = doc["author"] | "Unknown";

        tft.setFreeFont(&FF17);
        tft.drawString("By: " + String(authorName), 60, yPos + 28);
        JsonArray tags = doc["tags"];
        int tagCount = 0;

        for (JsonVariant tag : tags) {
          if (tagCount >= 4) break;

          const char* tagStr = tag.as<const char*>();
          String tagImgPath = "/Assets/UIImages/GamesTab/" + String(tagStr) + ".bmp";

          if (SD.exists(tagImgPath.c_str())) {
            int col = tagCount % 2;
            int row = tagCount / 2;

            int iconX = 260 + (col * 25);
            int iconY = 44 + (row * 22) + (screenIndex * itemHeight);

            drawBmp(tagImgPath.c_str(), iconX, iconY);
            tagCount++;
          }
        }
      }
    }

    if (isSelected) {
      tft.drawRoundRect(4, 32 + screenIndex * itemHeight, 302, 58, 6, 0xc53f);
      tft.drawRoundRect(5, 33 + screenIndex * itemHeight, 300, 56, 6, 0xc53f);
      tft.drawRoundRect(6, 34 + screenIndex * itemHeight, 298, 54, 6, 0x9b9c);
    }
  }

  if (_gameCount > maxVisible) {
    int sliderLength = (totalSliderLength * maxVisible) / _gameCount;

    if (sliderLength < 12) sliderLength = 12;

    int topDisplayedGame = _selectedGame - (maxVisible / 2);

    int maxScrollIndex = _gameCount - maxVisible;
    int currentScrollOffset = _selectedGame;
    if (currentScrollOffset > maxScrollIndex) currentScrollOffset = maxScrollIndex;
    if (currentScrollOffset < 0) currentScrollOffset = 0;

    int travelRange = totalSliderLength - sliderLength;

    int scrollY = 30 + (currentScrollOffset * travelRange) / maxScrollIndex;

    tft.fillRoundRect(311, 31, 7, totalSliderLength, 8, TFT_DARKGREY);
    tft.fillRoundRect(309, scrollY, 11, sliderLength, 8, 0xc53f);
    tft.fillRoundRect(311, scrollY + 2, 7, sliderLength - 4, 8, 0x9b9c);
  }

  Serial.printf("[Games] draw — selected: %s\n", _games[_selectedGame]);
}

void GamesTab::draw() {
  tft.fillScreen(COLOR_BG);
  /*const int maxVisible = 5;

  const int listYOffset = 70;  //space for the "games"
  const int itemHeight = (tft.height() - 60) / maxVisible;
  
  int scrollOffset = 0;
  if (_selectedGame >= maxVisible) scrollOffset = _selectedGame - maxVisible + 1;
  int displayStart = scrollOffset;
  int displayEnd = min(scrollOffset + maxVisible, _gameCount);

  tft.setFreeFont(&FONT_TITLE);
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(COLOR_TEXT);
  tft.drawString("GAMES", tft.width() / 2, 10);

  for (int i = displayStart; i < displayEnd; i++) {
    int screenIndex = i - scrollOffset;
    int yPos = listYOffset + itemHeight * screenIndex;
    bool isSelected = (i == _selectedGame);
    tft.setCursor(10, yPos);
    tft.setFreeFont(&FONT_BODY);
    tft.setTextColor(isSelected ? COLOR_SELECTED : COLOR_TEXT);
    tft.print(String(i + 1) + "." + String(_games[i]));
  }

  if (scrollOffset > 0) {
    tft.fillTriangle(
      tft.width() - 20, 15,
      tft.width() - 10, 15,
      tft.width() - 15, 5, 
      COLOR_HINT);
  }
  if (displayEnd < _gameCount) {
    int downY = listYOffset + maxVisible * itemHeight;
    tft.fillTriangle(
      tft.width() - 20, tft.height() - 15,
      tft.width() - 10, tft.height() - 15, 
      tft.width() - 15, tft.height() - 5,   
      COLOR_HINT);
  }
  Serial.printf("[Games] draw — selected: %s\n", _games[_selectedGame]);*/

  tft.setTextDatum(TL_DATUM);
  //tft.setFreeFont(&FONT_TITLE);
  tft.setTextColor(0xc53f);
  tft.setFreeFont(&FF23);
  tft.drawString("GAMES: " + String(_gameCount), 0, 0);

  tft.drawLine(0, 30, 310, 30, 0x6275);
  tft.drawLine(0, 92, 310, 92, 0x6275);
  tft.drawLine(0, 154, 310, 154, 0x6275);
  tft.drawLine(0, 216, 310, 216, 0x6275);

  tft.setTextDatum(BL_DATUM);
  //tft.setFreeFont(&FONT_TITLE);
  tft.setTextColor(COLOR_TEXT);
  tft.setFreeFont(&FF17);
  tft.drawString("SELECT: (A)  BACK:(B)", 0, 240);
  tft.setTextDatum(BR_DATUM);
  tft.drawString(String(_selectedGame + 1) + "/" + String(_gameCount), 320, 240);
  redrawGameSelect();
}




// GamesTab.cpp
void GamesTab::onInput(ButtonID btn, InputEvent evt) {
  if (evt != EVT_PRESSED && evt != EVT_REPEAT) return;
  if (runningLua == true) return;

  if (btn == BTN_DOWN) {
    _selectedGame = (_selectedGame + 1) % _gameCount;
    redrawGameSelect();  // only redraws when something actually changed
  } else if (btn == BTN_UP) {
    _selectedGame = (_selectedGame - 1 + _gameCount) % _gameCount;
    redrawGameSelect();
  } else if (btn == BTN_A) {
    // launch game
    char path[128];
    snprintf(path, sizeof(path), "/luaGames/%s/main.lua", _games[_selectedGame]);
    if (runLuaScript(path)) {
      //insideGame = true;
    }
  } else if (btn == BTN_B && evt == EVT_PRESSED) {
    exit();
    onExit();
  }
}

void GamesTab::onEnter() {
  _selectedGame = 0;
  _gameCount = loadFileNames("/luaGames", _games, MAX_GAMES, true);
  draw();
  Serial.println("[Games] entered");
}

void GamesTab::onExit() {
  Serial.println("[Games] exited");
  //drawPreview();
}

void GamesTab::update() {}
