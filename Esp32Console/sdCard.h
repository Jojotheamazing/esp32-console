#pragma once
#include <SPI.h>
#include <SD.h>

extern SPIClass fspi;
extern bool sdReady;

bool initSd();
int loadFileNames(const char* folderPath, char names[][64], int maxCount, bool foldersOnly = false);
uint32_t getWavDurationMs(const char* path);