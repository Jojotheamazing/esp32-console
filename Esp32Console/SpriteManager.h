// SpriteManager.h
#pragma once
#include <TFT_eSPI.h>
#include <SD.h>
#include "display.h"

#define MAX_SPRITES 20

struct Sprite {
  TFT_eSprite* spr = nullptr;
  char name[32] = {};
  int16_t w = 0, h = 0;
  bool loaded = false;
};

bool loadSprite(const char* name, const char* path);
void drawSprite(const char* name, int16_t x, int16_t y, TFT_eSprite* target = nullptr, uint16_t transparent = TFT_TRANSPARENT);
void freeSprite(const char* name);
void freeAllSprites();
void drawSpriteRotated(const char* name, int16_t x, int16_t y, float angle, uint16_t transparent, TFT_eSprite* target = nullptr);
TFT_eSprite* getSprite(const char* name);

#define MAX_CANVASES 20

struct Canvas {
  char name[32] = {};
  TFT_eSprite* spr = nullptr;
  uint16_t w = 0, h = 0;
  uint16_t bgColor = 0;
  bool loaded = false;
};

bool createCanvas(const char* name, uint16_t w, uint16_t h, uint16_t bgColor);
void pushCanvas(const char* name, uint16_t x, uint16_t y, bool centered = true);
void clearCanvas(const char* name);
void deleteCanvas(const char* name);
void deleteAllCanvases();  // note to self dont pass to lua never mind pass if needed
void drawTextTo(const char* text, int16_t x, int16_t y, uint16_t color, uint16_t bg,
                const GFXfont* font, uint8_t datum, TFT_eSprite* target = nullptr);
TFT_eSprite* getCanvas(const char* name);
