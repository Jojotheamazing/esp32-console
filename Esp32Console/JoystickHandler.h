#pragma once
#include <Arduino.h>

//struct fot processed joystick data
struct JoystickData {
    int x;
    int y;
};


//void initJoysticks(int maxRange = 100);
void updateJoysticks(); 
void calculateOffsets();
int getLX();
int getLY();


int getRX();
int getRY();

//configurations
void setDeadzone(int dz);
void setMaxValue(int maxVal);