# 🎮 esp32-console

# 🔥⚒️
Before starting I want to thank Forge which helped me actually finishing this project and not throwing to my drafts!
Fully journaled project:  https://forge.hackclub.com/projects/425

All 3d models available in: https://cad.onshape.com/documents/4f867cde0156033dadc87c73/w/ddabea45654a6a1e826b5495/e/dd9f599f0ffd93bcb053a424?renderMode=0&uiState=6ab2e4172b9c8dddb3ef7906

---

## 📖 Description

This is an ESP32 S3 handheld console with many features and a sick look.
The most awsome part? You can build your own game with its simple lua API the capabilities are endless!!
Too bored to make your own game? Good news this console can also emulate NES games :D
Using an ESP32 S3 as the main brain of the console unlocks many possibilities the fast proccesing power will deliver enough performance for any (optimazed) lua game.

This project was one of my earliest ideas in the hardware/ software aspect which I repeatedly abandoned but finalled locked in to finish it. I wanted to build this project for 2 main reasons: first one I wanted to test my abilities in CAD, coding, hardware and basically designing a product from nothing and secondly because I wanted to play and create my own games which I can now do.

3D preview:
<img width="1094" height="875" alt="image" src="https://github.com/user-attachments/assets/20bc168f-a52c-466a-abdf-6b9f6ddc6211" />
<img width="1136" height="512" alt="image" src="https://github.com/user-attachments/assets/7c26e2a1-43a8-46cb-b1da-167b5e7b6199" />
<img width="1460" height="542" alt="image" src="https://github.com/user-attachments/assets/6d4bf4d8-4a21-4c94-9f54-a5df30303530" />


---

# ✨🏗️ Hardware features

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


# ✨👾 Software features

## 📶 WiFi
- Manage sd card(configure files)  

## 👾 Games
- Supports custom made lua games (with custom api)
- Supports NES emulation

## 🎵 Mucic
- Can play music saved on the SD (on the built in speakers)

## 🖥️ PC (with python on the server side)
- Connect with laptop/pc and screen mirror the pc's screen to the console (I know kinda useless but I liked)
- Controled screen mirror similiar as above but with control (such as joystick as mouse) could potentially play pc games on the console

## 🎮 Gamepad/ Steering mode
- Can act as wirelles controller (connects with windows and android only)
- Or as a steering wheel (Uses the imu sensor to track rotation and joystick for acceleration/braking)

---

# ⚠️ IMPORTANT NOTES
- In my version I use a tft display with a ili9341 display driver (40 Mhz) I however recommend using a newer ST7789 which supports up to 80 Mhz, firmware is designed for the ili9341 but can provide setup help for the newer.
- This project isn't perfect and can have some issues on fast graphics. Optimazed lua and NES games can run well with plenty fps.
- The audio is stereo which means both speakers output the same audio.
- This project requires a lot of soldering and patience wouldn't recommend for beginners
-The System expects specific SD structure please follow it or the console wont function properly.

# 🛠️ INSTRUCTIONS
In the files you will find 2 folders "MainColor" and "SecondaryColor" each containing the 3d models in .step (for each part) and a .3mf for the complete for each color. The SecondaryColor is the purple (in my build) and the MainColor the black. If you need to make any changes I recomend seeing the onshape link at the start. Some parts might be tiny and ruin the print, if you are unsure of your printer abilities you could print them in different times or with a 0.2mm nozzle. (The black filament listed is Carbon Fiber and requires harnened steel nozzle)

The wire lenghts might not apply to reality please check by roughly laying it from point a to b before cutting.

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
For the power cables I recomend a bit thicker cable such as 24-26 awg.

Now connect with 30 awg cable the scl and sda pins of the mcp to the mpu6050 (since they share the same bus)
with long pieces of 30awg cable extend the pre existing cables of the vibrating motors and then connect those to the drv8833 out1/out2 and out3/out4.
Take the 2 resitors (4.7k ohms) and connect one end to 3v3 and the other scl/sda

Lets now move to the esp32 take the cut perfboard and solder the first and last pin of the esp32 to it (at least 2 pins soldered)
and set it aside the main board (on the drv8833 side and usb ports showing the mpu6050)
Wont get in-depth here but connect the components of the main board to the esp32 based on the schematic use 30awg for all the signal cables
and 24-26 awg for power cables going from the diode to the esp32 VIN (double check the gpio pin says VIN/5v and not 3v3, impotant for not frying the chip). 

