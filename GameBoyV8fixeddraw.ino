#include <TFT_eSPI.h>
#include <SPI.h>
#include <SD.h>
#include "BluetoothA2DPSource.h"
#include "FS.h"
#include "SPIFFS.h"
#include <vector>
#include <MyFonts.h>
#include <LuaWrapper.h>

// --- NEW MPU6050 LIBRARIES ---
#include "Wire.h"
#include <MPU6050_light.h>
// -----------------------------

LuaWrapper lua;

File currentScriptFile;
//right buttons
#define rUpButton 32
#define rDownButton 33
#define rLeftButton 25
#define rRightButton 26

//left buttons
#define lLeftButton 27
#define lRightButton 14
#define lDownButton 12
#define lUpButton 13

// ==== TFT (VSPI) pins ====
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_MISO -1  // not used
#define TFT_CS 5
#define TFT_DC 21
#define TFT_RST 22

// ==== SD (HSPI) pins ====
#define SD_MOSI 19
#define SD_MISO 16
#define SD_SCLK 17
#define SD_CS 15

// --- NEW MPU6050 CONFIG AND GLOBALS ---
const int SDA_PIN = 4;
const int SCL_PIN = 3;

const float TEMP_OFFSET = -24.0;
unsigned long mpuTimer = 0;  // Timer variable for MPU update rate (10ms is good)
MPU6050 mpu(Wire);
bool mpuAvailable = false;  // <-- new flag
// --------------------------------------

SPIClass spiSD(HSPI);

int screenWidth = 320;
int screenHeight = 240;
TFT_eSPI tft = TFT_eSPI();

enum Tab {
  Main,
  Games,
  Music,
  Settings,
  Utilities,
  MusicPlaying  // State for native music playback
};

Tab currentTab = Main;
int idx = 0;
int maxIdx = 0;

std::vector<String> gameFolders;
std::vector<String> musicFolders;
std::vector<String> utilityFolders;
int gameCount = 0;

bool runningLua = false;

// Time tracking for basic debouncing (200ms between accepted button presses)
unsigned long lastButtonPress = 0;
const long debounceDelay = 200;

// === Stop current Lua script ===
void stopLuaScript() {
  Serial.println("Stopping Lua...");
  lua.close();              // actually frees the Lua VM heap
  new (&lua) LuaWrapper();  // reconstruct cleanly
  runningLua = false;
  Serial.println("Lua stopped and memory reset!");
}

void showMpuData() {
  Serial.print(F("TEMPERATURE: "));
  Serial.println(mpu.getTemp());
  Serial.print(F("ACCELERO  X: "));
  Serial.print(mpu.getAccX());
  Serial.print("\tY: ");
  Serial.print(mpu.getAccY());
  Serial.print("\tZ: ");
  Serial.println(mpu.getAccZ());

  Serial.print(F("GYRO      X: "));
  Serial.print(mpu.getGyroX());
  Serial.print("\tY: ");
  Serial.print(mpu.getGyroY());
  Serial.print("\tZ: ");
  Serial.println(mpu.getGyroZ());

  Serial.print(F("ACC ANGLE X: "));
  Serial.print(mpu.getAccAngleX());
  Serial.print("\tY: ");
  Serial.println(mpu.getAccAngleY());

  Serial.print(F("ANGLE     X: "));
  Serial.print(mpu.getAngleX());
  Serial.print("\tY: ");
  Serial.print(mpu.getAngleY());
  Serial.print("\tZ: ");
  Serial.println(mpu.getAngleZ());
  Serial.println(F("=====================================================\n"));
}

