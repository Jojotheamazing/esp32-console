#include "Arduino.h"
#include "Audio.h"
#include "sdCard.h"
#include "I2SAudio.h"
#include "SettingsManager.h"

#define I2S_BCLK 4
#define I2S_LRC 5
#define I2S_DOUT 6

Audio* audio = nullptr;

void my_audio_info(Audio::msg_t m) {
  Serial.printf("%s: %s\n", m.s, m.msg);
}

void initI2SAudio() {
  if (audio == nullptr) {
    Audio::audio_info_callback = my_audio_info;
    audio = new Audio(); 
    audio->setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    adjustI2SVolume(settings.volume);
    Serial.println("[Audio] System audio engine allocated successfully.");
  }
}

void deinitI2SAudio() {
  if (audio != nullptr) {
    delete audio;
    audio = nullptr;
    Serial.println("[Audio] System audio engine released completely.");
  }
}

void playI2S(const char* filename, int32_t fileStartTime) {
  if (audio) audio->connecttoFS(SD, filename, fileStartTime);
}

void stopI2S() {
  if (audio) audio->stopSong();
}

void pauseI2S() {
  if (audio) audio->pauseResume();
}

bool isPlayingI2S() {
  return audio ? audio->isRunning() : false;
}

uint32_t getAudioDurationI2S() {
  return audio ? audio->getAudioFileDuration() : 0;
}

uint32_t getAudioPos() {
  return audio ? audio->getAudioCurrentTime() : 0;
}

void adjustI2SVolume(int volume) {
  if (audio) audio->setVolume(map(volume, 0, 100, 0, 21));
}

void I2SAudioLoop() {
  if (audio) audio->loop();
}