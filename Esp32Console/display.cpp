#include "esp32-hal.h"
#include <TFT_eSPI.h>
#include <Arduino.h>
#include <TJpg_Decoder.h>
#include "Preferences.h"
//#define USE_DMA

SemaphoreHandle_t tftMutex = xSemaphoreCreateMutex();

TFT_eSPI tft = TFT_eSPI();

#ifdef USE_DMA
uint16_t dmaBuffer1[16 * 16];
uint16_t dmaBuffer2[16 * 16];
uint16_t *dmaBufferPtr = dmaBuffer1;
bool dmaBufferSel = 0;
#endif

//uint16_t* dmaBuffer = nullptr;
File bmpFS;
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap) {
  if (y >= tft.height()) return 0;

#ifdef USE_DMA
  if (dmaBufferSel) dmaBufferPtr = dmaBuffer2;
  else dmaBufferPtr = dmaBuffer1;

  dmaBufferSel = !dmaBufferSel;

  tft.pushImageDMA(x, y, w, h, bitmap, dmaBufferPtr);
  //Serial.println("used dma");
#else
  tft.pushImage(x, y, w, h, bitmap);
#endif

  return 1;
}

void initTFT() {
  tft.begin();
  tft.fillScreen(COLOR_BG);
  tft.setRotation(3);
#ifdef USE_DMA
  tft.initDMA();
#endif
  tft.invertDisplay(false);
  TJpgDec.setJpgScale(1);
  tft.setSwapBytes(true);
  TJpgDec.setSwapBytes(false);
  TJpgDec.setCallback(tft_output);
  Serial.println("Setup done");
}



void drawJpg(const char *filename, int16_t x, int16_t y) {
  /*uint16_t w = 0, h = 0;
  TJpgDec.getSdJpgSize(&w, &h, filename);

  Serial.print("Width = ");
  Serial.print(w);
  Serial.print(", Height = ");
  Serial.println(h);*/

  uint32_t dt = millis();

  tft.startWrite();

  TJpgDec.drawSdJpg(x, y, filename);
  //TJpgDec.
  tft.endWrite();

  Serial.print("Render time: ");
  Serial.print(millis() - dt);
  Serial.println(" ms");
}

uint16_t read16(fs::File &f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read();
  ((uint8_t *)&result)[1] = f.read();
  return result;
}


uint32_t read32(fs::File &f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read();
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read();
  return result;
}

//dma wouldnt work drawing speed little slow but might be because of the sd card
//this should load line by line
//might switch to other format such as raw if faster
//also need for trasnaprent drawing
void drawBmpFast(const char *filename, int16_t x, int16_t y) {

  bmpFS = SD.open(filename);

  if (!bmpFS) {
    Serial.println("File not found");
    return;
  }
  if (read16(bmpFS) != 0x4D42) {
    Serial.println("Not BMP");
    bmpFS.close();
    return;
  }

  read32(bmpFS);
  read32(bmpFS);

  uint32_t dataOffset = read32(bmpFS);
  uint32_t headerSize = read32(bmpFS);
  uint32_t width = read32(bmpFS);
  uint32_t height = read32(bmpFS);
  uint16_t planes = read16(bmpFS);
  uint16_t depth = read16(bmpFS);
  uint32_t compression = read32(bmpFS);

  if (planes != 1 || depth != 24 || compression != 0) {
    Serial.println("BMP format not recognized");
    bmpFS.close();
    return;
  }

  y += height - 1;
  uint16_t padding = (4 - ((width * 3) & 3)) & 3;
  uint8_t lineBuffer[width * 3];

  bmpFS.seek(dataOffset);
  uint16_t pixelBuffer[width];
  uint32_t t0 = millis();
  tft.startWrite();

  for (uint16_t row = 0; row < height; row++) {
    bmpFS.read(lineBuffer, sizeof(lineBuffer));
    uint8_t *ptr = lineBuffer;
    for (uint16_t col = 0; col < width; col++) {
      uint8_t b = *ptr++;
      uint8_t g = *ptr++;
      uint8_t r = *ptr++;
      pixelBuffer[col] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    }
    tft.setAddrWindow(x, y, width, 1);
    tft.pushPixels(pixelBuffer, width);
    if (padding) bmpFS.read(lineBuffer, padding);
    y--;
  }
  tft.endWrite();

  Serial.print("Fast line: ");
  Serial.print(millis() - t0);
  Serial.println(" ms");
  bmpFS.close();
}