// --- NEW MPU6050 FUNCTIONS (C++) ---
void drawBmpTransparent(const char* filename, int16_t x, int16_t y, float scale, uint16_t transparentColor = 0x0000) {

  if ((x >= tft.width()) || (y >= tft.height())) return;

  File bmpFS = SD.open(filename);
  if (!bmpFS) {
    Serial.print("File not found");
    return;
  }

  uint32_t seekOffset;
  uint16_t w, h, row, col;
  uint8_t r, g, b;

  uint32_t startTime = millis();

  if (read16(bmpFS) == 0x4D42) {
    read32(bmpFS);
    read32(bmpFS);
    seekOffset = read32(bmpFS);
    read32(bmpFS);
    w = read32(bmpFS);
    h = read32(bmpFS);

    if ((read16(bmpFS) == 1) && (read16(bmpFS) == 24) && (read32(bmpFS) == 0)) {

      y += h - 1;  // BMP is bottom-up

      tft.setSwapBytes(true);
      bmpFS.seek(seekOffset);

      uint16_t padding = (4 - ((w * 3) & 3)) & 3;
      uint8_t lineBufferRaw[w * 3];
      uint16_t lineBuffer[w];

      for (row = 0; row < h; row++) {
        bmpFS.read(lineBufferRaw, sizeof(lineBufferRaw));
        uint8_t* bptr = lineBufferRaw;

        // Convert 24-bit to 16-bit
        for (col = 0; col < w; col++) {
          b = *bptr++;
          g = *bptr++;
          r = *bptr++;
          lineBuffer[col] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
        }

        if (padding) bmpFS.read((uint8_t*)bptr, padding);

        // Draw contiguous segments
        col = 0;
        while (col < w) {
          // Skip transparent pixels
          while (col < w && lineBuffer[col] == transparentColor) col++;

          uint16_t start = col;
          while (col < w && lineBuffer[col] != transparentColor) col++;

          if (col > start) {
            tft.pushImage(x + start, y, col - start, 1, &lineBuffer[start]);
          }
        }

        y--;  // move to next row
      }

      Serial.print("Loaded in ");
      Serial.print(millis() - startTime);
      Serial.println(" ms");
    } else Serial.println("BMP format not recognized.");
  }

  bmpFS.close();
}

void drawBmp(const char* filename, int16_t x, int16_t y) {

  if ((x >= tft.width()) || (y >= tft.height())) return;

  File bmpFS;

  // Open requested file on SD card
  bmpFS = SD.open(filename);

  if (!bmpFS) {
    Serial.print("File not found");
    return;
  }

  uint32_t seekOffset;
  uint16_t w, h, row, col;
  uint8_t r, g, b;

  uint32_t startTime = millis();

  if (read16(bmpFS) == 0x4D42) {
    read32(bmpFS);
    read32(bmpFS);
    seekOffset = read32(bmpFS);
    read32(bmpFS);
    w = read32(bmpFS);
    h = read32(bmpFS);

    if ((read16(bmpFS) == 1) && (read16(bmpFS) == 24) && (read32(bmpFS) == 0)) {
      y += h - 1;

      tft.setSwapBytes(true);
      bmpFS.seek(seekOffset);

      uint16_t padding = (4 - ((w * 3) & 3)) & 3;
      uint8_t lineBuffer[w * 3];

      for (row = 0; row < h; row++) {
        bmpFS.read(lineBuffer, sizeof(lineBuffer));
        uint8_t* bptr = lineBuffer;
        uint16_t* tptr = (uint16_t*)lineBuffer;
        // Convert 24 to 16 bit colours
        for (uint16_t col = 0; col < w; col++) {
          b = *bptr++;
          g = *bptr++;
          r = *bptr++;
          *tptr++ = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
        }
        // Read any line padding
        if (padding) bmpFS.read((uint8_t*)tptr, padding);
        // Push the pixel row to screen, pushImage will crop the line if needed
        tft.pushImage(x, y--, w, 1, (uint16_t*)lineBuffer);
      }
      Serial.print("Loaded in ");
      Serial.print(millis() - startTime);
      Serial.println(" ms");
    } else Serial.println("BMP format not recognized.");
  }
  bmpFS.close();
}


uint16_t read16(fs::File& f) {
  uint16_t result;
  ((uint8_t*)&result)[0] = f.read();  // LSB
  ((uint8_t*)&result)[1] = f.read();  // MSB
  return result;
}


uint32_t read32(fs::File& f) {
  uint32_t result;
  ((uint8_t*)&result)[0] = f.read();  // LSB
  ((uint8_t*)&result)[1] = f.read();
  ((uint8_t*)&result)[2] = f.read();
  ((uint8_t*)&result)[3] = f.read();  // MSB
  return result;
}


