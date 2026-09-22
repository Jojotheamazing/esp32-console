#include "HapticsManager.h"

#define MOTOR_L_PIN  17
#define MOTOR_R_PIN  18

void vibration_init() {
    ledcAttachChannel(MOTOR_L_PIN, 5000, 8, MOTOR_L_CH);
    ledcAttachChannel(MOTOR_R_PIN, 5000, 8, MOTOR_R_CH);
}

void setVibration(uint8_t channel, uint8_t strength) {
    if (channel == MOTOR_BOTH) {
        ledcWriteChannel(MOTOR_L_CH, strength);
        ledcWriteChannel(MOTOR_R_CH, strength);
    } else {
        ledcWriteChannel(channel, strength);
    }
}

void stopVibration(uint8_t channel) {
    setVibration(channel, 0);
}

struct VibChannel {
    const VibStep* steps;
    int step_count;
    int current_step;
    uint32_t step_start_ms;
    bool active;
};

VibChannel vib[2];

void playPattern(uint8_t ch, const VibStep* steps, int count) {
    if (ch == MOTOR_BOTH) {
        playPattern(MOTOR_L_CH, steps, count);
        playPattern(MOTOR_R_CH, steps, count);
        return;
    }
    vib[ch] = { steps, count, 0, millis(), true };
    setVibration(ch, steps[0].strength);
}

void stopPattern(uint8_t ch) {
    vib[ch].active = false;
    stopVibration(ch);
}

void vibration_update() {
    uint32_t now = millis();
    for (int ch = 0; ch < 2; ch++) {
        if (!vib[ch].active) continue;
        uint32_t elapsed = now - vib[ch].step_start_ms;
        if (elapsed >= vib[ch].steps[vib[ch].current_step].duration_ms) {
            vib[ch].current_step++;
            if (vib[ch].current_step >= vib[ch].step_count) {
                stopPattern(ch);
            } else {
                vib[ch].step_start_ms = now;
                setVibration(ch, vib[ch].steps[vib[ch].current_step].strength);
            }
        }
    }
}

const VibStep HIT[]    = { {255, 60} };
const VibStep RUMBLE[] = { {120, 500} };
const VibStep PULSE[]  = { {200, 80}, {0, 60}, {200, 80} };

void vibrate_hit(uint8_t ch)    { playPattern(ch, HIT, 1); }
void vibrate_rumble(uint8_t ch) { playPattern(ch, RUMBLE, 1); }
void vibrate_pulse(uint8_t ch)  { playPattern(ch, PULSE, 3); }
void vibrate_both_hit()         { vibrate_hit(0); vibrate_hit(1); }