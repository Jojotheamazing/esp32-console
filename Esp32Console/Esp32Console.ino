#include <Arduino.h>
#include "display.h"
#include "sdCard.h"
#include "ButtonManager.h"
#include "I2SAudio.h"
#include "WiFiFileServer.h"
#include "AudioHandler.h"
#include "SettingsManager.h"
#include "Mpu6050Handler.h"
#include "LuaEngine.h"
#include "TabManager.h"
#include "WiFiFileServer.h"
#include "JoystickHandler.h"
#include "HapticsManager.h"
#include "PCBridge.h"

void audioTask(void* pvParameters) {
  Serial.println("[Task] I2S Audio Worker Started on Core 0");

  while (1) {

    if (isPlayingI2S()) {
      I2SAudioLoop();

      vTaskDelay(pdMS_TO_TICKS(1));
    } else {
      vTaskDelay(pdMS_TO_TICKS(20));
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.printf("Heap at boot: %u\n", esp_get_free_heap_size());
  delay(1000);
  initTFT();

  while (!initSd()) {
    delay(1000);
    //tft.Print("Sd mount failed!");
  }

  loadSettings();
  Input.begin();
  tabManagerSetup();
  registerCustomLuaFunctions();
  initMPU();
  initAudio();
  vibration_init();
  pcb_init(tft);

  //initI2SAudio();
  delay(1000);
  xTaskCreatePinnedToCore(
    audioTask,
    "audioTask",
    4096,
    NULL,
    1,
    NULL,
    0);


  volumeAdjust(settings.volume);
  //calculateOffsets();
  Serial.printf("Free heap: %u, Max block: %u\n", esp_get_free_heap_size(), heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
  //wfsStart(WfsMode::STA,"Vodafone2025","stelios123");
  //delay(1000);
}

void loop() {
  updateMPU();
  //I2SAudioLoop();
  volumeBarUpdate();
  Input.update();
  tabManagerLoop();
  stepLuaUpdate();
  vibration_update();
  wfsLoop();
  delay(1);
}