int lua_getMPUData(lua_State* L) {
  lua_newtable(L);  // Create a new table on Lua stack

  // Temperature
  lua_pushstring(L, "temp");
  lua_pushnumber(L, mpu.getTemp());
  lua_settable(L, -3);

  // Accelerometer
  lua_pushstring(L, "accX");
  lua_pushnumber(L, mpu.getAccX());
  lua_settable(L, -3);

  lua_pushstring(L, "accY");
  lua_pushnumber(L, mpu.getAccY());
  lua_settable(L, -3);

  lua_pushstring(L, "accZ");
  lua_pushnumber(L, mpu.getAccZ());
  lua_settable(L, -3);

  // Gyroscope
  lua_pushstring(L, "gyroX");
  lua_pushnumber(L, mpu.getGyroX());
  lua_settable(L, -3);

  lua_pushstring(L, "gyroY");
  lua_pushnumber(L, mpu.getGyroY());
  lua_settable(L, -3);

  lua_pushstring(L, "gyroZ");
  lua_pushnumber(L, mpu.getGyroZ());
  lua_settable(L, -3);

  // Accelerometer angles
  lua_pushstring(L, "accAngleX");
  lua_pushnumber(L, mpu.getAccAngleX());
  lua_settable(L, -3);

  lua_pushstring(L, "accAngleY");
  lua_pushnumber(L, mpu.getAccAngleY());
  lua_settable(L, -3);

  // Gyro angles
  lua_pushstring(L, "angleX");
  lua_pushnumber(L, mpu.getAngleX());
  lua_settable(L, -3);

  lua_pushstring(L, "angleY");
  lua_pushnumber(L, mpu.getAngleY());
  lua_settable(L, -3);

  lua_pushstring(L, "angleZ");
  lua_pushnumber(L, mpu.getAngleZ());
  lua_settable(L, -3);

  return 1;  // Return 1 table to Lua
}



// ==== Helper Functions to expose to Lua ====
int lua_drawPixel(lua_State* L) {
  int x = luaL_checkinteger(L, 1);
  int y = luaL_checkinteger(L, 2);
  uint16_t color = luaL_checkinteger(L, 3);
  tft.drawPixel(x, y, color);
  return 0;
}

int lua_clearScreen(lua_State* L) {
  uint16_t color = luaL_checkinteger(L, 1);
  tft.fillScreen(color);
  return 0;
}

// === Lua exposed functions ===
int lua_drawPixels(lua_State* L) {
  luaL_checktype(L, 1, LUA_TTABLE);
  int len = lua_rawlen(L, 1);

  for (int i = 1; i <= len; i++) {
    lua_rawgeti(L, 1, i);
    if (lua_istable(L, -1)) {
      lua_rawgeti(L, -1, 1);
      int x = luaL_checkinteger(L, -1);
      lua_pop(L, 1);
      lua_rawgeti(L, -1, 2);
      int y = luaL_checkinteger(L, -1);
      lua_pop(L, 1);
      lua_rawgeti(L, -1, 3);
      uint16_t color = luaL_checkinteger(L, -1);
      lua_pop(L, 1);
      tft.drawPixel(x, y, color);
    }
    lua_pop(L, 1);
  }
  return 0;
}


// Lua wrapper now uses the unified drawBmpTransparent function
int lua_drawBmpTransparent(lua_State* L) {
  const char* path = luaL_checkstring(L, 1);
  int x = luaL_checkinteger(L, 2);
  int y = luaL_checkinteger(L, 3);
  // Lua users can optionally pass scale and transparent color
  float scale = (float)luaL_optnumber(L, 4, 1.0);  // New: optional scale, defaults to 1.0
  uint16_t transparentColor = luaL_optinteger(L, 5, 0xFFFF);

  // Call the new unified function
  drawBmpTransparent(path, x, y, scale, transparentColor);
  return 0;
}

int lua_drawBmp(lua_State* L) {
  const char* path = luaL_checkstring(L, 1);
  int x = luaL_checkinteger(L, 2);
  int y = luaL_checkinteger(L, 3);
  // Lua users can optionally pass scale and transparent color

  // Call the new unified function
  drawBmp(path, x, y);
  return 0;
}

int lua_log(lua_State* L) {
  const char* msg = luaL_checkstring(L, 1);
  Serial.println(msg);
  return 0;
}

