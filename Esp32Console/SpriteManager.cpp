// SpriteManager.cpp
#include "SpriteManager.h"
#include "display.h"

static Sprite _sprites[MAX_SPRITES];

static int findSprite(const char* name) {
  for (int i = 0; i < MAX_SPRITES; i++)
    if (_sprites[i].loaded && strcmp(_sprites[i].name, name) == 0)
      return i;
  return -1;
}

static int freeSlot() {
  for (int i = 0; i < MAX_SPRITES; i++)
    if (!_sprites[i].loaded) return i;
  return -1;
}

bool loadSprite(const char* name, const char* path) {
  if (findSprite(name) >= 0) {
    Serial.printf("[Sprite] '%s' already loaded\n", name);
    return true;
  }

  int slot = freeSlot();
  if (slot < 0) {
    Serial.println("[Sprite] No free slots");
    return false;
  }

  // open BMP
  File f = SD.open(path);
  if (!f) {
    Serial.printf("[Sprite] Cannot open: %s\n", path);
    return false;
  }
  uint16_t sig = f.read() | (f.read() << 8);
  if (sig != 0x4D42) {
    Serial.println("[Sprite] Not a BMP");
    f.close();
    return false;
  }

  f.seek(10);
  uint32_t dataOffset = f.read() | (f.read() << 8) | (f.read() << 16) | (f.read() << 24);
  f.seek(18);
  uint32_t width = f.read() | (f.read() << 8) | (f.read() << 16) | (f.read() << 24);
  uint32_t height = f.read() | (f.read() << 8) | (f.read() << 16) | (f.read() << 24);
  f.seek(28);
  uint16_t depth = f.read() | (f.read() << 8);

  if (depth != 24) {
    Serial.println("[Sprite] Only 24-bit BMP supported");
    f.close();
    return false;
  }

  TFT_eSprite* spr = new TFT_eSprite(&tft);
  if (!spr->createSprite(width, height)) {
    Serial.printf("[Sprite] Not enough RAM for %dx%d\n", width, height);
    delete spr;
    f.close();
    return false;
  }

  uint16_t padding = (4 - ((width * 3) & 3)) & 3;
  uint8_t lineBuffer[width * 3];

  f.seek(dataOffset);

  for (int row = height - 1; row >= 0; row--) {
    f.read(lineBuffer, width * 3);
    uint8_t* ptr = lineBuffer;
    for (uint32_t col = 0; col < width; col++) {
      uint8_t b = *ptr++;
      uint8_t g = *ptr++;
      uint8_t r = *ptr++;
      uint16_t color = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
      spr->drawPixel(col, row, color);
    }
    if (padding) f.seek(f.position() + padding);
  }
  f.close();

  // store in slot
  _sprites[slot].spr = spr;
  _sprites[slot].w = width;
  _sprites[slot].h = height;
  _sprites[slot].loaded = true;
  strncpy(_sprites[slot].name, name, 31);

  Serial.printf("[Sprite] Loaded '%s' (%dx%d) into slot %d\n", name, width, height, slot);
  return true;
}

void drawSprite(const char* name, int16_t x, int16_t y, TFT_eSprite* target, uint16_t transparent) {
  int slot = findSprite(name);
  if (slot < 0) {
    Serial.printf("[Sprite] '%s' not loaded\n", name);
    return;
  }

  if (target) {
    _sprites[slot].spr->pushToSprite(target, x, y, transparent);
  } else {
    _sprites[slot].spr->pushSprite(x, y, transparent);
  }
}

void freeSprite(const char* name) {
  int slot = findSprite(name);
  if (slot < 0) return;

  _sprites[slot].spr->deleteSprite();
  delete _sprites[slot].spr;
  _sprites[slot].spr = nullptr;
  _sprites[slot].loaded = false;
  _sprites[slot].name[0] = '\0';
  Serial.printf("[Sprite] Freed '%s'\n", name);
}

void freeAllSprites() {
  for (int i = 0; i < MAX_SPRITES; i++) {
    if (_sprites[i].loaded) {
      _sprites[i].spr->deleteSprite();
      delete _sprites[i].spr;
      _sprites[i].spr = nullptr;
      _sprites[i].loaded = false;
      _sprites[i].name[0] = '\0';
    }
  }
  Serial.println("[Sprite] All sprites freed");
}

TFT_eSprite* getSprite(const char* name) {
  int slot = findSprite(name);
  return slot >= 0 ? _sprites[slot].spr : nullptr;
}

