# 🎮 esp32-console

> Big note: this repo is kinda old when it comes to code and wiring but will update with the code and libraries and everything once i find some time. Thanks

# 🛠️ Under construction

Project is journalled daily in forge🔥⚒️: https://forge.hackclub.com/projects/425

---

## 📖 Description

Using an ESP32 s3 as the main brain of the console unlocks many capabilities.  
The main goal is to create a stable and functional handheld console with mostly cheap components so anyone can replicate it and is fun to use.


---

# ✨ Features

## 📶 WiFi **[ADDED]** EXCEPT SKETCH
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
- Mic for recording or audio interactive games (optional) 

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

# ⚠️ IMPORTANT NOTES
- In my version i use a tft display with a ili9341 display driver (40 Mhz) I however recommend using a newer ST7789 which supports up to 80 Mhz firmware is designed for the ili9341 but can provide set up help for the newer.
- This project isn't perfect and can have some issues on fast graphics. Optimazed lua and NES games can run well with plenty fps.
- The audio is stereo which means both speakers output the same audio.

# 🛠️ INSTRUCTIONS
  