int lua_showText(lua_State* L) {
  const char* text = luaL_checkstring(L, 1);
  int x = luaL_checkinteger(L, 2);
  int y = luaL_checkinteger(L, 3);
  int color = luaL_checkinteger(L, 4);
  const char* fontName = luaL_optstring(L, 5, "FF23");

  tft.setTextColor(color, TFT_BLACK);
  tft.setCursor(x, y);

  // match font string
  if (strcmp(fontName, "FF23") == 0) tft.setFreeFont(&FF23);
  else if (strcmp(fontName, "FF17") == 0) tft.setFreeFont(&FF17);
  else if (strcmp(fontName, "FF27") == 0) tft.setFreeFont(&FF27);
  else if (strcmp(fontName, "FF19") == 0) tft.setFreeFont(&FF19);
  else if (strcmp(fontName, "FF22") == 0) tft.setFreeFont(&FF22);
  else if (strcmp(fontName, "FF30") == 0) tft.setFreeFont(&FF30);
  else if (strcmp(fontName, "FF31") == 0) tft.setFreeFont(&FF31);
  else tft.setFreeFont(&FF23);  // default

  tft.print(text);
  return 0;
}

int lua_millis(lua_State* L) {
  lua_pushinteger(L, millis());
  return 1;
}

int lua_readGPIO(lua_State* L) {
  int pin = luaL_checkinteger(L, 1);
  int val = digitalRead(pin);
  lua_pushinteger(L, val);
  return 1;
}

// Function to stop the Lua VM from within a Lua script
int lua_StopLua(lua_State* L) {
  stopLuaScript();
  return 0;
}

// === Register all functions ===
void registerCustomLuaFunctions() {
  lua.Lua_register("drawPixel", lua_drawPixel);
  lua.Lua_register("drawPixels", lua_drawPixels);
  lua.Lua_register("drawBmpTransparent", lua_drawBmpTransparent);
  lua.Lua_register("drawBmp", lua_drawBmp);
  lua.Lua_register("clearScreen", lua_clearScreen);
  lua.Lua_register("log", lua_log);
  lua.Lua_register("millis", lua_millis);
  lua.Lua_register("readGPIO", lua_readGPIO);
  lua.Lua_register("showText", lua_showText);
  lua.Lua_register("stopLua", lua_StopLua);
  lua.Lua_register("getMPUData", lua_getMPUData);
}


// === Run Lua script from SD ===
bool runLuaScript(const char* path) {
  // stop any currently running script
  stopLuaScript();

  if (!SD.exists(path)) {
    Serial.println("Lua file not found!");
    return false;
  }

  File file = SD.open(path);
  if (!file) {
    Serial.println("Failed to open Lua file");
    return false;
  }

  String script;
  while (file.available()) script += (char)file.read();
  file.close();

  // register your custom Lua functions again
  registerCustomLuaFunctions();

  String result = lua.Lua_dostring(&script);

  if (result != "OK") {
    Serial.print("Lua error: ");
    Serial.println(result);
    return false;
  }

  Serial.println("Lua script executed successfully!");
  runningLua = true;
  return true;
}


//---------------FILES MANAGMENT-------------------------
std::vector<String> loadFolders(const char* folderPath) {
  std::vector<String> folders;

  File dir = SD.open(folderPath);
  if (!dir || !dir.isDirectory()) {
    Serial.printf("Folder not found or invalid: %s\n", folderPath);
    return folders;  // empty vector
  }

  File entry;
  while ((entry = dir.openNextFile())) {
    if (entry.isDirectory()) {
      // Note: entry.name() includes the path, e.g. "/games/GameA"
      // We want just the folder name: "GameA"
      String fullPath = entry.name();
      int lastSlash = fullPath.lastIndexOf('/');
      if (lastSlash != -1) {
        folders.push_back(fullPath.substring(lastSlash + 1));
      } else {
        folders.push_back(fullPath);
      }
    }
    entry.close();
  }
  dir.close();
  return folders;
}

void listFiles() {
  File root = SD.open("/");
  File file = root.openNextFile();
  while (file) {
    Serial.println(file.name());
    file = root.openNextFile();
  }
}


//-------------------------------------------TFT DRAW FUNCTIONS-------------------------------------------

void drawThickRoundRect(int x, int y, int w, int h, int cornerRadius, int thickness, uint16_t color) {
  for (int i = 0; i < thickness; i++) {
    tft.drawRoundRect(x + i, y + i, w - 2 * i, h - 2 * i, cornerRadius, color);
  }
}

