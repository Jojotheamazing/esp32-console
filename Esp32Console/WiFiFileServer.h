#pragma once


#include <Arduino.h>

enum class WfsMode { STA,
                     AP };

bool wfsStart(WfsMode mode,
              const char* ssid,
              const char* password = "",
              uint32_t timeoutMs = 10000);


void wfsLoop();


void wfsStop();


bool wfsRunning();
String wfsIP();