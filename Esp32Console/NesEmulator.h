#pragma once
#include <Arduino.h>

extern bool runningNes;

void launchGame(const char* filepath);
void stopGame();
bool isGameRunning();