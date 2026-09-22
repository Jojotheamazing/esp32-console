#pragma once
#include "Scene.h"
#include "display.h"
#include "Preferences.h"

class ControlTab : public Scene {
public:
  void onEnter() override;
  void onExit() override;
  void update() override;
  void draw() override;
  void onInput(ButtonID btn, InputEvent evt) override;

private:

  enum class State : uint8_t { MENU,
                               GAMEPAD,
                               STEERING_MODE };


  State _state = State::MENU;

  int _selected = 0;
  uint8_t _maxItems = 2;

  void goTo(State s);

  //void drawTitle(const char* text);

  void drawMenu();
  void drawGamepad();
  void drawSteering();
  void redrawSteering(float steerValue, int16_t yValue);
  void startGamepad();
  void startSteering();
  //void redrawGamepad();
  void handleGamepadInput(ButtonID btn, InputEvent evt);
  void handleMenuInput(ButtonID btn, InputEvent evt);
  void handleSteeringInput(ButtonID btn, InputEvent evt);
};