Lets now move to the joysticks what I recommend is to connect the switch pins of the joysticks to the mcp23170 before screwing the main board in the shell, the rest can be connected any time to the corresponding esp32 gpio and gnd /3v3 (Make 100% sure you take power from a 3v3 source and not a 5volt on since this will burn the esp32)

Lets now set up the switch take the 3d printed holder and place it through ( also make sure the lever lenght is around 2mm) after that procceed to connect it as the schematik shows with 24 awg I also reccomend using some heatshrinks.

This should be the hardest part but take the side button boards lay them in the correct side and connect all the disconnected cables (except the gnd) to the corresponding pin of the mcp23170 and take the gnd cables and connect them with any gnd connection you find. 

This is now the part which needs the most attention soldering the wires on the li ion cell for this I highly recommend finding a tutorial on youtube and follow it through. I have to note here that soldering directly on li ion cells can be dangerous be exctremly careful or buy lion cells with pre connected tabs/ cables. After connecting the wires secure both ends with electrical tape.
!Do not connect the battery/batteries to the powerbank module yet.!
Note: If you use 2 different cells check with a multimeter that the voltages are the same for both batteries before connecting or huge current will pass through and damage sometihng. From my own testing with one battery it has plenty play time. Make abssolutly sure that you connect them in parallel or you could burn everything. For the 2 battery version the only difference in the 3d model is the left battery cover. 

Now take both speakers and connect each tab to the other corresponding one (basically connect them in parralel) take the right speaker (them facing down) and connect 2 24awg cables at least 75mm long in the pads 
like that 

<img width="474" height="419" alt="image" src="https://github.com/user-attachments/assets/87309cd6-6dcd-4ef4-96ea-a6aa874c0a08" />

before assemling you need to also add 2 long 30awg wires (at least 170mm) to 2 free mcp pins (this will later connect to the volume control button) and one more on the ground.

now lets start the assembly make sure all the main board connections (with it self) are done and all the side buttons cables are connected same with joysticks, switch, and top buttons (not the middle one)
Firstly screw the main board and the side button boards and the esp32 in those spots 
<img width="1311" height="570" alt="image" src="https://github.com/user-attachments/assets/ced9dec4-bdef-47ea-bb1c-2c2ed7ce4453" />
The main board requires at maximum 5mm screw lenght (you can use only 2 if you want)

now peel the adhesive on the vibrating motors and slide them in these postiitons 

<img width="1054" height="419" alt="image" src="https://github.com/user-attachments/assets/a03477c7-4126-4353-856b-2f057c1517ea" />

Now for the rear buttons you will need 2 long screws 12mm recomended.
Firstly put the one spring end in the slot of the button (for both sides) and place them in the shell. Now put the limit switch and srew it in place with the other end of the spring should look like that

<img width="537" height="296" alt="image" src="https://github.com/user-attachments/assets/a3d2e84b-2fef-489e-a841-90bee10f0007" />

Take the powerbank module and screw it here

<img width="876" height="649" alt="image" src="https://github.com/user-attachments/assets/0c67ddab-f1f7-4e83-8eca-2f0d3dc29182" />

put the battery on the slot and get the cables through (make sure they dont come in contact)
Now take 26 awg cable and connect the 5v pin to the vin of the regulator and ground to any main board ground.
<img width="864" height="553" alt="image" src="https://github.com/user-attachments/assets/8dae76a5-899f-4a70-9bcb-c7a5aac8bbdf" />

Lets now move to the top shell set it flat above the bottom shell like that 
<img width="984" height="648" alt="image" src="https://github.com/user-attachments/assets/65fcd16d-8e93-42bd-bd46-9969fe617a6f" />

take the switch "Assembly" and screw it in place (make sure you add the switch cover, look at red arrow)
<img width="799" height="471" alt="image" src="https://github.com/user-attachments/assets/9ed4b0ba-0b85-43dd-aa20-91c75a6d83fa" />

I now recommend connecting the speakers to the amplifier and screwing them in the top shell using max 2.5mm scews.
Now add the tft screen and connect the signal cables (for sd car and tft) as shown in the schematic with 30 awg and the power cables with at least 26awg.
Add the volume button in here (you might need to cut the holder a bit)
<img width="664" height="729" alt="image" src="https://github.com/user-attachments/assets/ef1f0270-d752-4e67-a810-d649266efc95" />

