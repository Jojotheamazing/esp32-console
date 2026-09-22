#include "sdCard.h"
#include <Arduino.h>

#define SD_SCK 41
#define SD_MISO 40
#define SD_MOSI 39
#define SD_CS 38

SPIClass  sdSPI(FSPI);
bool sdReady = false;

bool initSd() {
  sdSPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  if (!SD.begin(SD_CS, sdSPI, 40000000)) {
    Serial.println("SD Card failed!");
    sdReady = false;
    return false;
  }
  Serial.println("SD Card ready!");
  sdReady = true;
  return true;
}

int loadFileNames(const char* folderPath, char names[][64], int maxCount, bool foldersOnly) {
  if (!sdReady) return 0;

  File dir = SD.open(folderPath);
  if (!dir) {
    Serial.printf("[SD] Failed to open folder: %s\n", folderPath);
    return 0;
  }

  const char* skipFiles[] = { "info.json", "cover.jpg", "cover.jpeg" };
  const int skipCount = sizeof(skipFiles) / sizeof(skipFiles[0]);

  int count = 0;
  while (count < maxCount) {
    File f = dir.openNextFile();
    if (!f) break;

    const char* fileName = f.name();
    bool shouldSkip = false;

    for (int i = 0; i < skipCount; i++) {
      if (strcmp(fileName, skipFiles[i]) == 0) {
        shouldSkip = true;
        break;
      }
    }

    if (!shouldSkip) {
      const char* ext = strstr(fileName, ".sav");
      if (ext && strcmp(ext, ".sav") == 0) {
        shouldSkip = true;
      }
    }

    if (!shouldSkip) {
      bool isDir = f.isDirectory();
      if (foldersOnly ? isDir : !isDir) {
        strncpy(names[count], fileName, 63);
        names[count][63] = '\0';
        //Serial.printf("[SD] Loaded: %s\n", names[count]);
        count++;
      }
    }
    f.close();
  }
  dir.close();
  Serial.printf("[SD] Total loaded from %s: %d\n", folderPath, count);
  return count;
}


uint32_t getWavDurationMs(const char* path) {
  File file = SD.open(path);
  if (!file) {
    Serial.println("Failed to open WAV");
    return 0;
  }

  char id[4];

  file.readBytes(id, 4);
  if (strncmp(id, "RIFF", 4) != 0) {
    Serial.println("Not RIFF");
    file.close();
    return 0;
  }

  file.seek(22);

  uint16_t channels;
  file.read((uint8_t*)&channels, 2);

  uint32_t sampleRate;
  file.read((uint8_t*)&sampleRate, 4);

  file.seek(34);

  uint16_t bitsPerSample;
  file.read((uint8_t*)&bitsPerSample, 2);

  file.seek(12);

  uint32_t dataSize = 0;

  while (file.available() > 8) {

    char chunkId[4];
    file.readBytes(chunkId, 4);

    uint32_t chunkSize;
    file.read((uint8_t*)&chunkSize, 4);

    Serial.print("Chunk: ");
    Serial.print(chunkId[0]);
    Serial.print(chunkId[1]);
    Serial.print(chunkId[2]);
    Serial.print(chunkId[3]);
    Serial.print(" Size: ");
    Serial.println(chunkSize);

    if (strncmp(chunkId, "data", 4) == 0) {
      dataSize = chunkSize;
      break;
    }

    file.seek(file.position() + chunkSize + (chunkSize & 1));
  }

  file.close();

  Serial.println("---- FINAL WAV INFO ----");
  Serial.print("Channels: ");
  Serial.println(channels);
  Serial.print("SampleRate: ");
  Serial.println(sampleRate);
  Serial.print("BitsPerSample: ");
  Serial.println(bitsPerSample);
  Serial.print("DataSize: ");
  Serial.println(dataSize);

  if (dataSize == 0 || sampleRate == 0 || channels == 0 || bitsPerSample == 0) {
    Serial.println("Invalid WAV parsed");
    return 0;
  }

  uint32_t byteRate =
    sampleRate * channels * (bitsPerSample / 8);

  if (byteRate == 0) return 0;

  uint32_t durationMs = (uint64_t)dataSize * 1000 / byteRate;

  Serial.print("Duration ms: ");
  Serial.println(durationMs);

  return durationMs;
}