void drawBmp(const char *filename, int16_t x, int16_t y) {
  drawBmpFast(filename, x, y);
}

void drawBmpTransparent(const char *filename, int16_t x, int16_t y, uint16_t transparentColor) {
  bmpFS = SD.open(filename);
  if (!bmpFS) {
    Serial.println("File not found");
    return;
  }
  if (read16(bmpFS) != 0x4D42) {
    Serial.println("Not BMP");
    bmpFS.close();
    return;
  }

  read32(bmpFS);
  read32(bmpFS);
  uint32_t dataOffset = read32(bmpFS);
  uint32_t headerSize = read32(bmpFS);
  uint32_t width = read32(bmpFS);
  uint32_t height = read32(bmpFS);
  uint16_t planes = read16(bmpFS);
  uint16_t depth = read16(bmpFS);
  uint32_t compression = read32(bmpFS);

  if (planes != 1 || depth != 24 || compression != 0) {
    Serial.println("BMP format not supported");
    bmpFS.close();
    return;
  }

  uint16_t padding = (4 - ((width * 3) & 3)) & 3;
  uint32_t t0 = millis();
  uint16_t *fullBuffer = (uint16_t *)malloc(width * height * sizeof(uint16_t));
  if (!fullBuffer) {
    Serial.println("OOM");
    bmpFS.close();
    return;
  }

  uint8_t lineBuffer[width * 3];
  bmpFS.seek(dataOffset);

  for (int row = height - 1; row >= 0; row--) {
    bmpFS.read(lineBuffer, width * 3);
    uint8_t *ptr = lineBuffer;
    for (uint16_t col = 0; col < width; col++) {
      uint8_t b = *ptr++, g = *ptr++, r = *ptr++;
      fullBuffer[row * width + col] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    }
    if (padding) bmpFS.seek(bmpFS.position() + padding);
  }

  bmpFS.close();

  tft.startWrite();
  tft.pushImage(x, y, width, height, fullBuffer, transparentColor);
  tft.endWrite();
  Serial.print("Fast line: ");
  Serial.print(millis() - t0);
  Serial.println(" ms");
  bmpFS.close();
  free(fullBuffer);
}

void drawBmpRegion(const char *filename, int16_t srcX, int16_t srcY, int16_t w, int16_t h, int16_t dstX, int16_t dstY) {
  File f = SD.open(filename);
  if (!f) {
    Serial.println("[BMP] File not found");
    return;
  }

  if (read16(f) != 0x4D42) {
    Serial.println("[BMP] Not BMP");
    f.close();
    return;
  }
  read32(f);
  read32(f);
  uint32_t dataOffset = read32(f);
  uint32_t headerSize = read32(f);
  uint32_t imgW = read32(f);
  uint32_t imgH = read32(f);
  read16(f);
  uint16_t depth = read16(f);
  uint32_t compression = read32(f);

  if (depth != 24 || compression != 0) {
    Serial.println("[BMP] Unsupported format");
    f.close();
    return;
  }

  uint16_t rowPad = (4 - ((imgW * 3) & 3)) & 3;
  uint32_t rowBytes = imgW * 3 + rowPad;

  if (srcX < 0) {
    dstX -= srcX;
    w += srcX;
    srcX = 0;
  }
  if (srcY < 0) {
    dstY -= srcY;
    h += srcY;
    srcY = 0;
  }
  if (srcX + w > (int16_t)imgW) w = imgW - srcX;
  if (srcY + h > (int16_t)imgH) h = imgH - srcY;
  if (w <= 0 || h <= 0) {
    f.close();
    return;
  }

  uint8_t lineBuf[w * 3];
  uint16_t pixBuf[w];

  tft.startWrite();
  for (int16_t row = 0; row < h; row++) {
    int16_t bmpRow = (imgH - 1) - (srcY + row);
    uint32_t offset = dataOffset + (uint32_t)bmpRow * rowBytes + srcX * 3;
    f.seek(offset);
    f.read(lineBuf, w * 3);
    uint8_t *ptr = lineBuf;
    for (int16_t col = 0; col < w; col++) {
      uint8_t b = *ptr++, g = *ptr++, r = *ptr++;
      pixBuf[col] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    }
    tft.setAddrWindow(dstX, dstY + row, w, 1);
    tft.pushPixels(pixBuf, w);
  }
  tft.endWrite();
  f.close();
}

