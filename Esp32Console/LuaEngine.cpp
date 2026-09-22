#include <Arduino.h>
#include <SD.h>
#include "LuaEngine.h"
#include "display.h"
#include "ButtonManager.h"
#include "MyFonts.h"
#include "GamesTab.h"
#include "SpriteManager.h"
#include "Preferences.h"
#include "AudioHandler.h"
#include "Mpu6050Handler.h"
#include "JoystickHandler.h"
#include "HapticsManager.h"
extern GamesTab gamesTab;

bool runningLua = false;

static ButtonID nameToButtonID(const char* name) {
  if (strcmp(name, "UP") == 0) return BTN_UP;
  if (strcmp(name, "DOWN") == 0) return BTN_DOWN;
  if (strcmp(name, "LEFT") == 0) return BTN_LEFT;
  if (strcmp(name, "RIGHT") == 0) return BTN_RIGHT;
  if (strcmp(name, "A") == 0) return BTN_A;
  if (strcmp(name, "B") == 0) return BTN_B;
  if (strcmp(name, "X") == 0) return BTN_X;
  if (strcmp(name, "Y") == 0) return BTN_Y;
  if (strcmp(name, "L") == 0) return BTN_L;
  if (strcmp(name, "R") == 0) return BTN_R;
  if (strcmp(name, "START") == 0) return BTN_START;
  if (strcmp(name, "SEL") == 0) return BTN_SEL;
  if (strcmp(name, "VOL_UP") == 0) return BTN_VOL_UP;
  if (strcmp(name, "VOL_DOWN") == 0) return BTN_VOL_DOWN;
  return (ButtonID)255;
}

static int lua_btnIsDown(lua_State* L) {
  ButtonID id = nameToButtonID(luaL_checkstring(L, 1));
  lua_pushboolean(L, id != 255 && Input.isDown(id));
  return 1;
}

static int lua_btnPressed(lua_State* L) {
  ButtonID id = nameToButtonID(luaL_checkstring(L, 1));
  lua_pushboolean(L, id != 255 && Input.pressed(id));
  return 1;
}

static int lua_btnReleased(lua_State* L) {
  ButtonID id = nameToButtonID(luaL_checkstring(L, 1));
  lua_pushboolean(L, id != 255 && Input.released(id));
  return 1;
}

static int lua_btnHeld(lua_State* L) {
  ButtonID id = nameToButtonID(luaL_checkstring(L, 1));
  lua_pushboolean(L, id != 255 && Input.held(id));
  return 1;
}

static int lua_btnRepeated(lua_State* L) {
  ButtonID id = nameToButtonID(luaL_checkstring(L, 1));
  lua_pushboolean(L, id != 255 && Input.repeated(id));
  return 1;
}

static int lua_btnAnyPressed(lua_State* L) {
  lua_pushboolean(L, Input.anyPressed());
  return 1;
}

int lua_getJoystickList(lua_State* L) {
  lua_newtable(L);

  lua_pushinteger(L, getLX());
  lua_rawseti(L, -2, 1);
  lua_pushinteger(L, getLY());
  lua_rawseti(L, -2, 2);
  lua_pushinteger(L, getRX());
  lua_rawseti(L, -2, 3);
  lua_pushinteger(L, getRY());
  lua_rawseti(L, -2, 4);

  return 1;
}

//Display


static int lua_drawPixel(lua_State* L) {
  tft.drawPixel(luaL_checkinteger(L, 1),
                luaL_checkinteger(L, 2),
                (uint16_t)luaL_checkinteger(L, 3));
  return 0;
}

static int lua_clearScreen(lua_State* L) {
  tft.fillScreen((uint16_t)luaL_checkinteger(L, 1));
  return 0;
}

static int lua_drawRect(lua_State* L) {
  tft.drawRect(luaL_checkinteger(L, 1), luaL_checkinteger(L, 2),
               luaL_checkinteger(L, 3), luaL_checkinteger(L, 4),
               (uint16_t)luaL_checkinteger(L, 5));
  return 0;
}

