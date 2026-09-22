#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "MyFonts.h"

extern SemaphoreHandle_t tftMutex;

void initTFT();
void flashColors();
//void drawBmpFast(const char* filename, int16_t x = 0, int16_t y = 0);
void drawBmp(const char* filename, int16_t x = 0, int16_t y = 0);
void drawBmpTransparent(const char* filename, int16_t x = 0, int16_t y = 0, uint16_t transparentColor = 0xF81F);  // 0xF81F is magenta
void drawJpg(const char* filename, int16_t x = 0, int16_t y = 0);

void drawBmpRegion(const char* filename, int16_t srcX, int16_t srcY,
                   int16_t w, int16_t h, int16_t dstX, int16_t dstY);


void drawBmpRegion(const char* filename, int16_t srcX, int16_t srcY,
                   int16_t w, int16_t h, int16_t dstX, int16_t dstY);

void saveRegion(const char* name, int16_t x, int16_t y, int16_t w, int16_t h);
void restoreRegion(const char* name, int16_t x, int16_t y);
void freeRegion(const char* name);
void freeAllRegions();

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap);

extern TFT_eSPI tft;
