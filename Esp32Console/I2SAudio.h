#pragma once

void playI2S(const char* filename,int32_t fileStartTime = -1);
void stopI2S();
void pauseI2S();

bool isPlayingI2S();
uint32_t getAudioDurationI2S();
uint32_t getAudioPos();
void adjustI2SVolume(int volume);

void initI2SAudio();
void deinitI2SAudio();
void I2SAudioLoop();
