#include "PCBridge.h"
#include "display.h"
#include <string.h>

static WiFiClient _client;
static WiFiUDP _udp;

static uint8_t _rxScratch[PCB_FRAME_BUF];
static uint8_t _frameBuf[PCB_FRAME_BUF];
static uint32_t _frameLen = 0;
static volatile bool _frameReady = false;
static SemaphoreHandle_t _frameMutex = nullptr;

static SemaphoreHandle_t _txMutex = nullptr;
static TaskHandle_t _rxTask = nullptr;
static SemaphoreHandle_t _clientMutex = nullptr;

static volatile bool _taskRunning = false;

static PCBridgeMode _mode = PCB_MIRROR_ONLY;
static volatile bool _running = false;
static volatile PCBStatus _status = PCB_IDLE;
static char _serverIP[24] = { 0 };

static uint32_t _lastJoyMs = 0;
static int8_t _lastLX = 0, _lastLY = 0, _lastRX = 0, _lastRY = 0;

static bool _pcbJpegOutput(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap) {
  if (y >= tft.height()) return 0;
  tft.pushImage(x, y, w, h, bitmap);
  return 1;
}

static bool tcpReadFull(uint8_t* dst, uint32_t len) {
  uint32_t received = 0;
  uint32_t deadline = millis() + 3000;

  while (received < len) {
    if (!_running) return false;
    if (!_client.connected()) return false;
    if (millis() > deadline) return false;

    int chunk = 0;

    if (xSemaphoreTake(_clientMutex, pdMS_TO_TICKS(10)) == pdTRUE) {
      chunk = _client.read(dst + received, len - received);
      xSemaphoreGive(_clientMutex);
    }

    if (chunk > 0) received += chunk;
    else if (chunk < 0) return false;
    else taskYIELD();
  }
  return true;
}

static bool tcpDrain(uint32_t len) {
  uint8_t tmp[64];
  uint32_t rem = len;
  uint32_t deadline = millis() + 3000;

  while (rem > 0) {
    if (!_running || !_client.connected()) return false;
    if (millis() > deadline) return false;

    int c = 0;

    if (xSemaphoreTake(_clientMutex, pdMS_TO_TICKS(10)) == pdTRUE) {
      c = _client.read(tmp, min(rem, (uint32_t)sizeof(tmp)));
      xSemaphoreGive(_clientMutex);
    }

    if (c > 0) rem -= c;
    else if (c < 0) return false;
    else taskYIELD();
  }
  return true;
}

static void sendBytes(const uint8_t* data, size_t len) {
  if (!_client.connected()) return;

  if (xSemaphoreTake(_txMutex, pdMS_TO_TICKS(5)) == pdTRUE) {

    if (xSemaphoreTake(_clientMutex, pdMS_TO_TICKS(5)) == pdTRUE) {
      _client.write(data, len);
      xSemaphoreGive(_clientMutex);
    }

    xSemaphoreGive(_txMutex);
  }
}

static bool discoverServer() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[PCB] WiFi not connected, aborting discovery");
    return false;
  }
  Serial.println("[PCB] Scanning for server...");
  _udp.begin(PCB_DISCOVERY_PORT);

  char buf[32];
  uint32_t start = millis();

  while (millis() - start < PCB_DISCOVERY_MS) {
    if (!_running) {
      _udp.stop();
      return false;
    } 

    int len = _udp.parsePacket();
    if (len > 0) {
      int toRead = min(len, (int)sizeof(buf) - 1);
      _udp.read(buf, toRead);
      buf[toRead] = '\0';
      if (strncmp(buf, "PCBRIDGE_SERVER", 15) == 0) {
        strncpy(_serverIP, _udp.remoteIP().toString().c_str(), sizeof(_serverIP) - 1);
        Serial.printf("[PCB] Found server at %s\n", _serverIP);
        _udp.stop();
        return true;
      }
    }
    delay(10);
  }
  _udp.stop();
  Serial.println("[PCB] No server found");
  return false;
}

static void onButton(ButtonID id, InputEvent evt) {
  if (evt != EVT_PRESSED && evt != EVT_RELEASED) return;
  uint8_t pkt[3] = { 0x01, (uint8_t)id, evt == EVT_PRESSED ? 1u : 0u };
  sendBytes(pkt, 3);
}

