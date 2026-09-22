#pragma once

#include <Arduino.h>
#include <SD.h>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#ifndef LUA_HEAP_CAP
#define LUA_HEAP_CAP (128 * 1024 * 2)
#endif


#define LUA_STOP_SENTINEL "__STOP__"

extern bool runningLua;


namespace LuaEngine {


namespace _priv {
inline lua_State* _state = nullptr;
inline size_t _used = 0;
inline size_t _cap = LUA_HEAP_CAP;

// Custom allocator — enforces the heap cap
inline void* allocator(void* /*ud*/, void* ptr, size_t osize, size_t nsize) {
  if (nsize == 0) {
    // free
    if (ptr) {
      _used -= osize;
      free(ptr);
    }
    return nullptr;
  }
  size_t delta = nsize - (ptr ? osize : 0);
  if (ptr == nullptr) {
    // fresh alloc
    if (_used + nsize > _cap) {
      Serial.printf("[Lua] OOM: want %u, used %u / %u\n",
                    (unsigned)nsize, (unsigned)_used, (unsigned)_cap);
      return nullptr;
    }
    void* p = malloc(nsize);
    if (p) _used += nsize;
    return p;
  } else {
    // realloc
    if (nsize > osize && _used + (nsize - osize) > _cap) {
      Serial.printf("[Lua] OOM(realloc): want %u, used %u / %u\n",
                    (unsigned)nsize, (unsigned)_used, (unsigned)_cap);
      return nullptr;
    }
    void* p = realloc(ptr, nsize);
    if (p) {
      _used = _used - osize + nsize;
    }
    return p;
  }
}

// Lua panic handler — called if an unprotected error escapes
inline int panic(lua_State* L) {
  Serial.printf("[Lua] PANIC: %s\n", lua_tostring(L, -1));
  return 0;  // returning from panic causes abort() in stock Lua, but on ESP32 it resets
}
}  // namespace _priv

// ── public helpers ──────────────────────────────────────────────────────────

// Raw lua_State pointer (for advanced use / extra bindings)
inline lua_State* state() {
  return _priv::_state;
}

// Current heap used by Lua
inline size_t heapUsed() {
  return _priv::_used;
}
inline size_t heapCap() {
  return _priv::_cap;
}

// Change the cap before calling init() / runLuaScript()
inline void setHeapCap(size_t bytes) {
  _priv::_cap = bytes;
}

// Register a C function by name (wraps lua_register)
inline void reg(const char* name, lua_CFunction fn) {
  if (_priv::_state) lua_register(_priv::_state, name, fn);
}

// ── init / teardown ─────────────────────────────────────────────────────────

// Tear down the current state completely and free all Lua memory
inline void close() {
  if (_priv::_state) {
    lua_close(_priv::_state);
    _priv::_state = nullptr;
    _priv::_used = 0;
  }
}

// Create a fresh Lua state with the custom allocator
// Returns false if allocation fails
inline bool init() {
  close();
  _priv::_state = lua_newstate(_priv::allocator, nullptr);
  if (!_priv::_state) {
    Serial.println("[Lua] Failed to create state!");
    return false;
  }
  lua_atpanic(_priv::_state, _priv::panic);

  // Open only the safe standard libs (no io, no os, no package — saves RAM)
  // Replace luaL_openlibs(_priv::_state); with:
  luaopen_base(_priv::_state);
  lua_settop(_priv::_state, 0);
  luaopen_table(_priv::_state);
  lua_settop(_priv::_state, 0);
  luaopen_string(_priv::_state);
  lua_settop(_priv::_state, 0);
  luaopen_math(_priv::_state);
  lua_settop(_priv::_state, 0);

  Serial.printf("[Lua] State ready — cap %u KB, free heap %u B\n",
                (unsigned)(_priv::_cap / 1024),
                (unsigned)esp_get_free_heap_size());
  return true;
}

}  // namespace LuaEngine


// ─────────────────────────────────────────────────────────────────────────────
//  Forward declarations — implemented in lua.cpp
// ─────────────────────────────────────────────────────────────────────────────
void registerCustomLuaFunctions();
bool runLuaScript(const char* path);
void stopLuaScript();
void stepLuaUpdate();