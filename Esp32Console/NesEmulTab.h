#pragma once
#include "Scene.h"

class NesEmulTab : public Scene {
public:
  void onEnter() override;
  void onExit() override;
  void draw() override;
  void onInput(ButtonID btn, InputEvent evt) override;
  void update() override;
private:
  int _selectedNesGame = 0;
  static const int MAX_NESGAMES = 20;  // max games
  char _nesgames[MAX_NESGAMES][64];
  int _nesgameCount = 0;
  bool insideNesGame = false;
};