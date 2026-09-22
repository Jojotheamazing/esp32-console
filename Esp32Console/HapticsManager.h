#pragma once
#include <Arduino.h>

#define MOTOR_L_CH  0
#define MOTOR_R_CH  1
#define MOTOR_BOTH   2 

struct VibStep {
    uint8_t  strength;
    uint32_t duration_ms;
};

void vibration_init();
void setVibration(uint8_t channel, uint8_t strength);
void stopVibration(uint8_t channel);


void playPattern(uint8_t ch, const VibStep* steps, int count);
void stopPattern(uint8_t ch);
void vibration_update();

void vibrate_hit(uint8_t ch);
void vibrate_rumble(uint8_t ch);
void vibrate_pulse(uint8_t ch);
void vibrate_both_hit();