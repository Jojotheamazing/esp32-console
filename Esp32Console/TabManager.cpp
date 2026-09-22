// TabManager.cpp
#pragma once
#include "TabManager.h"
#include "ButtonManager.h"
#include "Display.h"
#include "GamesTab.h"
#include "MusicTab.h"
#include "SettingsTab.h"
#include "NesEmulTab.h"
#include "PCTab.h"
#include "JoystickHandler.h"
#include "Preferences.h"
#include "ControlTab.h"

GamesTab gamesTab;
MusicTab musicTab;
SettingsTab settingsTab;
NesEmulTab nesEmulTab;
PcTab pcTab;
ControlTab controlTab;

unsigned long joyLastTime = 0;

static const int TAB_COUNT = 6;
static int currentTab = 0;

static Tab tabs[TAB_COUNT] = {
  { "Games", "/Assets/UIImages/games.bmp", &gamesTab },
  { "Music", "/Assets/UIImages/music.bmp", &musicTab },
  { "Settings", "/Assets/UIImages/settings.bmp", &settingsTab },
  { "NES", "/Assets/UIImages/nesEmul.bmp", &nesEmulTab },
  { "PC", "/Assets/UIImages/pc.bmp", &pcTab },
  { "Control", "/Assets/UIImages/control.bmp", &controlTab }
};


static void drawPreview() {
  tft.fillScreen(COLOR_BG);

  int16_t imgW = 128;
  int16_t imgH = 128;
  int16_t imgX = (tft.width() - imgW) / 2;
  int16_t imgY = (tft.height() - imgH) / 2 + 10;

  tft.setTextColor(COLOR_TEXT, COLOR_BG);
  tft.setFreeFont(&FONT_SMALL);


  tft.setTextSize(1);

  tft.setTextDatum(TL_DATUM);
  tft.drawString(tabs[(currentTab - 1 + TAB_COUNT) % TAB_COUNT].name, 0, 5);
  tft.setTextDatum(TR_DATUM);
  tft.drawString(tabs[(currentTab + 1) % TAB_COUNT].name, tft.width(), 5);

  tft.setFreeFont(&FONT_BODY);
  String text = String(tabs[(currentTab - 1 + TAB_COUNT) % TAB_COUNT].name) + "  >" + tabs[currentTab].name + "<  " + tabs[(currentTab + 1) % TAB_COUNT].name;
  //tft.setTextColor(TFT_BLUE);
  tft.setTextDatum(TC_DATUM);
  tft.drawString(String(">") + tabs[currentTab].name + "<", tft.width() / 2, 10);
  //preview image
  //drawJpg(tabs[currentTab].imagePath, imgX, imgY);

  drawBmpTransparent(tabs[currentTab].imagePath, imgX, imgY, TFT_BLACK);
  tft.setTextDatum(BL_DATUM);

  tft.setFreeFont(&FF21);
  tft.drawString("[A] Select", 0, tft.height());
}


static void onInput(ButtonID btn, InputEvent evt) {
  Serial.println(btn);
  Scene* scene = tabs[currentTab].scene;
  if (scene == &controlTab && scene->isInside() && evt == EVT_RELEASED) {
    scene->onInput(btn, evt);
    return;
  }
  if (evt != EVT_PRESSED && evt != EVT_REPEAT) return;
  //joyLastTime = millis();

  if (!scene->isInside()) {
    if (btn == BTN_RIGHT) {
      currentTab = (currentTab + 1) % TAB_COUNT;
      drawPreview();
    } else if (btn == BTN_LEFT) {
      currentTab = (currentTab - 1 + TAB_COUNT) % TAB_COUNT;
      drawPreview();
    } else if (btn == BTN_A) {
      Serial.printf("Enter");
      scene->enter();
      scene->onEnter();
    }
  } else {
    scene->onInput(btn, evt);
    if (!scene->isInside()) {
      drawPreview();
    }
  }
}
static void dummyInput(ButtonID btn, InputEvent evt) {}

void tabManagerSetup() {
  Input.addListener(onInput);
  //volatile InputCallback unused = onInput;
  //Input.addListener(dummyInput);
  drawPreview();
}

void tabManagerLoop() {
  /*if ((millis() - joyLastTime) > 300) {
    if (getLX() > 20) { onInput(BTN_RIGHT, EVT_REPEAT); }
    if (getLX() < -20) { onInput(BTN_LEFT, EVT_REPEAT); }
    if (getLY() > 20) { onInput(BTN_UP, EVT_REPEAT); }
    if (getLY() < -20) { onInput(BTN_DOWN, EVT_REPEAT); }
  }*/


  Scene* scene = tabs[currentTab].scene;
  scene->update();
}