// --- NEW UNIFIED FUNCTION FOR DRAWING ALL SCROLLABLE FOLDER LISTS ---
void drawFolderListScreen(Tab tab, const char* title, std::vector<String>& folders) {
  if (currentTab != tab) return;

  maxIdx = folders.size();  // Max index is 0 (Back) + N folders
  if (idx > maxIdx) idx = 0;
  if (idx < 0) idx = maxIdx;

  tft.fillScreen(TFT_BLACK);

  // 1. Draw Back Button (always visible)
  String backText = String("<-Back (") + title + ")";
  tft.setFreeFont(idx == 0 ? &FF27 : &FF23);
  tft.setCursor((screenWidth - tft.textWidth(backText.c_str())) / 2, 40);
  tft.setTextColor(idx == 0 ? TFT_YELLOW : TFT_WHITE);
  tft.print(backText);

  // --- Scrolling Logic ---
  const int maxDisplayItems = 3;  // Max items visible on screen (excluding Back)
  const int itemHeight = 50;
  const int listStartY = 90;

  int listSize = folders.size();

  int scrollOffset = 0;
  // If the selected index (idx) is greater than the number of items we can display, scroll down.
  // idx is 1-based for the list items (1, 2, 3, 4, ...)
  if (idx > maxDisplayItems) {
    // scrollOffset = 1-based index (idx) - number of items to display (3)
    // If idx=4, scrollOffset=1 (we start displaying item #2 at screen pos 0)
    scrollOffset = idx - maxDisplayItems;
  }

  // Determine the item indices to draw from the 'folders' vector (0-based)
  int displayStart = scrollOffset;                                 // 0-based index of the first item to draw (e.g. 0, 1, 2, 3...)
  int displayEnd = min(scrollOffset + maxDisplayItems, listSize);  // 0-based index of the last item to draw

  tft.setFreeFont(&FF19);

  // 2. List Items
  for (int i = displayStart; i < displayEnd; i++) {
    // Current position on the physical screen (0, 1, or 2)
    int screenIndex = i - scrollOffset;

    // Calculate Y position based on screenIndex
    int yPos = listStartY + itemHeight * screenIndex;

    // The current item's menu index (1-based: 1, 2, 3, ...)
    int menuIndex = i + 1;

    // Check if this item is selected
    bool isSelected = (idx == menuIndex);

    tft.setCursor(10, yPos);
    tft.setTextColor(isSelected ? TFT_YELLOW : TFT_WHITE);
    tft.print(folders[i]);
  }

  // Draw scroll indicators
  uint16_t indicatorColor = TFT_DARKGREY;

  // Up arrow if we are scrolled down (scrollOffset > 0)
  if (scrollOffset > 0) {
    tft.fillTriangle(screenWidth - 20, listStartY - 5, screenWidth - 10, listStartY - 5, screenWidth - 15, listStartY - 15, indicatorColor);
  }

  // Down arrow if there are more items below the visible window
  if (displayEnd < listSize) {
    // Calculate Y position for indicator (approx middle of the last displayed item slot)
    int downY = listStartY + maxDisplayItems * itemHeight - itemHeight / 2;
    tft.fillTriangle(screenWidth - 20, downY + 5, screenWidth - 10, downY + 5, screenWidth - 15, downY + 15, indicatorColor);
  }
}

void drawGamesScreen() {
  // Calls the unified function for Games
  drawFolderListScreen(Games, "GAMES", gameFolders);
}

void drawMusicScreen() {
  // Calls the unified function for Music
  drawFolderListScreen(Music, "MUSIC", musicFolders);
}

// NEW: Placeholder screen for when music is playing (native function)
void drawMusicPlayingScreen() {
  if (currentTab != MusicPlaying) return;
  maxIdx = 0;  // Only one action: Stop/Back
  if (idx > maxIdx) idx = 0;
  if (idx < 0) idx = maxIdx;

  tft.fillScreen(TFT_DARKGREEN);
  tft.setTextSize(1);
  tft.setFreeFont(&FF27);

  tft.setCursor((screenWidth - tft.textWidth("NOW PLAYING")) / 2, 40);
  tft.setTextColor(TFT_WHITE);
  tft.print("NOW PLAYING");

  tft.setFreeFont(idx == 0 ? &FF27 : &FF23);
  tft.setCursor((screenWidth - tft.textWidth("<-Stop Playback")) / 2, 120);
  tft.setTextColor(idx == 0 ? TFT_YELLOW : TFT_WHITE);
  tft.print("<-Stop Playback");
}


void drawUtilitiesScreen() {
  // Calls the unified function for Utilities
  drawFolderListScreen(Utilities, "UTILITIES", utilityFolders);
}