static TFT_eSprite canvas = TFT_eSprite(&tft);
static bool canvasReady = false;

void drawSpriteRotated(const char* name, int16_t x, int16_t y, float angle, uint16_t transparent, TFT_eSprite* target) {
  int slot = findSprite(name);
  if (slot < 0) {
    Serial.printf("[Sprite] '%s' not loaded\n", name);
    return;
  }
  TFT_eSprite* spr = _sprites[slot].spr;

  if (target) {
    spr->setPivot(x, y);
    spr->pushRotated(target, angle, transparent);
  } else {
    if (!canvasReady) {
      canvas.setColorDepth(16);
      canvas.createSprite(_sprites[slot].w, _sprites[slot].h);
      canvasReady = true;
    }
    canvas.fillSprite(transparent);
    spr->setPivot(_sprites[slot].w / 2, _sprites[slot].h / 2);
    spr->pushRotated(&canvas, angle, transparent);
    canvas.pushSprite(x - _sprites[slot].w / 2, y - _sprites[slot].h / 2, transparent);
  }
}

//CANVASES

static Canvas _canvases[MAX_CANVASES];

static int findCanvas(const char* name) {
  for (int i = 0; i < MAX_CANVASES; i++)
    if (_canvases[i].loaded && strcmp(_canvases[i].name, name) == 0)
      return i;
  return -1;
}


static int freeSlotCanva() {
  for (int i = 0; i < MAX_CANVASES; i++)
    if (!_canvases[i].loaded) return i;
  return -1;
}

bool createCanvas(const char* name, uint16_t w, uint16_t h, uint16_t bgColor) {
  if (findCanvas(name) >= 0) {
    Serial.println("canva already exists");
    return true;
  }

  int slot = freeSlotCanva();
  if (slot < 0) {
    Serial.println("no free canvases slot");
    return false;
  }

  TFT_eSprite* spr = new TFT_eSprite(&tft);
  spr->setColorDepth(16);
  if (!spr->createSprite(w, h)) {
    Serial.println("not enought ram :(");
    delete spr;
    return false;
  }
  spr->fillSprite(bgColor);

  _canvases[slot].spr = spr;
  _canvases[slot].w = w;
  _canvases[slot].h = h;
  _canvases[slot].bgColor = bgColor;
  _canvases[slot].loaded = true;
  strncpy(_canvases[slot].name, name, 31);

  Serial.println("Canvas created");

  return true;
}

TFT_eSprite* getCanvas(const char* name) {
  int slot = findCanvas(name);
  return slot >= 0 ? _canvases[slot].spr : nullptr;
}

void pushCanvas(const char* name, uint16_t x, uint16_t y, bool centered) {
  int slot = findCanvas(name);
  if (slot < 0) {
    Serial.println("canvas nor found");
    return;
  }
  uint16_t px = centered ? x - _canvases[slot].w / 2 : x;
  uint16_t py = centered ? y - _canvases[slot].h / 2 : y;
  _canvases[slot].spr->pushSprite(px, py, _canvases[slot].bgColor);  // added bgColor here
}
void clearCanvas(const char* name) {
  int slot = findCanvas(name);
  if (slot < 0) return;
  _canvases[slot].spr->fillSprite(_canvases[slot].bgColor);
}

void deleteCanvas(const char* name) {
  int slot = findCanvas(name);
  if (slot < 0) return;
  _canvases[slot].spr->deleteSprite();
  delete _canvases[slot].spr;
  _canvases[slot].spr = nullptr;
  _canvases[slot].loaded = false;
  _canvases[slot].name[0] = '\0';
  Serial.printf("deleted canva");
}

void deleteAllCanvases() {
  for (int i = 0; i < MAX_CANVASES; i++) {
    if (_canvases[i].loaded) {
      _canvases[i].spr->deleteSprite();
      delete _canvases[i].spr;
      _canvases[i].spr = nullptr;
      _canvases[i].loaded = false;
      _canvases[i].name[0] = '\0';
    }
  }
  Serial.println("all canvases deleted");
}


void drawTextTo(const char* text, int16_t x, int16_t y, uint16_t color, uint16_t bg,
                 const GFXfont* font, uint8_t datum, TFT_eSprite* target) {
  TFT_eSPI* dest = target ? (TFT_eSPI*)target : (TFT_eSPI*)&tft; 
  dest->setFreeFont(font);
  dest->setTextColor(color, bg);
  dest->setTextDatum(datum);
  dest->drawString(text, x, y);
}
