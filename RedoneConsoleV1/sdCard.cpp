#include <SPI.h>
#include <SD.h>

#define SD_SCK 14
#define SD_MISO 12
#define SD_MOSI 13
#define SD_CS 15

SPIClass hspi(HSPI);

bool initSd() {
  hspi.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  if (!SD.begin(SD_CS, hspi)) {
    Serial.println("SD Card failed!");
    return false;
  }
  Serial.println("SD Card ready!");
  return true;
}