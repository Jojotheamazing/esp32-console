#include "esp32-hal.h"
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

uint16_t* dmaBuffer= nullptr;

void initTFT() {
  tft.init();
  tft.setSwapBytes(true);
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
}
// helping functions
uint16_t read16(fs::File& f) {
  uint16_t r;
  ((uint8_t*)&r)[0]= f.read();
  ( (uint8_t*)&r)[1]=f.read();
  return r;

}

uint32_t read32(fs::File& f) {
  uint32_t r;
  ((uint8_t*)&r)[0] =f.read();
  ((uint8_t*)&r)[1]= f.read();
  ((uint8_t*)&r)[2]=f.read();
  ((uint8_t*) &r)[3]=f.read();
  return r;
}

//dma wouldnt work drawing speed little slow but might be because of the sd card
//this should load line by line
//might switch to other format such as raw if faster
//also need for trasnaprent drawing
void drawBmpFast(const char* filename, int16_t x, int16_t y) {

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
  
  uint32_t dataOffset=read32(bmpFS);
  uint32_t headerSize =read32(bmpFS);
  uint32_t width = read32(bmpFS);
  uint32_t height = read32(bmpFS);
  uint16_t planes =read16(bmpFS);
  uint16_t depth= read16(bmpFS);
  uint32_t compression= read32(bmpFS);

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
  uint32_t t0= millis();
  tft.startWrite();

  for (uint16_t row = 0; row < height; row++) {
    bmpFS.read(lineBuffer, sizeof(lineBuffer));
    uint8_t* ptr = lineBuffer;
    for (uint16_t col = 0; col < width; col++) {
      uint8_t b =*ptr++;
      uint8_t g =*ptr++;
      uint8_t r=*ptr++;
      pixelBuffer[col] = ((r& 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    }
    tft.setAddrWindow(x, y, width, 1);
    tft.pushPixels(pixelBuffer, width);
    if (padding) bmpFS.read(lineBuffer, padding);
    y--;
  }
  tft.endWrite();

  Serial.print("Fast line: ");
  Serial.print(millis()- t0);
  Serial.println(" ms");
  bmpFS.close();
}

}
//testing colors must be black->red-> blue yellow green might need to swap bytes
void flashColors() {
  tft.fillScreen(TFT_BLACK);
  delay(2000);
  tft.fillScreen(TFT_RED);
  delay(2000);
  tft.fillScreen(TFT_BLUE);
  delay(2000);
  tft.fillScreen(TFT_YELLOW);
  delay(2000);
  tft.fillScreen(TFT_GREEN);
  delay(2000);
}
