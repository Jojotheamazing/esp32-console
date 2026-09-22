#pragma once
#include "Scene.h"

class GamesTab : public Scene {
public:
  void onEnter() override;
  void onExit() override;
  void draw() override;
  void onInput(ButtonID btn, InputEvent evt) override;
  void update() override;
  void redrawGameSelect() ;
private:
  int _selectedGame = 0;
  static const int MAX_GAMES = 20;  // max games 
  char _games[MAX_GAMES][64];       // 64 chars per name
  int _gameCount = 0;               // how many games loaded
  bool insideGame = false;
};