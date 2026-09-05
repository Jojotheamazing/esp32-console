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
  
# Bill of Materials (BOM)

| Item | Usage | Quantity | Price (when bought) | Supplier/Link | Description/Notes |
|------|-------|----------|---------------------|---------------|-------------------|
| 2.8 inch TFT display module 320x240 ILI9341 (with touch panel) with SD reader | Shows the games and all the UI | 1 | 4.85€ | [AliExpress](https://a.aliexpress.com/_EIZItii) | The main (and only) screen doesn't need to be touch screen and other display drivers should be compatible if they are supported by the library (tft_espi) suggest going with a st7789v since they are faster |
| ESP32-S3 N16R8 | The processor which runs all the games and renders the music and basically everything | 1 | 4.48€ | [AliExpress](https://a.aliexpress.com/_ExT1jPM) | A simple esp32 s3 which is more powerful than the classic esp32 and with more gpios that are 100% needed. Mine came with support for external antenna which is useful. |
| MAX98357A I2S Class D amplifier | Plays the sound on the speakers | 1-2 | 2.75€ (5pcs) | [AliExpress](https://a.aliexpress.com/_EGm4xVg) | You can get either 1 or 2 based on if you want stereo sound or not. (In my project I am using only one and free gpios are limited) |
| 3-Pin Tripod Thumbwheel Toggle Switch | Used to control the volume (can be skipped) | 1 | 1.56€ (10pcs) | [AliExpress](https://a.aliexpress.com/_Eze2dMW) | It's just button which is like a rotating thingy(idk how describe it) |
| SS34 Schottky Diode | Used to block voltage back feed when the esp32 is connected on the type c for code upload | 1 | 0.50€ (50pcs) | [AliExpress](https://a.aliexpress.com/_Ez3JMAe) | It's a basic Schottky Diode which drops the voltage around 0.4 and support 1 amp 9 volts |
| 3Pin Toggle Switch 1P2T 2 Position SS12D00G2 DIP Slide Switch Handle length 3mm | Switch for turning off and on the game console system | 1 | 1.70€ (20pcs) | [AliExpress](https://a.aliexpress.com/_ExYMIee) | A simple 2 position switch can use a different one but design changes will be needed also the version of 2mm length might be better fit but 3mm is the one I used |
| 4.7k ohm resistors | Pull ups for the mcp's sda and scl pins | 2 | - | - | Just a resistor smd works too but don't recommend since it's harder to solder |
| MCP23017 Expander with I2C Interface | Connect all the buttons and only "eats" 3 gpios | 1 | 2.37€ | [AliExpress](https://a.aliexpress.com/_EuMM6o6) | Simple i2c expander because the esp32 pins aren't enough |
| DRV8833 motor driver | Drives the vibrating motors and block voltage back feeding (I hope) | 1 | 3.21€ (5pcs) | [AliExpress](https://a.aliexpress.com/_EJe5Rls) | Basic motor driver to control speed of motors |
| Mini Vibration Motors flat coin type | It vibrates the console for more haptic effect? | 2 | 2.05€ (10pcs) | [AliExpress](https://a.aliexpress.com/_Ex0j4b0) | Small little coin styled vibrating motors they work really good. |
| Limit switch 3PIN with metal arm | Used for the back left and right buttons | 2 | 1.66€ (20pcs) | [AliExpress](https://a.aliexpress.com/_EvdFDWa) | - |
| Linear voltage regulator AMS1117 3V3 | Powers every module that needs 3.3 including the mcp23017 chip the mpu6050 joysticks | 1 | 1.35€ (20pcs) | [AliExpress](https://a.aliexpress.com/_Ejuag4E) | Simple voltage regulator for 3.3 volts |
| Tactile Push Button | Buttons for controlling | 6x6x3.1 (8pcs)<br>3x6x2.5 (3pcs) | 4.12€ (box of 250pcs) | [AliExpress](https://a.aliexpress.com/_EJLsw0K) | It's a box with basically all the push buttons needed |
| M2 screws (variable lengths) | Hold everything in place securely without being bulky | - | 4.67€ (box of 482pcs) | [AliExpress](https://www.aliexpress.com/item/1005007278965396.html) | Any m2 screw will do but there are different needs for shorter or longer screws |
| Aluminum Electrolytic Capacitor 1000µF | Controls power spikes | 1 | 2.12€ (20pcs) | [AliExpress](https://a.aliexpress.com/_EINT58Q) | Needs to be at least 6 volts |
| Perfboard double sided | Board for buttons and the main board for mpu mcp motor driver max amplifier | - | 4.28€ (20pcs) | [AliExpress](https://a.aliexpress.com/_EIBvdBU) | I used pre cut prototype circuit boards but maybe a big piece would be better since I had to cut those either way |
| MPU6050 sensor | For interactive games and many cool features | 1 | 2.84€ | [AliExpress](https://www.aliexpress.com/item/1005008714169630.html) | I bought this on a sensor pack so the linked product isn't tested |
| Hall Effect Electromagnetic Joystick K-SILVER JH16 | Used for making the console gamepad "ready" and also for game/ui controlling | 2 | 12.15€ (2pcs) | [AliExpress](https://www.aliexpress.com/item/1005009646184648.html) | Those are some joysticks that are thinner than the normal 2$ modules which still offer the button click. |