// Simple placeholder for Settings (not a list)
void drawSettingsScreen() {
  if (currentTab != Settings) return;
  maxIdx = 0;
  if (idx > maxIdx) idx = 0;
  if (idx < 0) idx = maxIdx;

  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setFreeFont(idx == 0 ? &FF27 : &FF23);

  tft.setCursor((screenWidth - tft.textWidth("<-Back(SETTINGS)")) / 2, 40);
  tft.setTextColor(idx == 0 ? TFT_YELLOW : TFT_WHITE);
  tft.print("<-Back(SETTINGS)");
}

void refreshScreen() {
  if (runningLua == true) return;
  if (currentTab == Main) drawMainScreen();
  else if (currentTab == Games) drawGamesScreen();
  else if (currentTab == Music) drawMusicScreen();
  else if (currentTab == Settings) drawSettingsScreen();
  else if (currentTab == Utilities) drawUtilitiesScreen();
  else if (currentTab == MusicPlaying) drawMusicPlayingScreen();  // NEW
}


//---------------TABS TFT DRAWING---------------//
void drawMainScreen() {
  if (currentTab != Main) return;
  maxIdx = 3;
  if (idx > maxIdx) idx = 0;
  if (idx < 0) idx = maxIdx;

  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(1);
  tft.setFreeFont(&FF23);

  String text = "";

  if (idx == 0) {
    text = "Games";
    // Use the unified drawBmp function, passing 1.0 for scale
    drawBmp("/Assets/ImagesBmp/games_128x128V2.bmp", (screenWidth - 128) / 2, 80);
  } else if (idx == 1) {
    text = "Music";
    drawBmp("/Assets/ImagesBmp/music_128x128V3.bmp", (screenWidth - 128) / 2, 80);
  } else if (idx == 2) {
    text = "Settings";
    drawBmp("/Assets/ImagesBmp/settings_128x128V2.bmp", (screenWidth - 128) / 2, 80);
  } else if (idx == 3) {
    text = "Utilities";
    drawBmp("/Assets/ImagesBmp/utilities_128x128V2.bmp", (screenWidth - 128) / 2, 80);
  }

  // Draw text *after* the image is loaded to avoid delays
  tft.setCursor((screenWidth - tft.textWidth(text)) / 2, 50);
  tft.print(text);
}


void setup() {
  Serial.begin(9600);

  tft.init();
  tft.setRotation(1);  // optional, adjust for your screen orientation
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);

  spiSD.begin(SD_SCLK, SD_MISO, SD_MOSI, SD_CS);  // SCK, MISO, MOSI, CS
  if (!SD.begin(SD_CS, spiSD, 4000000)) {
    Serial.println("Card Mount Failed");
    tft.print("Card Mount Failed");
    while (1) yield();  // Stay here twiddling thumbs waiting
  }

  Serial.println("SD mounted.");

  // Load all folder lists at setup
  gameFolders = loadFolders("/games");
  musicFolders = loadFolders("/music");
  utilityFolders = loadFolders("/utilities");
  Serial.printf("Found %d game folders, %d music folders, %d utility folders.\n",
                gameFolders.size(), musicFolders.size(), utilityFolders.size());

  // Set up button pins
  pinMode(lUpButton, INPUT_PULLUP);
  pinMode(lDownButton, INPUT_PULLUP);
  pinMode(lLeftButton, INPUT_PULLUP);
  pinMode(lRightButton, INPUT_PULLUP);

  pinMode(rUpButton, INPUT_PULLUP);
  pinMode(rDownButton, INPUT_PULLUP);
  pinMode(rLeftButton, INPUT_PULLUP);
  pinMode(rRightButton, INPUT_PULLUP);

  // --- NEW: MPU6050 Setup ---
  Serial.println("Starting MPU6050 setup...");
  Wire.begin(SDA_PIN, SCL_PIN);

  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);

  // Many MPU6050_light versions return 0 on success. treat 0 as success, non-zero as failure.
  if (status == 0) {
    mpuAvailable = true;  // mark available
    Serial.println(F("Calculating offsets, do not move MPU6050"));
    delay(1000);
    mpu.calcOffsets(true, true);  // gyro and accelero
    Serial.println("Done!\n");
  } else {
    mpuAvailable = false;
    Serial.println("Failed to find MPU6050 chip. Check wiring!");
  }
  // ---------------------------

  refreshScreen();
}