#define MAX_SAVED_REGIONS 8

struct SavedRegion {
  char name[32];
  int16_t x, y, w, h;
  uint16_t *pixels;
  bool used;
};

static SavedRegion _savedRegions[MAX_SAVED_REGIONS];

static int findRegionSlot(const char *name) {
  for (int i = 0; i < MAX_SAVED_REGIONS; i++)
    if (_savedRegions[i].used && strcmp(_savedRegions[i].name, name) == 0)
      return i;
  return -1;
}

static int freeRegionSlot() {
  for (int i = 0; i < MAX_SAVED_REGIONS; i++)
    if (!_savedRegions[i].used) return i;
  return -1;
}

void saveRegion(const char *name, int16_t x, int16_t y, int16_t w, int16_t h) {
  int slot = findRegionSlot(name);
  if (slot >= 0) {
    free(_savedRegions[slot].pixels);
    _savedRegions[slot].used = false;
  }

  slot = freeRegionSlot();
  if (slot < 0) {
    Serial.println("[Region] No free slots");
    return;
  }

  uint16_t *buf = (uint16_t *)malloc(w * h * sizeof(uint16_t));
  if (!buf) {
    Serial.println("[Region] Out of RAM");
    return;
  }

  tft.readRect(x, y, w, h, buf);

  strncpy(_savedRegions[slot].name, name, 31);
  _savedRegions[slot].name[31] = '\0';
  _savedRegions[slot].x = x;
  _savedRegions[slot].y = y;
  _savedRegions[slot].w = w;
  _savedRegions[slot].h = h;
  _savedRegions[slot].pixels = buf;
  _savedRegions[slot].used = true;
}

void restoreRegion(const char *name, int16_t x, int16_t y) {
  int slot = findRegionSlot(name);
  if (slot < 0) {
    Serial.printf("[Region] '%s' not found\n", name);
    return;
  }
  bool oldSwap = tft.getSwapBytes();

  tft.setSwapBytes(false);
  tft.pushImage(x, y,
                _savedRegions[slot].w,
                _savedRegions[slot].h,
                _savedRegions[slot].pixels);

  tft.setSwapBytes(oldSwap);
}

void freeRegion(const char *name) {
  int slot = findRegionSlot(name);
  if (slot < 0) return;
  free(_savedRegions[slot].pixels);
  _savedRegions[slot].pixels = nullptr;
  _savedRegions[slot].used = false;
  Serial.printf("[Region] freed '%s'\n", name);
}

void freeAllRegions() {
  for (int i = 0; i < MAX_SAVED_REGIONS; i++) {
    if (_savedRegions[i].used) {
      free(_savedRegions[i].pixels);
      _savedRegions[i].pixels = nullptr;
      _savedRegions[i].used = false;
    }
  }
}

//testing colors must be black->red-> blue yellow green might need to swap bytes
void flashColors() {
  tft.fillScreen(COLOR_BG);
  delay(2000);
  tft.fillScreen(TFT_RED);
  delay(2000);
  tft.fillScreen(TFT_BLUE);
  delay(2000);
  tft.fillScreen(TFT_YELLOW);
  delay(2000);
  tft.fillScreen(COLOR_SUCCESS);
  delay(2000);
}
