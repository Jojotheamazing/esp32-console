# 🎮 esp32-console

> Big note: this repo is kinda old when it comes to code and wiring but will update with the code and libraries and everything once i find some time. Thanks

---

## 📖 Description

Using an ESP32 s3 as the main brain of the console unlocks many capabilities.  
The main goal is to create a stable and functional handheld console with mostly cheap components so anyone can replicate it.

---

# ✨ Features

## 🔵 Bluetooth **[ADDED]** turned off
- Scan for devices  
- Connect to device  
- Play audio from device
  EXCEPT:
- Play audio to device  
- Maybe connect external controller  

## 📶 WiFi (maybe) **[ADDED]** EXCEPT SKETCH
- Create WiFi network  
- Connect to pc/phone  
- Manage sd card(configure files)  
- Upload music/ organise music  
- Upload sketch(maybe)  

## 📳 Haptics
- 2 Vibration motors one in each side with dynamic setup  

## 🔊 Audio
- 2 Speakers for left/right  
- Music loaded from sd  
- Features stated in Bluetooth(bt sink/source)  
- Mic for recording or audio interactive games  

## 🎮 Control
- Four buttons each side  
- 2 buttons select/start  
- Smd button for volume control/mute  
- Mpu6050 for more interactive games  
- Maybe top button each side  
- On/off switch  
- Possible feature stated in bluetooth(external controller)  

## ⚡ General
- Type C charging and can act as a power bank  
- LED purple lights  

---

# ⚠️ Issues currently facing

- Esp32 classic lacks ram for both Bluetooth and lua. Planning on changing to esp32 s3 however s3 doesn’t support Bluetooth classic therefore no Bluetooth source/sink ability (possible solution: double chip esp32 s3 for heavy work and esp32 classic for Bluetooth)

- Pam amplifier no good will switch to max (excuse me I don’t remember the exact components)

- Lua wrapper library lacking features  
  **[FIXED]** changed library to lua 5.1 for esp32

---

# 🛠️ Plan

- Design it on a breadboard  
- Do all the fixing and coding on the breadboard  
- Move to making the case and soldering everything
- Might make a pcb if it gets too big but i have no idea how so need to learn first
  