static int lua_fillRect(lua_State* L) {
  tft.fillRect(luaL_checkinteger(L, 1), luaL_checkinteger(L, 2),
               luaL_checkinteger(L, 3), luaL_checkinteger(L, 4),
               (uint16_t)luaL_checkinteger(L, 5));
  return 0;
}

static int lua_drawCircle(lua_State* L) {
  tft.drawCircle(luaL_checkinteger(L, 1), luaL_checkinteger(L, 2),
                 luaL_checkinteger(L, 3), (uint16_t)luaL_checkinteger(L, 4));
  return 0;
}

static int lua_fillCircle(lua_State* L) {
  tft.fillCircle(luaL_checkinteger(L, 1), luaL_checkinteger(L, 2),
                 luaL_checkinteger(L, 3), (uint16_t)luaL_checkinteger(L, 4));
  return 0;
}

static int lua_drawLine(lua_State* L) {
  tft.drawLine(luaL_checkinteger(L, 1), luaL_checkinteger(L, 2),
               luaL_checkinteger(L, 3), luaL_checkinteger(L, 4),
               (uint16_t)luaL_checkinteger(L, 5));
  return 0;
}

static int lua_drawPixels(lua_State* L) {
  luaL_checktype(L, 1, LUA_TTABLE);
  int len = (int)lua_objlen(L, 1);
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
      uint16_t c = (uint16_t)luaL_checkinteger(L, -1);
      lua_pop(L, 1);
      tft.drawPixel(x, y, c);
    }
    lua_pop(L, 1);
  }
  return 0;
}

static int lua_drawBmp(lua_State* L) {
  drawBmp(luaL_checkstring(L, 1),
          luaL_checkinteger(L, 2),
          luaL_checkinteger(L, 3));
  return 0;
}

static int lua_drawBmpTransparent(lua_State* L) {
  drawBmpTransparent(luaL_checkstring(L, 1),
                     luaL_checkinteger(L, 2),
                     luaL_checkinteger(L, 3),
                     luaL_checkinteger(L, 4));
  return 0;
}

static int lua_drawJpg(lua_State* L) {
  drawJpg(luaL_checkstring(L, 1),
          luaL_checkinteger(L, 2),
          luaL_checkinteger(L, 3));
  return 0;
}

int lua_loadSprite(lua_State* L) {
  const char* name = luaL_checkstring(L, 1);
  const char* path = luaL_checkstring(L, 2);
  lua_pushboolean(L, loadSprite(name, path));
  return 1;
}

int lua_freeSprite(lua_State* L) {
  const char* name = luaL_checkstring(L, 1);
  freeSprite(name);
  return 0;
}

// screenWidth() / screenHeight()
static int lua_screenWidth(lua_State* L) {
  lua_pushinteger(L, tft.width());
  return 1;
}
static int lua_screenHeight(lua_State* L) {
  lua_pushinteger(L, tft.height());
  return 1;
}


static int lua_playSound(lua_State* L) {
  playSound(luaL_checkstring(L, 1));
  return 0;
}

static int lua_pauseSound(lua_State* L) {
  pauseSound();
  return 0;
}

static int lua_stopSound(lua_State* L) {
  stopSound();
  return 0;
}

static int lua_adjustVolume(lua_State* L) {
  volumeAdjust(luaL_checkinteger(L, 1));
  return 0;
}


