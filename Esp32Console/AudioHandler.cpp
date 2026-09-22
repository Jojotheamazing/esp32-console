#include "esp32-hal.h"
#include "AudioHandler.h"
#include "I2SAudio.h"
#include "osd.h"
#include "SettingsManager.h"
#include "ButtonManager.h"
#include "display.h"
#include "SpriteManager.h"
#include "Preferences.h"

int currentAudioOutput = 1; // 1 = speaker, 2 = bt
int currentVolume = 30;// 0-100
bool isPlaying = false; //note to self to add those and remove them from bluetooth
bool isPaused = false;

void changeOutput(int outputInd) {
  if (outputInd == currentAudioOutput) return;
  stopSound();
  currentAudioOutput = outputInd;
  Serial.printf("[Audio] Output -> %s\n", outputInd == 2 ? "Bluetooth" : "Speaker");
}

bool playSound(const String& filePath, int32_t timeOffset) {
  if (currentAudioOutput == 1) {
    playI2S(filePath.c_str(), timeOffset);
  }
  return false;
}

void pauseSound() {
  if (currentAudioOutput == 1) {
    pauseI2S();
  }
  isPaused = !isPaused;
}

void stopSound() {
  if (currentAudioOutput == 1) {
    stopI2S();
  }
  isPlaying = false;
  isPaused = false;
}

void volumeAdjust(int vol) {
  currentVolume = constrain(vol, 0, 100);
  adjustI2SVolume(currentVolume);
  nes_set_volume(currentVolume);
}

bool volumeBarVisible = false;
uint32_t lastVolBar = millis();

void drawVolumeBar() {

  TFT_eSprite* volumebar = getCanvas("VolumeBar");
  if (!volumebar) return;

  volumebar->fillRect(12, 1, 9, 104, COLOR_HINT);
  volumebar->fillRect(14, 100 - settings.volume + 3, 5, settings.volume, COLOR_SELECTED);
  String volText = String(settings.volume);// + "%";
  drawTextTo(volText.c_str(), 0, 108, TFT_WHITE, TFT_BLACK, &FONT_SMALL, TL_DATUM, volumebar);

  if (xSemaphoreTake(tftMutex, portMAX_DELAY) == pdTRUE) {
    if (!volumeBarVisible) {
      saveRegion("volBarBG", 0, 67, 32, 133);
    }
    lastVolBar = millis();
    pushCanvas("VolumeBar", 0, 67, false);
    volumeBarVisible = true;
    xSemaphoreGive(tftMutex);
  }
}

void volumeBarUpdate() {
  if (volumeBarVisible && (millis() - lastVolBar) > 2000) {
    if (xSemaphoreTake(tftMutex, portMAX_DELAY) == pdTRUE) {
      volumeBarVisible = false;
      restoreRegion("volBarBG", 0, 67);
      freeRegion("volBarBG");
      xSemaphoreGive(tftMutex);
    }
    saveSettings(); 
  }
}

void onAudioInput(ButtonID btn, InputEvent evt) {
  if (evt != EVT_PRESSED && evt != EVT_REPEAT) return;

  if (btn == BTN_VOL_UP) {
    settings.volume = min(100, settings.volume + 4);
    volumeAdjust(settings.volume);
    drawVolumeBar();
    
  }
  if (btn == BTN_VOL_DOWN) {
    settings.volume = max(0, settings.volume - 4);
    volumeAdjust(settings.volume);
    drawVolumeBar();
  }
}

void initAudio() {
  Input.addListener(onAudioInput);
  initI2SAudio();
  createCanvas("VolumeBar", 32, 133, TFT_TRANSPARENT);
}