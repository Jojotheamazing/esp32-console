#pragma once

#include "sdCard.h"

// 1 = built in speaker, 2 = Bluetooth
extern int  currentAudioOutput;
extern int  currentVolume;
extern bool isPlaying;
extern bool isPaused;

void changeOutput(int outputInd);
bool playSound(const String &filePath, int32_t timeOffset = -1);
void pauseSound();
void stopSound();
void volumeAdjust(int vol);
void initAudio();
void volumeBarUpdate();