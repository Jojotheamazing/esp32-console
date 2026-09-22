#pragma once
#include "Scene.h"
#include "display.h"
#include "Preferences.h"

class PcTab : public Scene {
public:
  void onEnter() override;
  void onExit() override;
  void update() override;
  void draw() override;
  void onInput(ButtonID btn, InputEvent evt) override;

private:

  enum class State : uint8_t {
    MENU,
    SCREEN,
    SCREEN_CONTROL
  };

  enum class PendingStart : uint8_t {
    NONE,
    MIRROR,
    MIRROR_CTRL
  };

  State        _state        = State::MENU;
  PendingStart _pendingStart = PendingStart::NONE;
  PendingStart _todo = PcTab::PendingStart::NONE;

  bool     _wifiBeginCalled  = false;
  bool     _wifiWaitShown    = false;
  uint32_t _wifiConnectStart = 0;

  int     _selected  = 0;
  uint8_t _maxItems  = 2;

  void goTo(State s);

  void drawTitle(const char* text);
  void drawMenu();
  void drawScreenMirror();
  void drawScreenMirrorControl();

  void handleMenuInput(ButtonID btn, InputEvent evt);
  void handleScreenMirrorInput(ButtonID btn, InputEvent evt);
  void handleScreenMirrorControlInput(ButtonID btn, InputEvent evt);
};