static int lua_getMPUData(lua_State* L) {
  MPUData d = getMPUData();

  lua_newtable(L);

  lua_pushnumber(L, d.yaw);
  lua_setfield(L, -2, "yaw");
  lua_pushnumber(L, d.pitch);
  lua_setfield(L, -2, "pitch");
  lua_pushnumber(L, d.roll);
  lua_setfield(L, -2, "roll");
  lua_pushnumber(L, d.accX);
  lua_setfield(L, -2, "accX");
  lua_pushnumber(L, d.accY);
  lua_setfield(L, -2, "accY");
  lua_pushnumber(L, d.accZ);
  lua_setfield(L, -2, "accZ");

  return 1;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Utility bindings
// ─────────────────────────────────────────────────────────────────────────────

static int lua_log(lua_State* L) {
  Serial.println(luaL_checkstring(L, 1));
  return 0;
}

static int lua_millis(lua_State* L) {
  lua_pushinteger(L, (lua_Integer)millis());
  return 1;
}

static int lua_readGPIO(lua_State* L) {
  lua_pushinteger(L, digitalRead(luaL_checkinteger(L, 1)));
  return 1;
}

static int lua_writeGPIO(lua_State* L) {
  digitalWrite(luaL_checkinteger(L, 1), luaL_checkinteger(L, 2));
  return 0;
}

static int lua_freeHeap(lua_State* L) {
  lua_pushinteger(L, (lua_Integer)esp_get_free_heap_size());
  return 1;
}

static int lua_luaHeapUsed(lua_State* L) {
  lua_pushinteger(L, (lua_Integer)LuaEngine::heapUsed());
  return 1;
}

// yield() — pumps the input system + feeds the watchdog
static int lua_yieldFor(lua_State* L) {
  Input.update();
  vTaskDelay(1);  // yields to FreeRTOS scheduler (feeds watchdog, no busy-wait)
  return 0;
}



// stopLua() — raises a Lua error with the stop sentinel so the call stack
//             unwinds cleanly.  runLuaScript() catches it and sets
//             runningLua = false without crashing.
static int lua_StopLua(lua_State* L) {
  lua_pushstring(L, LUA_STOP_SENTINEL);
  lua_error(L);  // never returns
  return 0;
}

void stepLuaUpdate() {
  if (!runningLua) return;
  lua_State* L = LuaEngine::state();
  if (!L) return;

  lua_getglobal(L, "update");
  if (!lua_isfunction(L, -1)) {
    lua_pop(L, 1);
    return;
  }

  int ret = lua_pcall(L, 0, 0, 0);
  if (ret != 0) {
    const char* err = lua_tostring(L, -1);
    if (err && strstr(err, LUA_STOP_SENTINEL)) {
      Serial.println("[Lua] Script stopped via stopLua()");
    } else {
      Serial.printf("[Lua] update() error: %s\n", err ? err : "(unknown)");
    }
    gamesTab.draw();
    freeAllSprites();
    deleteAllCanvases();
    lua_pop(L, 1);
    LuaEngine::close();
    runningLua = false;
  }
}

// ── Add these to lua.cpp (inside registerCustomLuaFunctions) ──

// drawBmpRegion(path, srcX, srcY, w, h, dstX, dstY)
int lua_drawBmpRegion(lua_State* L) {
  const char* path = luaL_checkstring(L, 1);
  int16_t srcX = luaL_checkinteger(L, 2);
  int16_t srcY = luaL_checkinteger(L, 3);
  int16_t w = luaL_checkinteger(L, 4);
  int16_t h = luaL_checkinteger(L, 5);
  int16_t dstX = luaL_checkinteger(L, 6);
  int16_t dstY = luaL_checkinteger(L, 7);
  drawBmpRegion(path, srcX, srcY, w, h, dstX, dstY);
  return 0;
}

// saveRegion(name, x, y, w, h)
int lua_saveRegion(lua_State* L) {
  const char* name = luaL_checkstring(L, 1);
  int16_t x = luaL_checkinteger(L, 2);
  int16_t y = luaL_checkinteger(L, 3);
  int16_t w = luaL_checkinteger(L, 4);
  int16_t h = luaL_checkinteger(L, 5);
  saveRegion(name, x, y, w, h);
  return 0;
}

// restoreRegion(name, x, y)
int lua_restoreRegion(lua_State* L) {
  const char* name = luaL_checkstring(L, 1);
  int16_t x = luaL_checkinteger(L, 2);
  int16_t y = luaL_checkinteger(L, 3);
  restoreRegion(name, x, y);
  return 0;
}

// freeRegion(name)
int lua_freeRegion(lua_State* L) {
  const char* name = luaL_checkstring(L, 1);
  freeRegion(name);
  return 0;
}

// freeAllRegions()
int lua_freeAllRegions(lua_State* L) {
  freeAllRegions();
  return 0;
}

static int lua_vibrate(lua_State* L) {
  uint8_t ch = (uint8_t)luaL_checkinteger(L, 1);
  uint8_t strength = (uint8_t)luaL_checkinteger(L, 2);
  setVibration(ch, strength);
  return 0;
}

static int lua_stopVibrate(lua_State* L) {
  uint8_t ch = (uint8_t)luaL_checkinteger(L, 1);
  stopVibration(ch);
  return 0;
}

static int lua_playVibPattern(lua_State* L) {
  uint8_t ch = (uint8_t)luaL_checkinteger(L, 1);
  luaL_checktype(L, 2, LUA_TTABLE);
  int count = (int)lua_objlen(L, 2);
  Serial.printf("[Vib] ch=%d count=%d\n", ch, count);

  static VibStep steps[32];
  if (count > 32) count = 32;

  for (int i = 0; i < count; i++) {
    lua_rawgeti(L, 2, i + 1);
    lua_rawgeti(L, -1, 1);
    steps[i].strength = (uint8_t)luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    lua_rawgeti(L, -1, 2);
    steps[i].duration_ms = (uint32_t)luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    lua_pop(L, 1);
    Serial.printf("[Vib]   step %d: str=%d dur=%d\n", i, steps[i].strength, steps[i].duration_ms);
  }

  playPattern(ch, steps, count);
  return 0;
}

static int lua_stopVibPattern(lua_State* L) {
  uint8_t ch = (uint8_t)luaL_checkinteger(L, 1);
  stopPattern(ch);
  return 0;
}

static int lua_createCanvas(lua_State* L) {
  const char* name = luaL_checkstring(L, 1);
  uint16_t w = luaL_checkinteger(L, 2);
  uint16_t h = luaL_checkinteger(L, 3);
  uint16_t bg = luaL_checkinteger(L, 4);
  lua_pushboolean(L, createCanvas(name, w, h, bg));
  return 1;
}

static int lua_pushCanvas(lua_State* L) {
  const char* name = luaL_checkstring(L, 1);
  uint16_t x = luaL_checkinteger(L, 2);
  uint16_t y = luaL_checkinteger(L, 3);
  bool centered = lua_isboolean(L, 4) ? lua_toboolean(L, 4) : true;
  pushCanvas(name, x, y, centered);
  return 0;
}

static int lua_clearCanvas(lua_State* L) {
  clearCanvas(luaL_checkstring(L, 1));
  return 0;
}

static int lua_deleteCanvas(lua_State* L) {
  deleteCanvas(luaL_checkstring(L, 1));
  return 0;
}

static TFT_eSprite* luaOptCanvas(lua_State* L, int argIndex) {
  if (lua_isnoneornil(L, argIndex)) return nullptr;
  const char* canvasName = luaL_checkstring(L, argIndex);
  TFT_eSprite* c = getCanvas(canvasName);
  if (!c) Serial.printf("[Lua] canvas '%s' not found, drawing to screen instead\n", canvasName);
  return c;
}

int lua_drawSprite(lua_State* L) {
  const char* name = luaL_checkstring(L, 1);
  int x = luaL_checkinteger(L, 2);
  int y = luaL_checkinteger(L, 3);
  uint16_t transparent = luaL_checkinteger(L, 4);
  TFT_eSprite* target = luaOptCanvas(L, 5);
  drawSprite(name, x, y, target, transparent);
  return 0;
}

static int lua_drawSpriteRotated(lua_State* L) {
  const char* name = luaL_checkstring(L, 1);
  int16_t x = luaL_checkinteger(L, 2);
  int16_t y = luaL_checkinteger(L, 3);
  float angle = (float)luaL_checknumber(L, 4);
  uint16_t transparent = luaL_checkinteger(L, 5);
  TFT_eSprite* target = luaOptCanvas(L, 6);
  drawSpriteRotated(name, x, y, angle, transparent, target);
  return 0;
}


static int lua_showText(lua_State* L) {
  const char* text = luaL_checkstring(L, 1);
  int x = luaL_checkinteger(L, 2);
  int y = luaL_checkinteger(L, 3);
  uint16_t color = (uint16_t)luaL_checkinteger(L, 4);
  const char* fontName = luaL_optstring(L, 5, "FF23");
  const char* datumStr = luaL_optstring(L, 6, "TL");
  TFT_eSprite* target = luaOptCanvas(L, 7);

  uint8_t datum = TL_DATUM;
  if (strcmp(datumStr, "TC") == 0) datum = TC_DATUM;
  else if (strcmp(datumStr, "TR") == 0) datum = TR_DATUM;
  else if (strcmp(datumStr, "ML") == 0) datum = ML_DATUM;
  else if (strcmp(datumStr, "MC") == 0) datum = MC_DATUM;
  else if (strcmp(datumStr, "MR") == 0) datum = MR_DATUM;
  else if (strcmp(datumStr, "BL") == 0) datum = BL_DATUM;
  else if (strcmp(datumStr, "BC") == 0) datum = BC_DATUM;
  else if (strcmp(datumStr, "BR") == 0) datum = BR_DATUM;

  const GFXfont* font = &FF23;
  if (strcmp(fontName, "FF17") == 0) font = &FF17;
  else if (strcmp(fontName, "FF18") == 0) font = &FONT_BODY;
  else if (strcmp(fontName, "FF19") == 0) font = &FONT_TITLE;
  else if (strcmp(fontName, "FF20") == 0) font = &FF20;
  else if (strcmp(fontName, "FF21") == 0) font = &FF21;
  else if (strcmp(fontName, "FF22") == 0) font = &FF22;
  else if (strcmp(fontName, "FF24") == 0) font = &FF24;
  else if (strcmp(fontName, "FF27") == 0) font = &FF27;
  else if (strcmp(fontName, "FF30") == 0) font = &FF30;
  else if (strcmp(fontName, "FF31") == 0) font = &FF31;
  else if (strcmp(fontName, "FF1") == 0) font = &FF1;
  else if (strcmp(fontName, "FF2") == 0) font = &FF2;
  else if (strcmp(fontName, "FF5") == 0) font = &FF5;
  else if (strcmp(fontName, "FF6") == 0) font = &FF6;

  drawTextTo(text, x, y, color, COLOR_BG, font, datum, target);
  return 0;
}

void registerCustomLuaFunctions() {
  // display
  LuaEngine::reg("drawBmpRegion", lua_drawBmpRegion);
  LuaEngine::reg("saveRegion", lua_saveRegion);
  LuaEngine::reg("restoreRegion", lua_restoreRegion);
  LuaEngine::reg("freeRegion", lua_freeRegion);
  LuaEngine::reg("freeAllRegions", lua_freeAllRegions);

  LuaEngine::reg("loadSprite", lua_loadSprite);
  LuaEngine::reg("drawSprite", lua_drawSprite);
  LuaEngine::reg("freeSprite", lua_freeSprite);
  LuaEngine::reg("drawSpriteRotated", lua_drawSpriteRotated);

  LuaEngine::reg("createCanvas", lua_createCanvas);
  LuaEngine::reg("pushCanvas", lua_pushCanvas);
  LuaEngine::reg("clearCanvas", lua_clearCanvas);
  LuaEngine::reg("deleteCanvas", lua_deleteCanvas);

  LuaEngine::reg("drawPixel", lua_drawPixel);
  LuaEngine::reg("drawPixels", lua_drawPixels);

  LuaEngine::reg("drawBmpTransparent", lua_drawBmpTransparent);
  LuaEngine::reg("drawBmp", lua_drawBmp);
  LuaEngine::reg("drawJpg", lua_drawJpg);

  LuaEngine::reg("clearScreen", lua_clearScreen);
  LuaEngine::reg("showText", lua_showText);
  LuaEngine::reg("drawRect", lua_drawRect);
  LuaEngine::reg("fillRect", lua_fillRect);
  LuaEngine::reg("drawCircle", lua_drawCircle);
  LuaEngine::reg("fillCircle", lua_fillCircle);
  LuaEngine::reg("drawLine", lua_drawLine);
  LuaEngine::reg("screenWidth", lua_screenWidth);
  LuaEngine::reg("screenHeight", lua_screenHeight);

  LuaEngine::reg("playSound", lua_playSound);
  LuaEngine::reg("pauseSound", lua_pauseSound);
  LuaEngine::reg("stopSound", lua_stopSound);
  LuaEngine::reg("adjustVolume", lua_adjustVolume);
  // input
  LuaEngine::reg("getMPUData", lua_getMPUData);

  LuaEngine::reg("btnIsDown", lua_btnIsDown);
  LuaEngine::reg("btnPressed", lua_btnPressed);
  LuaEngine::reg("btnReleased", lua_btnReleased);
  LuaEngine::reg("btnHeld", lua_btnHeld);
  LuaEngine::reg("btnRepeated", lua_btnRepeated);
  LuaEngine::reg("btnAnyPressed", lua_btnAnyPressed);
  // util
  LuaEngine::reg("log", lua_log);
  LuaEngine::reg("millis", lua_millis);
  LuaEngine::reg("readGPIO", lua_readGPIO);
  LuaEngine::reg("writeGPIO", lua_writeGPIO);
  LuaEngine::reg("freeHeap", lua_freeHeap);
  LuaEngine::reg("luaHeapUsed", lua_luaHeapUsed);
  LuaEngine::reg("yield", lua_yieldFor);
  LuaEngine::reg("stopLua", lua_StopLua);

  LuaEngine::reg("vibrate", lua_vibrate);
  LuaEngine::reg("stopVibrate", lua_stopVibrate);
  LuaEngine::reg("playVibPattern", lua_playVibPattern);
  LuaEngine::reg("stopVibPattern", lua_stopVibPattern);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Stop
// ─────────────────────────────────────────────────────────────────────────────

void stopLuaScript() {
  Serial.println("[Lua] Stopping...");
  LuaEngine::close();
  runningLua = false;
  gamesTab.draw();
  freeAllSprites();
  deleteAllCanvases();
  Serial.printf("[Lua] Stopped. Free heap: %u B\n", esp_get_free_heap_size());
}

// ─────────────────────────────────────────────────────────────────────────────
//  Run
// ─────────────────────────────────────────────────────────────────────────────

bool runLuaScript(const char* path) {
  // Always start clean
  stopLuaScript();

  if (!LuaEngine::init()) return false;
  registerCustomLuaFunctions();

  // ── Read file from SD ──────────────────────────────────────────────────────
  if (!SD.exists(path)) {
    Serial.printf("[Lua] File not found: %s\n", path);
    LuaEngine::close();
    return false;
  }

  File file = SD.open(path);
  if (!file) {
    Serial.printf("[Lua] Failed to open: %s\n", path);
    LuaEngine::close();
    return false;
  }

  size_t len = file.size();
  char* script = (char*)malloc(len + 1);
  if (!script) {
    Serial.println("[Lua] malloc failed for script buffer!");
    file.close();
    LuaEngine::close();
    return false;
  }

  size_t readLen = file.readBytes(script, len);
  script[len] = '\0';
  file.close();

  if (readLen != len) {
    Serial.println("[Lua] File read error");
    free(script);
    LuaEngine::close();
    return false;
  }

  Serial.printf("[Lua] Running %s (%u bytes) | free heap: %u B\n",
                path, (unsigned)len, esp_get_free_heap_size());

  // ── Execute ────────────────────────────────────────────────────────────────
  lua_State* L = LuaEngine::state();
  int ret = luaL_loadstring(L, script);
  free(script);
  script = nullptr;

  if (ret != 0) {
    Serial.printf("[Lua] Compile error: %s\n", lua_tostring(L, -1));
    lua_pop(L, 1);
    LuaEngine::close();
    return false;
  }

  ret = lua_pcall(L, 0, LUA_MULTRET, 0);

  if (ret != 0) {
    const char* err = lua_tostring(L, -1);
    // Clean stop requested from inside Lua via stopLua()
    if (err && strstr(err, LUA_STOP_SENTINEL)) {
      Serial.println("[Lua] Script stopped cleanly via stopLua()");
      lua_pop(L, 1);
      LuaEngine::close();
      runningLua = false;
      return true;  // not an error — script ended itself
    }
    Serial.printf("[Lua] Runtime error: %s\n", err ? err : "(unknown)");
    lua_pop(L, 1);
    LuaEngine::close();
    return false;
  }

  runningLua = true;
  Serial.printf("[Lua] Done. Lua heap used: %u B\n", LuaEngine::heapUsed());
  return true;
}