static void rxTask(void* param) {
  _taskRunning = true;
  Serial.println("[PCB] RX task started");

  _status = PCB_DISCOVERING;
  if (!discoverServer()) {
    Serial.println("[PCB] Could not find server");
    _status = PCB_FAILED;
    _running = false;
    _taskRunning = false;
    vTaskDelete(nullptr);
    return;
  }

  _status = PCB_CONNECTING;

  while (_running) {

    if (!_client.connected()) {

      Serial.printf("[PCB] Connecting to %s:%d\n", _serverIP, PCB_PORT);

      if (xSemaphoreTake(_clientMutex, pdMS_TO_TICKS(100)) == pdTRUE) {
        bool ok = _client.connect(_serverIP, PCB_PORT);
        xSemaphoreGive(_clientMutex);

        if (!ok) {
          for (int i = 0; i < 10 && _running; i++)
            vTaskDelay(pdMS_TO_TICKS(100));
          continue;
        }
      }

      _client.setNoDelay(true);
      Serial.println("[PCB] Connected!");
      _status = PCB_CONNECTED;

      uint8_t modePkt[2] = { 0x00, (uint8_t)_mode };
      sendBytes(modePkt, 2);
    }

    uint8_t tag = 0;
    if (!tcpReadFull(&tag, 1)) {
      continue;
    }

    if (tag == 0xFF) {
      uint32_t size = 0;

      if (!tcpReadFull((uint8_t*)&size, 4)) continue;
      if (size == 0) continue;
      if (size > PCB_FRAME_BUF) {
        tcpDrain(size);
        continue;
      }

      if (!tcpReadFull(_rxScratch, size)) continue;

      if (xSemaphoreTake(_frameMutex, pdMS_TO_TICKS(20)) == pdTRUE) {
        memcpy(_frameBuf, _rxScratch, size);
        _frameLen = size;
        _frameReady = true;
        xSemaphoreGive(_frameMutex);
      }
    } else {
      uint16_t plen = 0;

      if (!tcpReadFull((uint8_t*)&plen, 2)) continue;

      if (plen > 0) {
        uint8_t pbuf[256];

        if (plen <= sizeof(pbuf)) {
          if (!tcpReadFull(pbuf, plen)) continue;
        } else {
          tcpDrain(plen);
        }
      }
    }
  }

  
  if (xSemaphoreTake(_clientMutex, pdMS_TO_TICKS(100)) == pdTRUE) {
    _client.stop();
    xSemaphoreGive(_clientMutex);
  }

  Serial.println("[PCB] RX task ended");
  _taskRunning = false;
  vTaskDelete(nullptr);
}

static void startInternal() {
  _running = true;
  _status = PCB_IDLE;
  _frameReady = false;
  _frameLen = 0;

  if (!_frameMutex) _frameMutex = xSemaphoreCreateMutex();
  if (!_txMutex) _txMutex = xSemaphoreCreateMutex();
  if (!_clientMutex) _clientMutex = xSemaphoreCreateMutex();

  if (_mode == PCB_MIRROR_CTRL)
    Input.addListener(onButton);

  xTaskCreatePinnedToCore(rxTask, "pcb_rx", 8192, nullptr, 1, &_rxTask, 1);
  Serial.println("[PCB] Started");
}

void pcb_init(TFT_eSPI& tftRef) {
  (void)tftRef;
  Serial.println("[PCB] PCBridge ready");
}

void pcb_startMirror() {
  _mode = PCB_MIRROR_ONLY;
  startInternal();
}

void pcb_startMirrorWithControl() {
  _mode = PCB_MIRROR_CTRL;
  startInternal();
}

void pcb_stop() {
  if (!_running && !_taskRunning) {
    Input.removeListener(onButton);
    tft.fillScreen(TFT_BLACK);
    _status = PCB_IDLE;
    return;
  }

  _running = false;
  Input.removeListener(onButton);

  uint32_t waitStart = millis();
  while (_taskRunning && millis() - waitStart < 2000) {
    vTaskDelay(pdMS_TO_TICKS(10));
  }

  if (_taskRunning) {
    Serial.println("[PCB] RX task did not exit cleanly — forcing delete");
    if (_rxTask) vTaskDelete(_rxTask);
    _taskRunning = false;
  }

  _rxTask = nullptr;

  tft.fillScreen(TFT_BLACK);
  _status = PCB_IDLE;
  Serial.println("[PCB] Stopped");
}

void pcb_update() {
  if (_frameMutex && xSemaphoreTake(_frameMutex, 0) == pdTRUE) {
    if (_frameReady && _frameLen > 0) {
      _frameReady = false;
      TJpgDec.setCallback(_pcbJpegOutput);
      tft.startWrite();
      TJpgDec.drawJpg(0, 0, _frameBuf, _frameLen);
      tft.endWrite();
      TJpgDec.setCallback(tft_output);
    }
    xSemaphoreGive(_frameMutex);
  }

  if (_mode == PCB_MIRROR_ONLY) return;
  if (millis() - _lastJoyMs < 50) return;
  _lastJoyMs = millis();

  int8_t lx = (int8_t)getLX();
  int8_t ly = (int8_t)getLY();
  int8_t rx = (int8_t)getRX();
  int8_t ry = (int8_t)getRY();

  if (lx != _lastLX || ly != _lastLY || rx != _lastRX || ry != _lastRY) {
    uint8_t pkt[5] = { 0x02, (uint8_t)lx, (uint8_t)ly, (uint8_t)rx, (uint8_t)ry };
    sendBytes(pkt, 5);
    _lastLX = lx;
    _lastLY = ly;
    _lastRX = rx;
    _lastRY = ry;
  }
}

bool pcb_isConnected() {
  return _running && _client.connected();
}

PCBStatus pcb_getStatus() {
  return _status;
}