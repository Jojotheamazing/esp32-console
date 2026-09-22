#pragma once
#include "Scene.h"
#include "display.h"
#include "Preferences.h"

class SettingsTab : public Scene {
public:
  void onEnter() override;
  void onExit() override;
  void update() override;
  void draw() override;
  void onInput(ButtonID btn, InputEvent evt) override;

private:

  enum class State : uint8_t { MENU,
                               DISP,
                               AUDIO,
                               SYSTEM,
                               FILES,
                               JOYSTICKS };



  enum class FilesState : uint8_t { MAIN,
                                    WIFI_AP,
                                    WIFI_STA,
                                    USB };

  static const uint8_t STATE_MAX_ITEMS[];

  State _state = State::MENU;
  FilesState _filesState = FilesState::MAIN;

  int _selected = 0;
  uint8_t _maxItems = 6;

  //int _brightness = 100; //0-100
  int _sleepTimeout = 30;  // seconds  0 = never

  void goTo(State s);

  void drawTitle(const char* text);
  void drawSelector(int row);
  void drawValueBar(int x, int y, int w, int h, int value, int maxVal, uint16_t color = COLOR_SELECTED);

  void drawMenu();
  void drawDisplay();
  void drawAudio();
  //void drawBluetooth();
  void drawSystem();
  void drawFiles();
  void drawJoystickCalibration();

  void redrawDisplayValues();
  void redrawAudioValues();
  void redrawBtStatus();
  void redrawJoysticks();

  void handleJoysticksInput(ButtonID btn, InputEvent evt);
  void handleMenuInput(ButtonID btn, InputEvent evt);
  void handleDisplayInput(ButtonID btn, InputEvent evt);
  void handleAudioInput(ButtonID btn, InputEvent evt);
  //void handleBluetoothInput(ButtonID btn, InputEvent evt);
  void handleSystemInput(ButtonID btn, InputEvent evt);
  void handleFilesInput(ButtonID btn, InputEvent evt);
};