And connect the remaining cables from before (the mcp23017 and the ground)  to these spots (red=mcp cable and black=ground)

<img width="722" height="602" alt="image" src="https://github.com/user-attachments/assets/7843de0a-eec0-455e-bb47-7fe96a0da2a8" />

I reccomend using a bit of super glue to better hold it in place but be careful not to block the rotating mechanism.

Now before connecting the battery check with a multimeter there is no continuity in the circuit between ground and V+.
If everything looks good proceed to connect the battery !IN CORRECT POLARITY! to the powerbank module (with the switch to off) 

<img width="1469" height="1011" alt="image" src="https://github.com/user-attachments/assets/e85b0459-096c-4da1-8fcb-2dcb1c6f3058" />



Lets now move on puting the whole thing together 
But firstly double check that every connection is made and you should be able to fully turn it on before closing it.

This step is optional take 4x M2 heat insterts and place them using your soldering iron in these spots (red arrows):

<img width="1319" height="557" alt="image" src="https://github.com/user-attachments/assets/89eadf54-7fe5-4e55-9c44-47c1ce7d3810" />

And screw the tft display with M3 Screws (Purple arrows) (if your screws are longer there is a little ring in the 3d files)

Put a litle standof bellow the console and put the buttons in the correct slots (check the rotation) and then screw the top buttons board.
now carefully close the console byt taking the bottom part and putting it over the top (Dont move the top shell as the buttons can fall) while closing it align the joysticks and it might need a little help in the powerbank module ports area.
Screw it with long screws 17mm minimum (if you didnt use heat inserts use longer screws 20mm minimum 23mm max)

Add all the additional designs and glue them with plastic glue (NOT FOR THE JOYSTICKS).

Final look:

<img width="640" height="480" alt="IMG_8321" src="https://github.com/user-attachments/assets/44a6afdf-188b-4aaa-b1e8-e3bcbce32ba5" />
<img width="640" height="480" alt="IMG_8322" src="https://github.com/user-attachments/assets/b8259e9a-9a71-433f-89a0-7cfe3e85d5fd" />

Thats it for any questions feel free to contact me I am more than willing to answer!!

# 👾 FIRMWARE SETUP/ GUIDE
-Most libraries can be downloaded via arduino IDE however some libraries are modified to fit the needs of the project.

-Go to documents/arduino/libraries/TFT_eSPi/User_Setups and add the "ConsoleUserSetup.h" from this repo then find the User_Setup_Select.h comment out with "//" the previous #include <....> and add the line: #include <User_Setups/ConsoleUserSetup.h>
-Before uploading any code configure the board settings in "Tools" tab in arduino IDE to this:

<img width="651" height="1051" alt="image" src="https://github.com/user-attachments/assets/fc4dd8d0-5f6a-4042-8bc6-7a8647ddf9fe" />

now upload the code this should take several minutes

-To set up the sd card first I reccomend FORMATING it to FAT32 (ALL FILES WILL BE DELETED) and then download and transfer the whole "SD CARD" folder found in this repo.
If for any reason you need to change any images/icons they need to be name exactly the same and the resolutuion should be the same.
-Configure your home wifi's ssid and password in settings.json
-Wanna add your music? Create a foler in /music this will be the playlist add any song you want in either .mp3 or .wav form (.wav is lighter on proccesing power but bigger file .mp3 required heavier proccesing but smaller file both should be perfectly fine) you can also include the info.json file found in the dummyPlaylist (only artist matters) but most importantly a "cover.jpg" which should strictly be 128x128 pixels.

-Wanna add more NES games? add any NES game file (should be .rom) in "nesGames" folder (for legal reasons I cant provide any links to find those) make sure you own the copyrights for it!

-Wanna add more Lua games? lua games are structured in folders the folder should contain a "main.lua" which is the excecutable code. Optionally you can add an icon image "Icon.bmp" (46x46) and a meta.json which includes tags which show in the game list little icons
<img width="126" height="113" alt="image" src="https://github.com/user-attachments/assets/9886e647-eceb-4e5b-b250-b48d1801ec8e" /> 

valid tags are "single" , "mpu6050" , "multi" in the meta.json you can also add the author (the creator of the game).

-Button mapping is wrong?? Connect you pc to the COM port of the esp32 open serial monitor in arduino IDE after each button press a number shows match this with the configuration in "ButtonManager.h"
<img width="677" height="811" alt="image" src="https://github.com/user-attachments/assets/79cad017-c079-42be-b7be-6d95b5d6e860" />

