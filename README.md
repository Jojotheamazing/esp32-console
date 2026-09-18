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

## 📳 Haptics
- 2 Vibration motors one in each side with dynamic setup  

## 🔊 Audio
- 2 Speakers for left/right (non stereo sound)
- Music loaded from sd  

## 🎮 Control
- Four buttons each side  
- 2 buttons select/start  
- Tripod button for volume control
- Top button for each each side
- Mpu6050 for more interactive games  
- On/off switch 

## ⚡ General
- Type C charging and can act as a power bank  

---

---

# ✨ Features

## 📶 WiFi
- Manage sd card(configure files)  

## 👾 Games
- Supports custom made lua games (with custom api)
- Supports NES emulation

## 🎵 Mucic
- Can play music saved on the SD (on the built in speakers)

## 🖥️ PC (with python on the server side)
- Connect with laptop/pc and screen mirror the pc's screen to the console (i know kinda useless but i liked)
- Controled screen mirror similiar as above but with control (such as joystick as mouse) could potentially play pc games on the console

## 🎮 Gamepad/ Steering mode
- Can act as wirelles controller (connects with windows and android only)
- Or as a steering wheel (Uses the imu sensor to track rotation and joystick for acceleration/braking)

---

# ⚠️ IMPORTANT NOTES
- In my version i use a tft display with a ili9341 display driver (40 Mhz) I however recommend using a newer ST7789 which supports up to 80 Mhz, firmware is designed for the ili9341 but can provide setup help for the newer.
- This project isn't perfect and can have some issues on fast graphics. Optimazed lua and NES games can run well with plenty fps.
- The audio is stereo which means both speakers output the same audio.
- This project requires a lot of soldering and patience wouldn't recommend for beginners
# 🛠️ INSTRUCTIONS
The wire lenghts might not apply to reality please check by roughly laying it from point a to b.

First step: perfboard cutting
Tools: I recomend a cutting razor for the cutting or diagnal cutiing pliers, for the holes you need a 2mm drill bit and a dremel/ drill

You are going to need to cut 5 perfboard pieces in these dimensions
<img width="3508" height="2480" alt="Part 1 Drawing 1 (1)" src="https://github.com/user-attachments/assets/342a46b5-e794-453f-97f4-50943dcb663e" />

As you can see we need 2 side boards these should strictly be 12x12 pins, the main board doesnt have any strict pin number just make sure you can fit all the components on it (lay them on it before cutting it),
then the hardest to get right is the esp32-s3 mount board this needs just a row of pins but its hard to line the usb ports correctly and lastly the top button board this should be 3 pins wide.

There are many methods to cut them if you are struggling you can search a tutorial online.

After cutting your perfboard to the specified dimension and drilling the mounting holes its time to prepare each one of them.

We will start with the smaller square perfboards those are the side boards where the buttons will be on. So for this step we need 8x Tactile Push Buttons and thin wire (recommend 30awg) and soldering equipment
These buttons:
<img width="480" height="640" alt="image0 (9)" src="https://github.com/user-attachments/assets/2109e837-b930-483b-8917-4ca00afb7434" />


Firstly set the board falt on the table and put the buttons in this pattern
<img width="588" height="550" alt="image" src="https://github.com/user-attachments/assets/47ab0237-228d-40a3-9b5d-9a22adff8014" />

Securely solder them on the board you can either solder 2 diagnol pins or all 4 of them after that flip the board over here is where you need the wire you now need to connect all the ground pads together 
Like that:
<img width="480" height="640" alt="IMG_7884" src="https://github.com/user-attachments/assets/147abe67-274e-422f-827f-8fa6681f0f1c" />

Now you need to cut long pieces of wires: 5x 140mm and 5x 55mm
The shorter pieces are for the left side you should connect 1 piece to each button and leave the other end unconnected and the fifth cable should connect to the common ground
The longer pieces are for the right side same as above.

Now we will connect the top buttons: take 2 limit switches
on the one connect the ground pin to the left common ground on the button board (1cm wire) and the other pin to a 55mm wire and leave the other end disconnected
on the other same for ground but the other cable should be 140mm long

Nice you have now finished the side button boards!
Lets move to the Top button board this is really simple you need 3 tactile buttons of this kind 
<img width="480" height="640" alt="image3" src="https://github.com/user-attachments/assets/0fe83089-103f-44b8-93f4-5b06eee87e53" />

lay the buttons like that
<img width="1148" height="201" alt="image" src="https://github.com/user-attachments/assets/b2316f1e-0f99-4ccb-adbe-aaa1de1ee56a" />
secure both ends with solder then connect one pad of each button to the other.
Then cut 3 long 30 awg cable 2x140mm and 1x150mm
The longest cable should be soldered to the center button and the other 2 wires to the 2 remaining buttons.

YAY done with the top button board as well (for now :D)!!
Next step the main board this should be a bit demanding the placement of each compent can be changed but make sure you calculate the wire lenght correctly and they wont intersect with an other stuff (especially the sd card slot of the tft screen)
Firstly lay all the compnets the board like that (The mpu6050 and the max9857A shouldnt have header pins) 
<img width="834" height="724" alt="image" src="https://github.com/user-attachments/assets/6fe91240-c20a-4d10-9163-b8b7858dd66b" />
(Also add the diode somewhere on the board and the 2 resitors 4.7kohm for the mcp23170)
secure everything on the board with solder.
Now flip the board and connect the 3v3 output from the regulator to both the mpu6050 and the mcp230170.
Connect all the ground pads together.
Now you need to make sure not to mess this up as it can damage the components
connect the regulator voltage input (we will connect the 5volts on it later) to the drv8833 input, the amplifier's input and to the the diode.
For the power cables i recomend a bit thicker cable such as 24-26 awg.

Now connect with 30 awg cable the scl and sda pins of the mcp to the mpu6050 (since they share the same bus)
with long pieces of 30awg cable extend the pre existing cables of the vibrating motors and then connect those to the drv8833 out1/out2 and out3/out4.
Take the 2 resitors (4.7k ohms) and connect one end to 3v3 and the other scl/sda

Lets now move to the esp32 take the cut perfboard and solder the first and last pin of the esp32 to it (at least 2 pins soldered)
and set it aside the main board (on the drv8833 side and usb ports showing the mpu6050)
Wont get in-depth here but connect the pins of the main board to the esp32 based on the schematic use 30awg for all the signal cables and 24-26 awg for power cables. 

Lets now move to the joysticks what i recommend is to connect the switch pins of the joysticks to the mcp23170 before screwing the main board in the shell, the rest can be connected any time to the corresponding esp32 gpio and gnd /3v3 (Make 100% sure you take power from a 3v3 source and not a 5volt on since this will burn the esp32)

Lets now set up the switch take the 3d printed holder and place it through ( also make sure the lever lenght is around 2mm) after that procceed to connect it as the schematik shows with 24 awg i also reccomend using some heatshrinks.

This should be the hardest part but take the side button boards lay them in the correct side and connect all the disconnected cables (except the gnd) to the corresponding pin of the mcp23170 and take the gnd cables and connect them with and gnd connection you find.

This is now the part which needs the most attention soldering the wires on the li ion cell for this i highly recommend finding a tutorial on youtube and follow it through. I have to note here that soldering directly on li ion cells can be dangerous be exctremly careful or buy lion cells with pre connected tabs/ cables.

  
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