void loop() {
  // Always run MPU check and event firing frequently.
  mpu.update();


  if (millis() - mpuTimer > 1000) {  // print data every second
    showMpuData();
    mpuTimer = millis();
  }
  // While running Lua, we skip the menu logic
  if (runningLua) {
    return;
  }

  // Basic button debouncing check
  unsigned long now = millis();
  if (now - lastButtonPress > debounceDelay) {
    bool screenNeedsRefresh = false;

    // --- Navigation Logic ---

    // Down Button (rDownButton)
    if (digitalRead(rDownButton) == LOW) {
      idx = (idx + 1) % (maxIdx + 1);  // Wrap around index
      screenNeedsRefresh = true;
    }
    // Up Button (rUpButton)
    else if (digitalRead(rUpButton) == LOW) {
      idx = (idx - 1);
      if (idx < 0) idx = maxIdx;  // Wrap around index
      screenNeedsRefresh = true;
    }
    // Right Button (rRightButton) - Select/Enter
    else if (digitalRead(rRightButton) == LOW) {
      if (currentTab == Main) {
        // Main menu selection
        if (idx == 0) currentTab = Games;
        else if (idx == 1) currentTab = Music;
        else if (idx == 2) currentTab = Settings;
        else if (idx == 3) currentTab = Utilities;
        idx = 0;  // Reset index for new tab
        screenNeedsRefresh = true;
      }

      // Handle folder list navigation and execution
      else if (currentTab == Games) {
        if (idx == 0) {  // Back action
          currentTab = Main;
          idx = 0;
          screenNeedsRefresh = true;
        } else if (idx > 0 && idx <= gameFolders.size()) {
          // Launch game script (Lua)
          String folderName = gameFolders[idx - 1];
          String scriptPath = "/games/" + folderName + "/main.lua";
          Serial.printf("Attempting to run script: %s\n", scriptPath.c_str());
          if (SD.exists(scriptPath)) {
            runLuaScript(scriptPath.c_str());
          }
        }
      }

      else if (currentTab == Music) {
        if (idx == 0) {  // Back action
          currentTab = Main;
          idx = 0;
          screenNeedsRefresh = true;
        } else if (idx > 0 && idx <= musicFolders.size()) {
          // *** MODIFIED: Launch native music playback (not Lua) ***
          String folderName = musicFolders[idx - 1];
          // Placeholder for native C++ music playback start
          Serial.printf("STARTING NATIVE MUSIC PLAYBACK for folder: /music/%s\n", folderName.c_str());

          currentTab = MusicPlaying;  // Switch to the music playback screen/state
          idx = 0;                    // Reset index for the MusicPlaying screen (e.g., stop button)
          screenNeedsRefresh = true;
          // runningLua remains FALSE to allow button input for controls (stop/skip)
        }
      }

      else if (currentTab == Utilities) {
        if (idx == 0) {  // Back action
          currentTab = Main;
          idx = 0;
          screenNeedsRefresh = true;
        } else if (idx > 0 && idx <= utilityFolders.size()) {
          // Launch utility script (Lua)
          String folderName = utilityFolders[idx - 1];
          String scriptPath = "/utilities/" + folderName + "/main.lua";  // Assuming main.lua in subfolder
          Serial.printf("Attempting to run utility script: %s\n", scriptPath.c_str());
          if (SD.exists(scriptPath)) {
            runLuaScript(scriptPath.c_str());
          }
        }
      }

      else if (currentTab == MusicPlaying) {  // NEW: Logic for Music Playing state
        if (idx == 0) {
          // Placeholder for native C++ music playback stop
          Serial.println("STOPPING NATIVE MUSIC PLAYBACK.");
          currentTab = Main;
          idx = 0;
          screenNeedsRefresh = true;
        }
      }

      else {  // Settings (idx 0 is "Back")
        if (idx == 0) {
          currentTab = Main;
          idx = 0;
          screenNeedsRefresh = true;
        }
      }
    }
    // Left Button (rLeftButton) - Back/Exit (Shortcut)
    else if (digitalRead(rLeftButton) == LOW) {
      if (currentTab == MusicPlaying) {  // Shortcut to stop music
        Serial.println("STOPPING NATIVE MUSIC PLAYBACK via L-Button.");
        currentTab = Main;
        idx = 0;
        screenNeedsRefresh = true;
      } else if (currentTab != Main) {
        currentTab = Main;
        idx = 0;
        screenNeedsRefresh = true;
      }
    }

    if (screenNeedsRefresh) {
      lastButtonPress = now;  // Record the time of this valid press
      refreshScreen();        // Only redraw the screen when something changes
    }
  }
}
