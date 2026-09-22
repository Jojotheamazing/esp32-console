#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>
#include "ButtonManager.h"
#include "JoystickHandler.h"

#define PCB_PORT            5555
#define PCB_DISCOVERY_PORT  4999
#define PCB_FRAME_BUF       (20 * 1024)
#define PCB_DISCOVERY_MS    5000

enum PCBridgeMode : uint8_t {
    PCB_MIRROR_ONLY = 0,
    PCB_MIRROR_CTRL = 1
    };

enum PCBStatus : uint8_t {
    PCB_IDLE = 0,
    PCB_DISCOVERING,
    PCB_CONNECTING,
    PCB_CONNECTED,
    PCB_FAILED,
};

void pcb_init(TFT_eSPI& tft);

void pcb_startMirror();
void pcb_startMirrorWithControl();

void pcb_stop();
void pcb_update();
bool pcb_isConnected();
PCBStatus pcb_getStatus();