For further questions please contact me!

# Bill of Materials (BOM)

| Item | Usage | Quantity | Price (when bought) | Supplier/Link | Description/Notes | Actual Cost (based on quantity used) |
|---|---|---|---|---|---|---|
| 2.8 inch TFT display module 320x240 ILI9341 (with touch panel) with SD reader | Shows the games and all the UI | 1 | 4.85€ | [AliExpress](https://a.aliexpress.com/_EIZItii) | The main (and only) screen doesn't need to be touch screen and other display drivers should be compatible if they are supported by the library (tft_espi) suggest going with a st7789v since they are faster | 4.85€ |
| ESP32-S3 N16R8 | The processor which runs all the games and renders the music and basically everything | 1 | 4.48€ | [AliExpress](https://a.aliexpress.com/_ExT1jPM) | A simple esp32 s3 which is more powerful than the classic esp32 and with more gpios that are 100% needed. Mine came with support for external antenna which is useful. | 4.48€ |
| MAX98357A I2S Class D amplifier | Plays the sound on the speakers | 1 | 2.75€ (5pcs) | [AliExpress](https://a.aliexpress.com/_EGm4xVg) | You can get either 1 or 2 based on if you want stereo sound or not. (In my project I am using only one and free gpios are limited) | 0.55€ |
| 3-Pin Tripod Thumbwheel Toggle Switch | Used to control the volume (can be skipped) | 1 | 1.56€ (10pcs) | [AliExpress](https://a.aliexpress.com/_Eze2dMW) | It's just button which is like a rotating thingy(idk how describe it) | 0.16€ |
| SS34 Schottky Diode | Used to block voltage back feed when the esp32 is connected on the type c for code upload | 1 | 0.50€ (50pcs) | [AliExpress](https://a.aliexpress.com/_Ez3JMAe) | It's a basic Schottky Diode which drops the voltage around 0.4 and support 1 amp 9 volts | 0.01€ |
| 3Pin Toggle Switch 1P2T 2 Position SS12D00G2 DIP Slide Switch Handle length 3mm | Switch for turning off and on the game console system | 1 | 1.70€ (20pcs) | [AliExpress](https://a.aliexpress.com/_ExYMIee) | A simple 2 position switch can use a different one but design changes will be needed also the version of 2mm length might be better fit but 3mm is the one I used | 0.09€ |
| 4.7k ohm resistors | Pull ups for the mcp's sda and scl pins | 2 | - | - | Just a resistor smd works too but don't recommend since it's harder to solder | - |
| MCP23017 Expander with I2C Interface | Connect all the buttons and only "eats" 3 gpios | 1 | 2.37€ | [AliExpress](https://a.aliexpress.com/_EuMM6o6) | Simple i2c expander because the esp32 pins aren't enough | 2.37€ |
| DRV8833 motor driver | Drives the vibrating motors and block voltage back feeding (I hope) | 1 | 3.21€ (5pcs) | [AliExpress](https://a.aliexpress.com/_EJe5Rls) | Basic motor driver to control speed of motors | 0.64€ |
| Mini Vibration Motors flat coin type | It vibrates the console for more haptic effect? | 2 | 2.05€ (10pcs) | [AliExpress](https://a.aliexpress.com/_Ex0j4b0) | Small little coin styled vibrating motors they work really good. | 0.41€ |
| Limit switch 3PIN with metal arm | Used for the back left and right buttons | 2 | 1.66€ (20pcs) | [AliExpress](https://a.aliexpress.com/_EvdFDWa) | - | 0.17€ |
| Linear voltage regulator AMS1117 3V3 | Powers every module that needs 3.3 including the mcp23017 chip the mpu6050 joysticks | 1 | 1.35€ (20pcs) | [AliExpress](https://a.aliexpress.com/_Ejuag4E) | Simple voltage regulator for 3.3 volts | 0.07€ |
| Tactile Push Button | Buttons for controlling | 6x6x3.1 (8pcs); 3x6x2.5 (3pcs) | 4.12€ (box of 250pcs) | [AliExpress](https://a.aliexpress.com/_EJLsw0K) | It's a box with basically all the push buttons needed | 0.18€ (11pcs used) |
| M2 screws (variable lengths) | Hold everything in place securely without being bulky | - | 4.67€ (box of 482pcs) | [AliExpress](https://www.aliexpress.com/item/1005007278965396.html) | Any m2 screw will do but there are different needs for shorter or longer screws. Lengths used: 6x22mm, 5x4mm, 4x5mm, 6x8mm | ~0.20€ |
| M3 screws | Used to hold the tft screen | 4x3.5mm | - | - | No link available for these | ~ |
| Aluminum Electrolytic Capacitor 1000µF | Controls power spikes | 1 | 2.12€ (20pcs) | [AliExpress](https://a.aliexpress.com/_EINT58Q) | Needs to be at least 6 volts | 0.11€ |
| Perfboard double sided | Board for buttons and the main board for mpu mcp motor driver max amplifier | - | 4.28€ (20pcs) | [AliExpress](https://a.aliexpress.com/_EIBvdBU) | I used pre cut prototype circuit boards but maybe a big piece would be better since I had to cut those either way | 4.28€ |
| MPU6050 sensor | For interactive games and many cool features | 1 | 2.84€ | [AliExpress](https://www.aliexpress.com/item/1005008714169630.html) | I bought this on a sensor pack so the linked product isn't tested | 2.84€ |
| Hall Effect Electromagnetic Joystick K-SILVER JH16 | Used for making the console gamepad "ready" and also for game/ui controlling | 2 | 12.15€ (2pcs) | [AliExpress](https://www.aliexpress.com/item/1005009646184648.html) | Those are some joysticks that are thinner than the normal 2$ modules which still offer the button click. | 12.15€ |
| Powerbank module | Charges the li-ion battery and charges other devices | 1 | 1.11€ | [AliExpress](https://www.aliexpress.com/item/1005007300134658.html) | Basically its used as the li ion charger but it also offers 5volt output and you can charge other devices from the console | 1.11€ |
| PETG-CF filament Elegoo black | The main body filament | ~100gr | 15.78€ (0.5kg) | [Skroutz](https://www.skroutz.gr/s/66648050/elegoo-petg-cf-3d-printer-filament-1-75mm-mayro-0-5kg-50-203-0647.html?product_id=300656250&sponsored=featured_similar) | This is for refrence only its the filament I used to make my version any filament type and color will work | 3.16€ |
| PETG Purple Creality | The secondary color filament | ~20gr | 8.00€ (1kg) | [Skroutz](https://www.skroutz.gr/s/61674982/creality3d-3d-printer-filament-1-75mm-mov-1kg-3301030045.html) | This is for refrence only its the filament I used to make my version any filament type and color will work | 0.16€ |
| FEP Copper Wire 30AWG | Signal wires | ~4m | 1.5€ (10m) | [AliExpress](https://www.aliexpress.com/item/1005008851767447.html) | Just for refrence any wire 28-32 AWG will work | 0.60€ |
| 24AWG 8cm Fly Jumper Wire Tin Conductor Wires | Power higher current cable | ~14 pcs | 1.73€ (120pcs) | [AliExpress](https://www.aliexpress.com/item/1005008194967488.html) | Just for refrence any wire 22-24 AWG will work | 0.20€ |
| SD Card | Used as storage for everything | 1 | ~ | ~ | You can use any sd card available that can be formated to FAT32 | - |
| **TOTAL (sum of package/list prices actually paid)** | | | | | | **84.78€** |
| **TOTAL (actual cost of quantities used, prorated)** | | | | | | **~39.05€** |

# "Credits"
Thanks to flaticon and their amazing artists who share their creations free of charge.

<a href="https://www.flaticon.com/free-icons/gaming" title="gaming icons">Gaming icons created by Smashicons - Flaticon</a>

<a href="https://www.flaticon.com/free-icons/computer" title="computer icons">Computer icons created by Magnific - Flaticon</a>

<a href="https://www.flaticon.com/free-icons/alien" title="alien icons">Alien icons created by Freepik - Flaticon</a>

<a href="https://www.flaticon.com/free-icons/next-song" title="next song icons">Next song icons created by bsd - Flaticon</a>

And this wonderful project which made the NES emulation possible.
https://github.com/derdacavga/DSN-Nes-Emulator-Universal

<div> Icons made by <a href="https://www.flaticon.com/authors/bsd" title="bsd"> bsd </a> from <a href="https://www.flaticon.com/" title="Flaticon">www.flaticon.com'</a></div>

<a href="https://www.flaticon.com/free-icons/playback" title="playback icons">Playback icons created by bsd - Flaticon</a>
