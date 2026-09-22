#include "NesEmulator.h"
#include <Arduino.h>
#include "SdCard.h"
#include "Display.h"
#include "ButtonManager.h"
#include "I2SAudio.h"
#include <esp_heap_caps.h>
#include "hw_config.h"
#include "NesEmulTab.h"
#include "SettingsManager.h"
extern NesEmulTab nesEmulTab;
extern TFT_eSPI tft;
extern void setup_controller();
bool runningNes = false;

static TaskHandle_t emuTaskHandle = NULL;

extern "C" {
#include "osd.h"
#include "nofrendo.h"
}


volatile bool game_is_running = false;

static void emu_task(void* pvParameters) {
  const char* rom_path = (const char*)pvParameters;

  runningNes = true;
  nes_launch_game(rom_path, ENABLE_SOUND,settings.volume);

  osd_shutdown();
  delay(50);
  runningNes = false;
  Serial.println("[Task] Core engine shut down safely. Cleaning up task allocations...");


  initI2SAudio();
  nesEmulTab.draw();
  emuTaskHandle = NULL;
  vTaskDelete(NULL);
}

void launchGame(const char* filepath) {
  if (emuTaskHandle == NULL) {

    deinitI2SAudio();
    delay(50);

    tft.fillScreen(TFT_BLACK);

    xTaskCreatePinnedToCore(
      emu_task,
      "EmuTask",
      49152, // 48KB allocation
      (void*)filepath,
      1,
      &emuTaskHandle,
      0
    );
  } else {
    Serial.println("Error: A game instance is already running!");
  }
}
void stopGame() {
  if (emuTaskHandle != NULL) {
    nes_stop_game();
  }
}

bool isGameRunning() {
  return (emuTaskHandle != NULL);
}
