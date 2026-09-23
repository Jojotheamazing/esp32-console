---
title: "ESP32-Based Handheld Gaming Console"
author: "Jojo"
description: "Game boy inspired console uses the power of the esp32 chip and more amazing features such as bluetooth music player."
created_at: "2026-05-16"
---

# 2026-09-22: Git finalazing

**Total time spent: 1 hour 20 minutes**

The github repo is finally in finishing stages i started adding the needed files such as the code, and the 3d models i also added a guide to add more lua/nes games and music and an "SdCard" folder which has the main structure the sd card needs.
![image.png](https://cdn.hackclub.com/01a0cade-d2a7-7535-8345-752dd3d01c9b/image.png)
Linked the onshape project as well and fixed some typos
![image.png](https://cdn.hackclub.com/01a0cadf-59e3-7b8e-8a9b-7d18d342cacb/image.png)
continued writing the firmware setup which needs some more details for the asjusted libraries
![image.png](https://cdn.hackclub.com/01a0cae0-4ff0-73e7-86f8-cc0b05618acc/image.png)
I changed some icons for the console menu for the PC tab and the games tab.
I will finish adding all the 3d models in the repo tomorrow the thing is that i want to split them to 2 sections main color and secondary color but the onshape document isnt organised.

# 2026-09-21: Github readme and BOM.

**Total time spent: 1 hour 10 minutes**

I feel embarrassed to say that i yet spend an other hour+ writing the github repo but i sped up the whole proccess by cutting some details. i hope tomorrow i will complete the repo and will finally sumbit the project. I also finalized the BOM adding filament wires and a module i forgot.
Wont flood the whole journal with screenshots so here are some snippets
![image.png](https://cdn.hackclub.com/01a0c5b7-fbbe-7dee-bd35-55ad217f6141/image.png)
![image.png](https://cdn.hackclub.com/01a0c5b8-1f74-7cfb-b4bd-201ec6ca8cf7/image.png)
![image.png](https://cdn.hackclub.com/01a0c5b8-4c09-73e6-ae3b-62d938488bce/image.png)

# 2026-09-20: GitHub instructions pt3 aesthetics

**Total time spent: 1 hour 2 minutes**

I finally completed the assembly by also adding the battery covers and all of the aesthetic details. For the battery covers I used a different design holding on to the shell differently so it doesn’t intersect with the battery the cover for the empty one is much thicker because there is enough space. ![image.jpeg](https://cdn.hackclub.com/01a0c085-09a0-7416-a24f-ec082b9efacd/image.jpeg)![image.jpeg](https://cdn.hackclub.com/01a0c085-48a2-7f79-b4fa-38c2bd513ac2/image.jpeg)
I also continued the GitHub repo writing process and fixed some typos and some parts where I was unclear. 

# 2026-09-19: GitHub readme pt2

**Total time spent: 1 hour 15 minimum**

Today I wrote more of the read me I spend a lot of time writing so I might make this faster and skip some details. I also looked around the code and delete some logic that was removed either way. ![upload failed]()![image.png](https://cdn.hackclub.com/01a0bb42-eb6e-7502-89ec-f7025beab212/image.png)![Uploading image.png...]()

# 2026-09-18: Github readme instructions pt1

**Total time spent: 2.5 hours**

At first i started by making the volume bar disapearing which i had forgotten to add when i first made it, i know this aproach isnt perferct and has bugs but any other would be too complicated for low improvement so i will stick with this.
![image.png](https://cdn.hackclub.com/01a0b647-e21e-7bed-bd19-efa884bd6fb8/image.png)

But i also did what i hate the most writing the github repo i dont have much to say for this only that i started writing the instructions and i dont know how in-depth i should go, also its hard describing so trying to explain it the mostly with images (which is kinda hard because i cant find any old photos from when assembling) Also i know i got a lot of gramtical and spelling mistakes but i will fix them an other time. Oh i forgot to say that i added a list of the features that it has (firmware side)
![image.png](https://cdn.hackclub.com/01a0b64b-206c-70a3-a96f-e82371ab923b/image.png)
![image.png](https://cdn.hackclub.com/01a0b64b-5690-74a9-b3ce-a12ab019bbb3/image.png)
![image.png](https://cdn.hackclub.com/01a0b64b-9fcc-7dc6-85c6-783d2fcce50d/image.png)
i dont want to fill this journal with images from the repo so i will just leave only those 

# 2026-09-17: Steering tab design 

**Total time spent: 1 hour 10 minutes**

So for starters I fixed the text that was out of bounds and it looks pretty nice![image.jpeg](https://cdn.hackclub.com/01a0b0d1-84f4-73d4-8ddd-138a65697387/image.jpeg) 
I also changed the steering wheel image as I mentioned yesterday but I implemented it correctly with the correct pivot and now it rotates as it should however I now see a bug that I know exactly from where it is caused but will fix tomorrow (the slider doesn’t draw when the yValue is 0 yep I added an if which causes that will remove it later)
![image.jpeg](https://cdn.hackclub.com/01a0b0d3-9ddc-726b-8e6f-f12b6764a937/image.jpeg) 
I like it pretty much I also test drove it and it is kinda hard but fun. Lastly I added the button presses also register in the steering mode so you can change how it accelerates from the game setting (for example when pressing a button) however then the ui won’t get updated 

# 2026-09-16: Firmware fixes pt2 and nes saves

**Total time spent: 1 hour 24 minutes**

Today i started by working in the save of progress for nes games i could say it wasnt that hard because the main concept was already included by the emulator but the library didnt put it in use so after some changes in the library's code i got it working like fixing the function osd_newextension and osd_fullname and adding load file and save file but i was devestated because i mostly did this so i can save my progress in super mario but found out that super mario doesnt support it and never did and only limited games did so i tried it with zelda and it worked fine. I also fixed the volumebar that crashed the whole system while running the emulator fix was simple just added a extern SemaphoreHandle_t tftMutex; in osd and display and the just run checks for it ![image.png](https://cdn.hackclub.com/01a0ab30-19c5-7a06-a743-8e3e8146d2be/image.png) ![image.png](https://cdn.hackclub.com/01a0ab30-5860-720b-8767-9a08c88605c3/image.png) 

also added the accelerator and braking on the joystick and designed a screen in pixlr e and i need to put it to the console will do it later tho ![image.png](https://cdn.hackclub.com/01a0ab9b-3cd2-7900-8528-2f07e4deb332/image.png)

# 2026-09-15: Firmware general fixes

**Total time spent: 1 hour 34 minutes**

As promised yesterday i started fixing some issues with the code that existed here and there here is a full list of things fixed and if i faced any difficulties while fixing them.

~When you were in the control tab (menu) and pressed back button the main tab selection didnt draw i found out thati had added a filter on the  onInput function in the tab manager so it explicity passes the input to the control tab so it has the EVT_RELEASED as well but i forgot to add this check so it returned after each button without checking if it has left fix just added && evt == EVT_RELEASED
![image.png](https://cdn.hackclub.com/01a0a6ad-f909-77c8-bb7b-9f295b4abde9/image.png) a bit later in the code ![image.png](https://cdn.hackclub.com/01a0a6ae-3496-7fa3-b5a1-e7462215ef13/image.png)

¬Added when you press select& start you leave from the gamepad/steering mode migfht have to add an in between menu for confirmation was supper simple because button manager already has what i needed so no need for bool values ![image.png](https://cdn.hackclub.com/01a0a6af-9bce-7937-9e68-b8dc27845542/image.png)

¬Removed: from pc tab "pc games" since it never worked or could work, from the setting tab "brightness" since there is physically (hardware wise) not a way to control it and "Audio output" since there are only speakers and bluetooth is no longer supported.

~When adjustiong the audio from the buttons the setting value didntt save so on a second power up and changes in volume were lost (only on the button) also made them change the values faster because they were painfully slow
On the same "scope" i started adding the volume bar so you can visualize where the volume is set so you dont get earbang here is how i am planning on doing it ![image.png](https://cdn.hackclub.com/01a0a6cb-8c5e-7c32-b8ab-aebda9151cac/image.png) i have to think some other logic stuff on how it will work such as what will happen to the back groung on which it gets drawn on like when it goes away

# 2026-09-14: Sanding and battery fix

**Total time spent: 1 hour 2 minutes**

So today I did the things I least expected to. For starters I sanded the buttons the front decor( the heart and the star) since I had the dremel out idk if it looks any better on the photos but it definitely feels smoother here is a close up look of the before ![image.jpeg](https://cdn.hackclub.com/01a0a194-60df-783a-ae30-dd9d5ba96fa9/image.jpeg) and here is the after ![image.jpeg](https://cdn.hackclub.com/01a0a194-d3d6-747c-aa6f-87286aa4cf16/image.jpeg)
I also did some messing around to find the fixes needed in the firmaware and what needs to be added and I wrote them down ![image.jpeg](https://cdn.hackclub.com/01a0a196-3f9a-79ac-bee0-347c534a5f05/image.jpeg) I forgot to write that I need to add the acceleration and braking in the steering mode and maybe some kind of ui for the gamepad mode. I also found a fork of the library I am using the esp32 ble gamepad that supports dual sense and xinput which might let me use the haptics and more features but I don’t know if I will switch to it any time soon. 
Another thing I didn’t expect to do is resoldering the battery. The problem with the battery was the excessive amount of solder I use and electrical tape so when I was trying to remove them the cables got cut off so I had to go through 2 heart attacks (i thought I had shorted the battery like melted the plastic) and some time it’s now even better than before(fits a bit better on the compartment but still don’t know if the battery cover will fit) 
![image.jpeg](https://cdn.hackclub.com/01a0a19a-8f5d-73c5-81ac-5d06f57de5d2/image.jpeg)

# 2026-09-13: Assembly fixes and joystick cap 

**Total time spent: 1 hour 10 minutes**

So most of the things I did today I don’t have a lapse for because I didn’t have my phone with me I can say the hardware is 100% done same should be the 3d design now I have to 3d print the last back decoration and I need to glue it and maybe sand it a bit after. I have a problem with the battery cover that idk if it will fit. I made little pads for the joysticks after some attempts they are pretty good but they look kinda funny because they are too tall I was thinking of cutting the joystick a bit but I didn’t want to damage it also idk if black color would fit better. I also fixed the button mapping because I had reconnected a few wires differently and fixed the on game menu for the nes games (the text was off center and was messy). I remember doing more stuf but it was probably just the screwing and unscrewing I did. Oh I also made the buttons a bit thinner because when screwed they were constantly pressed and made the back buttons smaller because they were blocked by the shell and lastly I cut a bit of the shell near the battery with a dremel because the cutout wasn’t printed for some reason(I don’t have a picture and I can’t reopen because it’s a bit difficult to put the buttons correctly and close it without them falling out)
![image.jpeg](https://cdn.hackclub.com/01a09c68-632f-7fc3-a44c-86a816fd8ce4/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/01a09c68-84a2-78aa-80ec-601ae361ae25/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/01a09c68-add0-7fdf-b96d-135cab83b8ff/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/01a09c68-d5f8-78d4-80e9-8d2e59dc54b9/image.jpeg)

# 2026-09-12: Last assembly and hopefully soldering

**Total time spent: 2hour 50 minutes**

I don’t know what took so much time even though I did a lot of stuff. So finally I printed the shell in the filament I wanted the design is pretty solid only a few minor issues which were fixed like the tft screen mounting holes were too small and I couldn’t screw it but I just bade it a bit bigger with a screwdriver.  What took the longest was the soldering I had to replace a lot of cables that were too short to connect and of course resoldering vcable that disconnected continuously. I also put the heat inserts. There was a problem with the battery compartment and the battery couldn’t fit and I don’t know if it will close with the cover. Lastly I soldered the joysticks and the volume control button and everything is set I closed it up without screwing it to see if it closes and it does. Now I need to put some tape to hold specific cables and maybe something with the speakers and everything will be ready. ![image.jpeg](https://cdn.hackclub.com/01a096f3-6c66-75e7-beff-7e1b12f828b5/image.jpeg)![image.jpeg](https://cdn.hackclub.com/01a096f3-9756-727c-9c54-51f70e125765/image.jpeg)![image.jpeg](https://cdn.hackclub.com/01a096f3-ccdb-71c5-8219-32159be5df5b/image.jpeg) (this isn’t the final because there are some purple decor missing) forgot to mention that the select and start button have the text a bit messed up so I might have to print again with 0.2mm nozzle

# 2026-09-11: 3d design finalisation and solder fixes 

**Total time spent: 1 hour 2 minutes**

For starters I fixed some cables that were cut off and I had to resolver them it a common thing because I haven’t closed it or screwed everything in place so sudden moves tension the cables and disconnect them so I only reconnect the vital ones as the power button and the sd and tft so I can still write and test code. (Just a few hours later and more cables broke
![image.jpeg](https://cdn.hackclub.com/01a0922f-ea0c-74f7-bafd-f7ab200471f6/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/01a09230-0ff5-7c0e-861b-1e8a027404fd/image.jpeg)
I really can’t remember everything that I did today because it was mostly small potato stuff so I forgot. In the 3d design I made a little cutout for the batteries because with the cables soldered they become longer and a small cutout for the bottom cables 
![image.png](https://cdn.hackclub.com/01a09231-f54f-7a7e-aa4e-ec7f1e1edb20/image.png)
I also did some general minor fixes but I can’t recall them all as I said but it’s ready to be printed !!! I sliced it ![image.png](https://cdn.hackclub.com/01a09232-b229-700d-84aa-f4cbf53fae7c/image.png) but I am waiting for the filament to dry a bit ![image.jpeg](https://cdn.hackclub.com/01a09233-5b56-7a16-b0d3-fcca37a0e3e7/image.jpeg) i will
Put it before sleeping so tomorrow it will be ready for assembly!

# 2026-09-10: Battery placement alternatives 

**Total time spent: 1 hour 9 minutes**

So today I received the new joystick and they are pretty pretty good but it got me thinking if I can place the batteries else where so I know it’s a bit stupid from but I sat and started redesigning around a different battery placement that I knew I probably wouldn’t use to see if it would be better. Long story short it took me over 1 hour and I came to the conclusion it doesn’t even make a difference. The main issue is the thickness (it’s not very thick but I wanted it as thin as possible) but in the newer design instead of joystick being the issue the buttons were maybe at best I would be saving 1-2 mm which isn’t anything significant. So I gave up on the redesign and stuck with the old one I inspected it a bit to see if it’s ready to print but I didn’t go through everything so tomorrow I will check once more (double checking because I don’t have a lot of the specific filament and I want to get the most out of it) and finally send it to the printer within the next days I should have finished the whole hardware-3d section and move to the final touches in ui and coding and lastly the GitHub repo should be done by the end of the next week. 
![image.png](https://cdn.hackclub.com/01a08d1b-b631-7453-8ce9-789a3260ff88/image.png)
(Other pictures can’t load so will update tomorrow)

# 2026-09-08: Graphics system improvements (canvas system)

**Total time spent: 1 hour 10 minutes**

I don’t have anything much to say for today I just did what I mentioned I would yesterday. That is making a “2 phase” draw system nothing but it’s something I should have thought of from the start. there are canvas which have been added to the sprite manager (will probably rename it to graphics manager because it more generic now) they have similar methods as the sprites such as create canvas with a unique name identifier width height and bg color more functions are deleteCanvas(name) delete all canvases, clear canvas which basically just fill the whole thing in the bg color I have made a struct that holds all the info width, height, name etc. and also changed the sprite logic by adding a target value on the function (if left nil it just pushes directly to the tft if target exists it draws to the corresponding canva). So the system is simple create a canvas-> draw anything on it text, images, shapes -> push it to the tft (actual render) this should
Make the screen less flickery. I also added the functions to the lua that will most likely be needed but lua needed extra care for the text and I forgot to add shapes on the lua. I don’t have anything specific to show so here are code snippets (also forgive me for the poor writing of this Juneau but I am sick and exhausted)
![image.jpeg](https://cdn.hackclub.com/01a0826d-9d04-7731-bba7-c9994f368900/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/01a0826d-c4d3-7400-bf3d-ab892b03b200/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/01a0826d-fe58-776a-90f9-41f367771a39/image.jpeg)

Gotta love errors like this 
![image.jpeg](https://cdn.hackclub.com/01a0826e-5f50-7f7d-a225-e3a084139576/image.jpeg)

# 2026-09-07: Steering wheel pt2

**Total time spent: 1 hour 17 minutes**

So as I said yesterday I worked a bit more on the stability of the steering. I achieved it by adjusting the angle so when the mpu is rotated 80 degrees (basically its maximum) it maps as the maximum of a steering wheel (180 degrees) and what made the biggest difference was that now I check before sending the data if it rotates more that a specific threshold so when your hand just shakes a little it won’t move so you can actually hold it still in an angle without it jittering lastly instead of having a delay(14) which blocked the loop I made it use millis with a denounce flag so it also doesn’t overwhelm the core (14 ms should be around 60khz?? I think I might have done the math way to incorrectly) which is enough for this. Now on the visuals I added a steering wheel (kinda looks like it might put something prettier) it actually shows the rotation of what’s send on the pc and not the actual rotation of the device I wanted to add a text label with the degrees actually shown same for acceleration and braking (alongside a slider for them) but will do that another time. I had to add a new method in sprite manager that lets you draw a sprite but rotated. During this I realised that I need to do some redesign on how everything is drawn I should switch to a 2 phase system when you create a canvas you draw every you want on it and then do like showCanva(…); so it pushes everything at once this was actually the fix for the jittering I show at the steering wheel visual (actually might be that I made the bmp not transparent so I didn’t need to draw a rectangle above it every time)
![image.jpeg](https://cdn.hackclub.com/01a07d74-b910-7cbc-ac79-b4d73c6d4034/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/01a07d74-dfdc-7c5a-8205-a09057627e26/image.jpeg)

# 2026-09-06: Steering wheel pt1

**Total time spent: 1 hour 35 minutes**

So I had no idea on what I should do today so figured I would make the console act as a steering wheel. So I used the mpu6050 which is already set up and has the handler which makes easy to read the angles. I made it so you can hold it in the air and it steers based on the rotation. I simply used the esp32 ble gamepad library (same as used in the gamepad mode) which has all the features needed. However I have some issues for starters the mpu6050 is pretty inconsistent and fails to reliably return the correct angle but I will try doing some tweaking in the library setup and see if it fixes any thing maybe add some kind of filter idk I will figure it out. Also I don’t know what to use for the acceleration and braking I was planning on using the rear buttons but then it would be too flat while the real thing needs some kind of analog sensor so it feels more like a pedal. So I thought I could use the joystick up for acceleration and down for braking but idk if it will be good and then I also consider using the pitch of the mpu pull to your self for braking and rotate outwards for acceleration but it could also be messy and inconsistent and hard to get used to it. (Will probably go with the joysticks or fake the buttons longer you hold it more it accelerates)
![image.jpeg](https://cdn.hackclub.com/01a07871-e02b-78ad-af9e-5a00c4eb8621/image.jpeg)
(Middle screen I need to find a better font size )
![image.jpeg](https://cdn.hackclub.com/01a07872-6588-72d0-9a4d-3c82b6e293be/image.jpeg)

(Steering on action)
![image.jpeg](https://cdn.hackclub.com/01a07872-e60c-7a1c-ac1f-2f364bcde72c/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/01a07873-2f73-79e9-884c-238e8e63ca5f/image.jpeg)

# 2026-09-05: 3d fixes (switch holder and tft holder)

**Total time spent: 17 minutes**

Did some fixes on the 3d model for starters i fixed the switch holder because the wall around the screw hole was so thin which wasnt even printed so i added some more material there also added some chambering so it deosnt block the button (weird angle image but you get it) 
![2026-09-05_232543.png](https://cdn.hackclub.com/01a0734b-7b26-7cdc-a747-0ea6c6701f87/2026-09-05_232543.png) ![2026-09-05_232557.png](https://cdn.hackclub.com/01a0734b-8b3a-7963-b784-fba3460737ed/2026-09-05_232557.png) then i added something like a washer ? because the m3 screws i have are too long and the display moves up and donw ![2026-09-05_231618.png](https://cdn.hackclub.com/01a0734c-1f14-7057-a75f-13c76c830529/2026-09-05_231618.png) it going to go like this ![2026-09-05_231729.png](https://cdn.hackclub.com/01a0734c-4147-713d-862a-2628073b58a4/2026-09-05_231729.png) i also made the sd card slot a bit smaller and lastly i went around the bottom shell and added chambers so it makes the stand offs stronger ![2026-09-05_233120.png](https://cdn.hackclub.com/01a0734d-1425-7f14-abfa-3e6f36d5e8d2/2026-09-05_233120.png)
i couldnt do more for today because i am sick and also waiting for the joysticks to get right measurements.

# 2026-09-05: Github bom add

**Total time spent: 15 minutes**

so i wanted to add the BOM to the github repo i thought it was supposed to be in .csv format but then i see in docs that i should i have it as a table in the read me so all the time figuring out how to turn it inot a .csv went to waste. luckily i found a tool which you copy the table and makes it github format
![2026-09-05_231139.png](https://cdn.hackclub.com/01a07347-8180-78e0-b98e-b91962df04a7/2026-09-05_231139.png) now its good looking i will complete the rest of the repo when the project is finished so i have pictures of it and complete models, code and instructions

# 2026-09-04: Switch holder fix and gamepad button mapping

**Total time spent: 1 hour 40 minutes**

For starters I fixed some wires that were cut like the sd sck ![image.jpeg](https://cdn.hackclub.com/01a06e19-5abc-7dbc-8ea1-8a20b3fe98e6/image.jpeg) I also made the switch actually work until now it was left unconnected so when I was charging it the console was left on I used 2 wires because they were too short and I don’t like the other cables I have ![image.jpeg](https://cdn.hackclub.com/01a06e1a-9968-7755-8b10-ea9738d1a854/image.jpeg)![image.jpeg](https://cdn.hackclub.com/01a06e1a-b3b2-7d94-9d30-b3886c980914/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/01a06e1a-eb9f-77a4-9e3d-a7dcb587f889/image.jpeg) I then finally fixed the button mapping using a little trick with a gamepad tester and its history forgot to send the ss over to my phone so will update later. Lastly I worked on the 3d model more specifically the power switch holder previously it was something like that 

# 2026-09-03: GAMEPAD FIXEDDDD

**Total time spent: 1 hour 1 minute**

Omg this took way too long for such a simple fix. I genuinely had no idea what was going on so I decided to update the library and boards and hope it fixes the issue to my surprise it made the whole thing an even bigger time waste because it lost all the board setting and I didn’t realise so I had to wait for it to reach the end of compiling and give the errors. It wouldn’t be a big problem but every new compile takes more than 10 minutes so I had to go through this 2-3 times just to fix the settings. However the updates did absolutely nothing so I went back to testing. I thought it was something like a limit with the attributes(as the ai told me spoiler: I should have known not to follow it as it always messes things up) after some time searching the web and the library I found…NOTHING. So I switched method and I wanted to try if something else in the sketch blocks it (I had similar problems when first setting it up but I thought it was past this) so I started disabling features one by one and turns out that the audio is the problem and they couldn’t work at the same time for some reason I was so mad because the fix was really just 1 line of code (deinit audio that I had setup for the nes emulator) and now it works just fine only thing left is to fix the button mapping but I might leave it for later and configure them when the joysticks arrive so I don’t go back and forth.![image.png](https://cdn.hackclub.com/01a0690c-9780-7672-a201-d2257811773b/image.png) yeah even some random
Crashes idk the whole thing was a rage bait today ![image.png](https://cdn.hackclub.com/01a0690d-2d86-751a-9a91-2d93b26e7d3f/image.png) even thought it might be the set button (wasn’t an issue) because someone said they had problems with it ![image.png](https://cdn.hackclub.com/01a0690d-fefb-7f36-97b0-66682c9fdc4f/image.png) finally worked 🤯![image.png](https://cdn.hackclub.com/01a0690e-480f-7bd0-b0d1-50eff51828f4/image.png)

# 2026-09-02: Gamepad mode not working ??

**Total time spent: 1 hour 6 minutes**

so i decided to fix some wrong mapping that the gamepad mode had so i first had to coonect it and see whats wrong but to my suprise i couldnt even find it turns out the gamepad mode stopped working since i had cahged nothing i thought it would be the physical antenna that i had removed previously i tried reconnecting it without unscrewing anything which lead to disconnected cables so i had to resolder them. After i soldered everything i tried with the multimeter as always and showed coniniuty from gnd to 5+ volts which is a big no so i searched around couldnt find anything cleaned the whole thing with a brush and isopropyl alcohol and then the short was gone. Back to the problem the antenna didnt fix anything i tried changing things on code but i found it unreasonable it stopped working because it worked like 3 days ago and i havent change anything related to it but i am getting hit with this error ![image.png](https://cdn.hackclub.com/01a063e8-7c36-798b-a33d-166e2635bc6b/image.png) i cant fix it but i will keep trying untill it works flawlessly.

# 2026-09-01: Skematik and github update

**Total time spent: 1 hour**

So i didnt really have will to do coding today so i did some little things that are neccessery for the project too. Firstly a small fix i made the speaker protector have smallers holes so less stuff can stick to the magnet but i might have to but some kind of net to fully protect it because i dont want to block the sound. 
![image.png](https://cdn.hackclub.com/01a05e88-39c4-70ba-9902-cf2c2eae81ab/image.png)
After i started working on the skematik which is pretty outdated so i added the k pin on the powerbank module and also added a second bat cell
![2026-09-01_223110.png](https://cdn.hackclub.com/01a05e89-93c8-74c3-ab88-cc3b11b6bbc5/2026-09-01_223110.png) i also added the motor driver with the vibrating motors which were missing ![2026-09-01_223059.png](https://cdn.hackclub.com/01a05e89-f573-7152-b6ac-0c30dafa62a0/2026-09-01_223059.png)
and lastly (on the skematic) i added all the buttons which were missing (back, volume, select/start, and the one tied to k pin on the power bank)
![2026-09-01_223120.png](https://cdn.hackclub.com/01a05e8b-0890-71cc-9eab-ed20a7b13f8a/2026-09-01_223120.png).Finally i removed some features that wont be included in this version from the git hub read me and added a section for important notes and instruction and planning on adding more
![2026-09-01_225004.png](https://cdn.hackclub.com/01a05e8c-4e1e-7ed8-9202-325dfaf04360/2026-09-01_225004.png)

Removed:
![image.png](https://cdn.hackclub.com/01a05e8c-a3a5-790e-a6fe-1b967e7c7d6b/image.png)

# 2026-08-31: Game select screen implementation (idk if it called that)

**Total time spent: 2.5 hours**

So I actually made the game select screen from yesterday to work on the console it was a bit of challenge with the sliding bar on the side (it was always out of bounds) but with some head banging on the wall and math I figured it out and works fairly good. Also had issues with the little icons which I wanted to be in a grid but like filling each spot then moving to the next without a lot of if statements for it I created a json file(meta.json) which is inside the game folder which includes the creator the description tittle but also tags (I made the tags be the same text as the images so I don’t need mapping) ![image.jpeg](https://cdn.hackclub.com/01a05974-2564-71d5-a991-624c15b9edfc/image.jpeg) so far I have tags for single and multiplayer and mpu6050 ready but I will add more probably. Here is the final look ![image.jpeg](https://cdn.hackclub.com/01a05974-e25c-78a4-a3c3-981f21d2a9af/image.jpeg) the little ghost is a failsafe image when the game has no icon.bmp (only look at the last since only added the meta json to it ) and here is it in pixlr editor (removed the around the image frame)
![image.jpeg](https://cdn.hackclub.com/01a05976-1e0f-7cda-b129-6141e7364a11/image.jpeg)

Idk why this took me so long or if it’s logical but I had so long since I last coded and I have forgotten basic commands 

# 2026-08-30: Game select redeisng

**Total time spent: 1.5 hours**

This feels so stupid to write but i really spend an hour and half on designing this game select screen on pixlr editor and i am not even sure if i like it or not ![image.png](https://cdn.hackclub.com/01a0545d-18ad-76fb-94bc-ee834d0555ea/image.png) but at least i made those multiplayer-single player myself and they dont look that bad ![Multiplayer.png](https://cdn.hackclub.com/01a0545e-fb27-7feb-a252-8be93f0ce1b6/Multiplayer.png)
![SinglePlayer.png](https://cdn.hackclub.com/01a0545f-063e-75ef-bf98-3e24a1b7e205/SinglePlayer.png)
i almost went with a different deisgn like a grid but i figured out it ddint have enough space 
![image.png](https://cdn.hackclub.com/01a0545f-fb10-774b-9c2e-6c5734c6f0de/image.png)
i think i will keep the list design since it took me so much time and i make like a second screen when you press it which has details how to play etc before its launched with a nice background. I also fixed the playing now screen for the music so it now actually support longer song names but i had to sacrifice the album name however i might try to fit it somewhere an other time ![image.png](https://cdn.hackclub.com/01a05464-0c5e-7eb3-88a8-bcb0e242efd3/image.png) and also i decided that i dont like the sizing(either too big or small) of the fonts on tft espi custom fonts so i might have to add my own ones  ![IMG_8150.jpeg](https://cdn.hackclub.com/01a05465-21d9-734e-82a5-3cd52af16784/IMG_8150.jpeg)

# 2026-08-29: Now playing redesign 

**Total time spent: 1.5 hours**

So i finally got around to making a decent now playing screen for the music for comparison this is the old one which now that I see again isn’t bad ![image.jpeg](https://cdn.hackclub.com/01a04eda-3afb-72d5-a6cb-d7bf88a3bfe0/image.jpeg) but I had to have some better icons for pausing and skipping I tried to make my own but I didn’t like it ![image.jpeg](https://cdn.hackclub.com/01a04edb-05f4-7b48-9ce0-54897e925380/image.jpeg)
So I found some on flaticon which look great here is the inspiration pic ![image.jpeg](https://cdn.hackclub.com/01a04edb-e2f7-73d3-9ad2-5467f6272ddf/image.jpeg) I firstly made the design in pixlr editor to have the positioning right ![image.jpeg](https://cdn.hackclub.com/01a04edc-7dfb-7963-9d70-f3fbd7ff57b4/image.jpeg) and here it is in the console ![image.jpeg](https://cdn.hackclub.com/01a04edc-d358-7656-91f2-c16158a8f6a2/image.jpeg)
But this version has some problems the title and the artist (potentially the album too) gets half displayed if it just a bit longer so idk what I will do I might switch to a more hybrid version instead of having the text on side I put it in the middle and also I need to change and actually read the audio’s metatable for the album and artist 

# 2026-08-28: 3d design fixes , BOM , tidying

**Total time spent: 1 hour**

For starters i decided to finally use kinda reasonable names for the parts in onshape instead of part2 part5 etc (i know not the best naming but whaterver)
![image.png](https://cdn.hackclub.com/01a04a29-2543-7144-bb7c-d20bc0541901/image.png)
I fixed the mounting holes for the button board as i said yesterday 
![image.png](https://cdn.hackclub.com/01a04a29-e4b1-7d76-bb87-6db771cdce83/image.png)
And i addded some things on the BOM
![image.png](https://cdn.hackclub.com/01a04a2b-dcc8-793b-9793-b97222f625e0/image.png)
I almost forgot to mention that i had some trouble with the left vibrating motor and i thought i had wired something wrong and turns out i really did in the code i had them in gpio 17 and 18 
![image.png](https://cdn.hackclub.com/01a04a2d-b87e-7b3c-90e8-43366c634726/image.png)
but for some reason i had soldered them in gpio 16 and 17 and i just resoldered it instead of changing it in the code because i was too lazy to wait the code to upload (takes a longgggg time) and i already had my soldering iron on. after that both motor worked y but they need a tighter holding because you can hear them like colliding with the plastic.

# 2026-08-27: Battery

**Total time spent: 1 hour**

So the batteries finally arrived and looking pretty good ![image.jpeg](https://cdn.hackclub.com/01a044cf-bbb0-7f83-be2a-b5818eea2510/image.jpeg) 
It was a bit tricky soldering on them since I had to use a sandpaper first and then some flux so the solder sticks to the surface (2 of my fluxes didn’t work until I found like a really old one which for some reason worked better ) forgot to take a picture outside the shell 
![image.jpeg](https://cdn.hackclub.com/01a044d1-29c3-7403-9849-25b784182233/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/01a044d1-5962-72ba-b700-cf93aa4c3867/image.jpeg)
I also should mention that I wrapped some electrical tape around it just as an extra protection. Then I moved everything to the most recent print and fixed some wires that were cut from all the movements (more specifically the the negative speaker the sd cs and the left vibrating motor negative cable). 
![image.jpeg](https://cdn.hackclub.com/01a044d3-3d9a-7b30-aedb-5cd1efbe21d9/image.jpeg)
I have some problems tho firstly the button cables on the right are a bit too short now because of the battery bump also the battery was hard to fit with the cables attached since it made it longer (I should adjust the compartment) also for some reason the mounting holes for the buttons are now inverted? Idk how that happened which also adds up the short cable problem ![image.jpeg](https://cdn.hackclub.com/01a044d5-d507-7267-b55b-d9f06a1e484d/image.jpeg) lastly I ordered the joysticks (the thicker ones) finally and I have to say that I kinda hate the new import taxes which add 3€ to any item. 

# 2026-08-26: Back design (again)

**Total time spent: 1 hour**

After redesigning the console for the new batteries the whole back side designs were ruined so i had to remake them again. It was easier this time because i had them ready but of course i had classic problems with offset thingy and when even slithly moving anything ![2026-08-26_111145.png](https://cdn.hackclub.com/01a03d30-c4f0-71a6-82e4-a8c17d2ebedc/2026-08-26_111145.png) also i was trying to assemble everything one by one and then i remembered there is a better way to just import all of it and group it (SO MANY PARTS) ![2026-08-26_112339.png](https://cdn.hackclub.com/01a03d32-7c67-77be-902a-cc5abf260226/2026-08-26_112339.png) ![2026-08-26_111708.png](https://cdn.hackclub.com/01a03d31-ae2d-7570-ab40-64633e9da007/2026-08-26_111708.png) but i will probably make the ones on the battery cover be like fused together so multi color print because its thin. But the final version look really good in my opinion ![2026-08-26_112636.png](https://cdn.hackclub.com/01a03d32-e5cd-7234-95ca-445e4b575b71/2026-08-26_112636.png)
Bad news is that eu has new import taxes so every item i order from abroad gets taxed an additional 3 euros no matter the original cost so the joysticks end up costing 11 euros which is too much but i have no other option so i will order them and hoping they arrive soon.

# 2026-08-25: Bluetooth & joystick redesign

**Total time spent: 32 minutes**

A strong "need" got back to me and made me search to find a bluetooth module that can send audio to headphones i could use a second esp32 but its pretty big i found this but i am not sure it fits what i need i have to do a deeper search into it 
![image.png](https://cdn.hackclub.com/01a03a6b-58b0-78bd-80cd-9aa8a3b3fc72/image.png)

Also back to the joysticks i decided i will go with these
![image.png](https://cdn.hackclub.com/01a03a6b-efb7-7541-92bd-3dfdaa72b6e1/image.png)
but will also buy some cheap fis connectors and see if the joy con joysticks work.

after deciding i went on the 3d design and starterd makin adjustments firstly i made the battery cover 0.7mm instead of 1mm same with the top of the compantment saving 0.6mm also made the console 1mm thicker at made a little "bump" around the joystick so at total i bought myself 2.6 which should be enough i decided to make a diff part so i can print the rest of the console flat.
![image.png](https://cdn.hackclub.com/01a03a6f-58a4-77ba-9a02-1725232760c8/image.png)
(will make it purple)
![image.png](https://cdn.hackclub.com/01a03a70-d266-7b16-8cb6-7872e3743ab2/image.png)

# 2026-08-25: Battery holder & joystick search

**Total time spent: 33 minutes**

So i continued the search for the right joystick but now since i am on pc i can replicate the module and put it inside the 3d design and see if it fits so i tested this one ![image.png](https://cdn.hackclub.com/01a039a9-4a3e-7cc5-a197-ce8873e07cd7/image.png) and its a little bit thicker but its alr i will redesign some parts and it will be okay. however i dont think i can fit a button under it but i will try but it might be better to just use this ![image.png](https://cdn.hackclub.com/01a039aa-ea11-7ba4-81d0-65c3a52cde87/image.png) since its only 0.8 mm thicker but still has the button press. Then i swifted my search into battery holders despite what i said about soldering on the cells just because i want the project to be easier to replicate and more "Finished" but i strugled to find the demensions of all the holders and i think they are too chubby for the case especially now with the bigger joystick ![image.png](https://cdn.hackclub.com/01a039b0-2a27-7b3e-86d5-a61bb563c13d/image.png) ![image.png](https://cdn.hackclub.com/01a039b0-b724-7365-82b2-f2adf3d00f1b/image.png) i even got to a point on designing my own which aint bad but it hard if anyone wants to replicate the project ![image0_8_.jpeg](https://cdn.hackclub.com/01a039b5-1481-7c60-a6c8-be357a0849a9/image0_8_.jpeg) so i will stick with just soldering them if they ever arrive

# 2026-08-24: More joystick searching

**Total time spent: 0.5 hours**

So as I mentioned before several times I have had issues with the joysticks. Currently I own 2 joysticks similar to those ![image.png](https://cdn.hackclub.com/01a0356f-4e29-73d7-9230-6282f12da137/image.png)

However I can’t connect them/ solder wires on the fpc cable so I searched for connectors however I have already damaged one of them so I would have to buy a new one but I decided I don’t want to mess with fpc cables and I rather have pins where I can easily connect wires to. I found this alternative from adafruit but I can’t find any reasonable priced on stock ![image.png](https://cdn.hackclub.com/01a03571-1839-7a5a-ab7f-3f5f1db8f4d4/image.png). So I kept searching for a thin joystick I found those alternatives 
![image.png](https://cdn.hackclub.com/01a03572-039f-7d8c-8380-7242dfe6bee8/image.png)
![image.png](https://cdn.hackclub.com/01a03572-2958-7262-9004-83bc1c84b861/image.png)
![image.png](https://cdn.hackclub.com/01a03572-4ec6-76d6-818c-a1f408b0ecb8/image.png)
I like the first one but it’s a bit thicker than the 5mm space I have I could change the design but this module also has strange contacts which solder might not stick to and quite expensive compared to others. The second one seemed a bit bulky so I will probably go with the last one problem is they don’t have a push button on them so will have to probably add a button myself below the module if I need it that much. 

# 2026-08-24: BOM pt2

**Total time spent: 0.5 hours**

Continued designing the BOM but I have some problems like for the prototype boards the buttons the resistors I bought them in packages where most of them aren’t needed so idk what to put on the price and on the link am I supposed to put like the whole box or find the only ones I used 😬
![image.png](https://cdn.hackclub.com/01a03553-b4d2-71da-88ac-868998ddb328/image.png)
![image.png](https://cdn.hackclub.com/01a03553-df72-76fb-8823-5b48a12b1647/image.png)

# 2026-08-23: BOM pt1

**Total time spent: 20 minutes**

Started working on a BOM since it’s the only thing I can do from where I am at. First time making a BOM so idk if I am supposed to do it like that or not. I only managed to complete part of it since I don’t have much time. I included stuff like item name price description usage link and supplier and also quantity as I think those are the necessary. I will however check other projects on how they are supposed to look. 
![image.png](https://cdn.hackclub.com/01a02fc5-ffe6-7ea5-a33e-aaea8e29a802/image.png)
![image.png](https://cdn.hackclub.com/01a02fc6-242d-7dcd-901d-305af67fb043/image.png) 
I couldn’t lapse it since it didn’t let me to due to an error but it took me around 20 mins (it’s hard on the phone)
![image.png](https://cdn.hackclub.com/01a02fc6-c705-7461-bdfa-ebeac59a1a67/image.png)

# 2026-08-22: Joystick matters 

**Total time spent: 5 minutes**

So I said before I have some issues with connecting the joysticks and those remain. I thought of buying 2 connectors 0.5 mm pitch and 5 pin however idk if I can later solder it and attach it somewhere or not so I thought about breakout boards ehich cost more but will save me the trouble if they fit (they cost around 7€ for both) but I have an other issues in my attempts in soldering in the fpc cable I cut the stiff end of one of the joysticks and idk if the connector will hold or if I will need to buy a new joystick. So here are my searches but the thing is that i will have to wait like 2 weeks for them to arrive and it’s kinda annoying. 
![image.png](https://cdn.hackclub.com/01a02b0e-4c44-7272-b64a-b6e9dae5270c/image.png)
![image.png](https://cdn.hackclub.com/01a02b0e-84c4-79d3-ac1d-cfd7945ec7f6/image.png)

In conclusion I will probably order the breakout boards and might order an extra joystick just in case. 

# 2026-08-21: Battery order

**Total time spent: 3 minutes**

So I finally found the right battery with a fair amount of capacity and reasonable priced and I ordered them I bought 2 from the start so I won’t pay double shipping and either way I was probably going to order after. 
It’s the Samsung 18650 3400mah I don’t remember the exact model but you can see below. They should arrive to my house within the next 4 days. 
![image.png](https://cdn.hackclub.com/01a025ce-0cc5-76b7-9ff8-e3d867317d57/image.png)

# 2026-08-20: Test print 

**Total time spent: 2 minutes**

So I sent the file to the printer and started printing the first prototype of the second version. However I didn’t manage to test it but I saw it and it should be good(paused it and put the battery on top to see if it would fit). I have left the house for vacation so I will try and do some things from here small things to keep the daily posts. Tomorrow I will probably order the batteries and will see what I will do the rest of the days probably some planning, research or some ui ideas. 
![image.jpeg](https://cdn.hackclub.com/01a02066-fc50-7f99-aaed-09b02f6b7244/image.jpeg)

# 2026-08-19: Battery compartment redesign pt 1

**Total time spent: 3h 18m**

Turns out that the bigger cell needs much more space which i cant free up without making the console thicker which i dont want to do. So i will go with the clasic 18650 cell i saw some samsung ones that are around 3400 mah and if its not enough i will add a second one but it shouldnt be needed.
So i started redesinging the console for the different battery but i didnt think it would take this much time (i havent done really good job on the design so everything was falling apart with every change). Finally i completed it added support for 2 cells one in each side as i said yesterday. I had to burry the speakers into the shell and change how they hold in place (now it needs screws D: ). Now i have to put the back designs in the place again but diff spot. So i have potentially 4 things left (For this stage)
<br>1| How to connect the battery cells (spoiler: probably soldering on them) and 
<br>2| Fix the astheatics
<br>3| Test print it
<br>4| Buy the good cells (i only have some generic ones that are posibly only 2200mah)

![2026-08-19_182348.png](https://cdn.hackclub.com/01a01aac-8039-736c-8a76-ff11dfd8d485/2026-08-19_182348.png)
![2026-08-19_182355.png](https://cdn.hackclub.com/01a01aac-9096-7af0-bfc6-6f359dd4f80e/2026-08-19_182355.png)
![2026-08-19_182427.png](https://cdn.hackclub.com/01a01aac-a4ca-756f-a22a-c0821c4a1dbb/2026-08-19_182427.png)


# 2026-08-18: Battery searching 

**Total time spent: 10 minutes**

So I searched my options for batteries a bit more and I am closing on single li ion cells. However I am thinking if I should got with the 21700 size which offers around 5000mah but is bigger in size or the 18650 which is 3400 mah so 1600 mah less which is a fair amount. But the smaller size can easily fit in the case with small adjustments while the bigger needs more tweaking and some redesigning like “burring” the speakers into the shell which gives 2-2.5mm making the battery cover cap thinner like 1mm saving also 2mm and some other stuff which adds up to leaving just enough space for the battery to fit. But I also have the option to put 2 batteries one in each side which doubles the capacity reaching 10000mah for the big ones or 6800mah for the smaller ones but it might be an overkill. I think I am going to focus on one cell for now and see how it performs but I will probably include support for both batteries from the start. I now have to choose which size to go for and check if the description from the seller is valid and if yes I will probably go with the bigger since it’s around the same price. Another problem I am really considering is how I am going to connect them to the circuit since it’s not good to solder on them I don’t have spot welding machine I can’t find any with pre installed wires so I will need to either carefully solder on them or see if I can find a shop to spot weld them for me. 
The 2 options:
![image.png](https://cdn.hackclub.com/01a016a8-cd5f-756f-a267-173efae35759/image.png)
![image.png](https://cdn.hackclub.com/01a016a8-f465-72a7-8a17-8356cd897a64/image.png)
And where I could place them:
![image.jpeg](https://cdn.hackclub.com/01a016a9-50e5-7148-80bf-0c40fe905073/image.jpeg)

# 2026-08-17: Soldering final part (for now)

**Total time spent: 30 minutes**

Today I completed the soldering I did more research and it turns out the power bank module is just fine but I will have to put a button that it needs to start giving the 5volts. However I am not happy with the battery for a couple of reasons first it’s a high voltage one so it needs 4.35 volts to charge at maximum so I loose capacity secondly it’s really old so I don’t trust its true max capacity (12 years old) and lastly if someone want to replicate this project he won’t be able to since the battery isn’t available to buy. So I did some searching I found some good choices for batteries one that’s 2500 mah which is alright it fits well in the dimensions but not much capacity (it’s also reasonably priced) also found some other including one that’s close to perfect for my project around 3500 mah but the shipping is way too much for some reason (30€ and you must spend 15€ so I would need to spend 45€ for a battery) but then I thought about a single li ion cell battery which I think are more than 3000 mah and I could probably squeeze it below the joystick but I need to buy one with already connected wires or maybe just solder on it (but I haven’t done it before and I am guessing it’s not the best idea). 
![image.jpeg](https://cdn.hackclub.com/01a01177-8727-713c-9821-ade9ad716865/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/01a01177-c986-7c63-b181-ad60de6e2269/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/01a01177-ec93-7009-bce4-1c8f5fc0ac30/image.jpeg)
Note: I only lapsed half the soldering and nothing from the battery search (was longer that I was planning 😭) I have around 15 mins lapsed so I will just put an extra 15 mins😬

# 2026-08-16: Soldering almost final pt

**Total time spent: 3.5 hours**

Today was a really good day I managed to do almost all the soldering except the battery charger because I still don’t know which to use. I connected all the signal wires and power to tft screen and sd card and same with the mcp23017 and all the buttons (except the select start and the volume ones ). I had some issues with the mcp I confused the interupt pin with the reset so it wasn’t working but I fixed it. I still haven’t managed to solder the joysticks and idk if I will be able too I might buy connectors or switch to simple joysticks. I also did some test and seem to work fine but I have a problem with the speakers resistance and more stuff basically not enough power for both of them in parallel might be the cheap breadboard power supply I am using at the moment. 
![image.jpeg](https://cdn.hackclub.com/01a00c1a-8b12-78e5-8bc1-27ab37f1ed04/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/01a00c1a-b0bf-7628-a2ff-56b653e39a33/image.jpeg)

![image.jpeg](https://cdn.hackclub.com/01a00c1a-f206-786c-93fb-53e4020496d1/image.jpeg)

# 2026-08-15: Soldering pt3

**Total time spent: 1 hour**

I connected some signal cables to the esp32 such as the motor driver the mpu and the amplifier had no issues with that apart that it was a bit tricky because it was space tight. However after I soldered them I realised that they don’t fit and they collide with the tft screen sd card slot so I had to make them shorter I decided to cut the header pins and solder them as smd components saving around 2 mm it was tricky since I was trying to cut them without having to solder all the cables again so I cut them while being soldered on the perfboard. To no surprise I kinda damaged the silkscreen of the components pcb. Tomorrow I will finish connecting the mpu and resolver the power cables from below and try it like that might have to bump the console thickness 1-2mm.  
![image.jpeg](https://cdn.hackclub.com/01a00c1a-d5ed-7482-85aa-36d9c207aa58/image.jpeg)

# 2026-08-14: SOLDERINGGG PT2

**Total time spent: 2.5 hours**

For today I wasn’t sure on what to solder so I decided to just connect all the signal wires (only the one end) so they are ready to be soldered to the esp32. However I detected 2 problems firstly the power bank module that I was planning on using for charging the battery and providing power needs a button to start giving power which could be used as a switch but I haven’t designed it around this and idk if I like it like that but also it says that it charges the battery to 2.4 amps (I think it meant this) which is way more than what the battery can handle so I might switch to a simple boost charger module which should be pretty good for this but I won’t be able to charge anything with it (but I guess I wouldn’t do that either way). Second problem is the joysticks with the fpc cable which I can absolutely not solder on it I tried multiple times and failed (I even halved the length of it from all the tries) so I will need to either try and find connectors or change it to have the normal joysticks (but they are bigger and a bit ugly). Tomorrow I will either connect everything to the esp32 and test it or do some searching for the connectors(or change the design if I don’t find any) but I might not have time since I am planning a road trip 😬
![image.jpeg](https://cdn.hackclub.com/01a001fe-c48f-7e9c-b072-c54d8925084d/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/01a001fe-e79c-78b2-b4a3-d10009afdd9a/image.jpeg)

![image.jpeg](https://cdn.hackclub.com/01a001ff-1581-7570-b5b2-ea98102bbe4e/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/01a001ff-3d29-7f45-ba0b-305e1739e9b3/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/01a001ff-6d64-7878-8ac3-8a7ee6fab09c/image.jpeg)

# 2026-08-13: SOLDERINGGG PT1

**Total time spent: 2 hours**

Today I did some soldering for the buttons signal wires also connected the 2 speakers together since they share the same audio. Also I soldered the little battery contact thingy with the power bank module but in addition I soldered the components on the “main” perfboard the mpu the amplifier the diode the regulator and the motor driver which I connected the 2 vibration motors. 

![image.jpeg](https://cdn.hackclub.com/019ffc96-c280-7ed8-91e6-06ef85dfe0d1/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019ffc96-f136-79b2-b7d2-70ffe14edd00/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019ffc97-1401-7bd5-87c4-48c7003c08c9/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019ffc97-50f9-793e-a18b-7cf038212003/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019ffc97-775a-784f-baad-e1f6ac79ecaf/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019ffc97-a5f6-76b4-b276-53e6740be49a/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019ffc97-cd66-77e7-99da-1316835140d7/image.jpeg)

Note: I managed to lapse 1 hour of work but I did roughly 3 but due to my phone not having battery and not having somewhere to attach and record I couldn’t lapse all of it. (I am going to count 2 hours as something in the middle)



# 2026-08-12: some fixes 3d design

**Total time spent: 16 minutes**

after the second 3d printed prototype i located some flaws and fixed them. Firstly i was way of with the microphone screws (i used - insead of + in the calculations) and made the weird looking mount a bit smalled in diameter. Lastly i fixed the position the buttons for the esp32 (reset and boot) and added a hole for the error rgb light. 
![image.png](https://cdn.hackclub.com/019ff761-f786-73d1-9d6a-96687a4e3dfa/image.png)
![image.png](https://cdn.hackclub.com/019ff762-1f60-7578-b2ef-621d5b73bd9d/image.png)
![image.png](https://cdn.hackclub.com/019ff766-9462-7843-9e03-0ff4e2da279c/image.png)

Tomorow is lock in time i am going to move in soldering most of the stuff like adding individual cables for the buttons and other stuff i am not sure i will solder each component together so i can test it in the breadboard still but we will see.

# 2026-08-11: 2nd prototype print

**Total time spent: 10 minutes**

Today I inspected one last time and send a second prototype to be printed so i can test it. Also did some tweaking on the firmware some and tested the gamepad again it works fine but i need to fix the buttons. 
![upload failed]()
![image.jpeg](https://cdn.hackclub.com/019ff282-a5a8-79ae-a4d0-7d1c9da1784f/image.jpeg)

# 2026-08-10: General 3d design fixes

**Total time spent: 2 hours**

I fixed some small but kinda important stuff around the 3d design like making the screen mounting holes smaller so the srew can grip better made the nail holes bigger so the nail goes in easier. Also added some chambers around the mounting thingys so they are stronger and wont snap off. I added mounting stuff for an i2s microphone but i am not sure i will install one but wont hurt having support for it. Made some changes in the battery area like fixing the cover so the little teeth go under the shell and made the comparntmenmt a bit longer and smaller on the sides. Moved the powerbank module mounting hole closer to the outside and added clearance for its pcb. I also made some other minor readjustments that i cant remember. But i am not sure what my next move will be should i print it again with a testing cheap material or with the normal petg cf ? 

![image.png](https://cdn.hackclub.com/019fed4e-2119-7182-a73a-886c792bff29/image.png)
![image.png](https://cdn.hackclub.com/019fed4e-6afb-7736-bdb4-7f37bbcdf77c/image.png)
![image.png](https://cdn.hackclub.com/019fed4e-cb4b-7b00-a409-7dfce5ef06d8/image.png)
![image.png](https://cdn.hackclub.com/019fed4f-497a-7c21-868e-b128c33bc054/image.png)

# 2026-08-09: Protoboard cutting

**Total time spent: 1 hour**

The title explains it all but I will explain more. I designed the console mounting holes and everything to just be easier to fit and not actually match it with the positioning of the boards so I had to drill new holes cut the protoboards to the correct sizing so they fit well. I can say that the drilling part wasn’t difficult but getting the positions correct was a nightmare which I kinda failed in some but it’s alright because I can micro adjust the design for the final print. The hardest part was cutting them I started with my cutting clippers (I think it’s called that) but it wasn’t really easy so I switched to the dremel I used previously for the drilling. Everything was going smoothly but the dremel soon started acting up loosing its strength and barely spinning (I really have no idea why it did this since I gave it big breaks to not over heat and didn’t use it continuously) so I finished it with the clippers. 
![image.jpeg](https://cdn.hackclub.com/019fe839-1589-794d-acc1-831437f8feb1/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019fe839-468d-764b-8b45-2c23e021324c/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019fe839-6914-72ba-98ff-daed13cdd4a6/image.jpeg)

Tomorrow’s plan is to examine the 3d printed parts again writing down all the flaws and then fixing them for potentially the final version. 

# 2026-08-08: First prototype print 

**Total time spent: 1.5 hours**

I AM BACK FROM VACATIONNNNNNNN that means I am going to fully lock in since I have nothing else to do (that I prefer)
Today I added some screw holes that gonna hold the bottom and top shell together (forgot to mention that I will make them 2 parts and not 6) took me some time because I kept changing them. But most importantly I 3d printed the first prototype and inspected it closely and found weak spots and positioning misscalculations which should all be fairly simple to fix they are a lot and I don’t remember each one but for example the usb type c ports for the esp32 needed to be lower so it actually fits the battery compartment a little smaller and some mounting holes a bit thicker and chamber so they are stronger (since it’s printed in the layer lines it really weak). 

![image.jpeg](https://cdn.hackclub.com/019fe2fa-28a1-777c-97ab-34d60eb1f78c/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019fe2fa-4d96-722e-b496-6b52c1c57dcc/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019fe2fa-678a-786e-9abc-c023b39bda52/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019fe2fa-8c78-7e13-81d1-e94b6f8b9bbd/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019fe2fa-b293-7164-abea-c4617200d57f/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019fe2fa-d200-7100-b6c4-f6e6d3e39fc0/image.jpeg)

# 2026-08-06: Power rail pt2

**Total time spent: 3 minutes**

I will also need some diodes for the esp32 so it doesn’t backfire voltage into the battery when you connect to type c for code upload. I found those which should be good should drop the voltage less than others and should support the amps
![image.png](https://cdn.hackclub.com/019fd8db-9ccf-7aaf-b247-84b7b4f99e92/image.png)

# 2026-08-04: Power rail

**Total time spent: 2 minutes**

I am designing the power rail I decided I will use the power bank module that I have that auto step up to 5volts and add a capacitor 1000mf and 3.3 v regulator for all the 3v3 logic components 
![image.png](https://cdn.hackclub.com/019fce73-fecf-753d-a534-8993389ea988/image.png)


# 2026-08-02: Stickerss 

**Total time spent: 5 minutes**

Found some hack club stickers that I had lost and I will definitely add them on the back and I will also design some forge and valinor stuff around the console. I also realised that I need to lock in because the program is ending in a week and I still have some designing and 3d printing but also assembly/soldering and some software stuff that I might not have the time to complete. 
But I will need some more ideas for the design. 
![image.jpeg](https://cdn.hackclub.com/019f9ac7-d38b-7527-8d6a-ce7b034d5730/image.jpeg)

# 2026-08-01: Design dielema

**Total time spent: 1 minute**

I can’t decide if I should print the whole thing in 2 parts bottom and top and just connect it with some screws or 6 parts left right centre top and bottom and then attach them together but idk if it will be stable and sturdy. 
Also I kind of in vacation rn so I will be slow 

Update: it going to be 2 pieces one too one bottom this way it’s easier to attach it together and be sturdy. 

![image.jpeg](https://cdn.hackclub.com/019fbefe-5c32-75fc-90c5-fe25fa5c17a8/image.jpeg)

# 2026-07-31: Front design (star & heart)

**Total time spent: 1 hour 20 minutes**

Added the forge logo with the letters on the back my only concern is that the purple infill may be to narrow to print but i tried it and it came out okay with pla i think petg will be fine as well.

Also found this star sticker on the hack club website so i added it to one side but then something was missing from the other side so i made my own little heart replica that goes really nice with the design. i think i wont put anything else except if i find something nice and i will fill the gaps on the back with the stickers i have.
![image.png](https://cdn.hackclub.com/019fb9a7-2992-794e-93b8-96a48070b780/image.png)
![image.png](https://cdn.hackclub.com/019fb9a7-6ca4-7923-8b64-f2f3b1545943/image.png)
![image.png](https://cdn.hackclub.com/019fb9a7-a055-7c75-bffa-eeb01bb884c0/image.png)
![image.png](https://cdn.hackclub.com/019fb9a7-c7eb-775b-bde1-ec0d4fc249ae/image.png)
![image.png](https://cdn.hackclub.com/019fb9a7-ef05-7939-a52d-16309a5b59b3/image.png)
![image.png](https://cdn.hackclub.com/019fb9a8-2904-73c0-af0b-d6ed76f8caf4/image.png)

# 2026-07-29: Hack club flagggg design 

**Total time spent: 30 minutes**

Found this little sticker on the google so I decided to add it to the back it look really nice so I am keeping it and I will find more to add. 

![image.jpeg](https://cdn.hackclub.com/019faf8e-d413-7e98-ac2b-22ac8f9eb141/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019faf8f-047c-7ef2-bb6b-eba506066b0e/image.jpeg)

# 2026-07-28: Fixes & nicer design 

**Total time spent: 28 minutes**

Fixed a diameter of hole on the limit switch mount made the little stopper for the back button a bit thicker so it is stronger and I added the GitHub logo with my user on n the back button now that I am thinking it I should search like how legal it is but I don’t think there should be a problem. 
I swear I did something else too but I can’t recall. 
![image.jpeg](https://cdn.hackclub.com/019faa35-1609-7f6d-95a7-b6270dbe7adc/image.jpeg)

# 2026-07-27: More astheatic design ?

**Total time spent: 1 hour**

Idk if i will keep this it looks kinda weird but i need some more purple.
![image.png](https://cdn.hackclub.com/019fa53a-b66e-7114-bed6-ac1467f47c69/image.png)
FORGED BY JOJO RAHHHH 🔥🔥🔥🔥
![image.png](https://cdn.hackclub.com/019fa53b-6908-7354-960f-13d06829258f/image.png)
I am thinking of adding maybe the github logo and my user and probably more forge stuff.

Lil volume indicator
![image.png](https://cdn.hackclub.com/019fa53c-cba5-75ee-a0ae-326e5a186b19/image.png)

I also redesigned the power switch because i couldnt get the purple switch to go in and function properly so i moved the switch holder to the side instead of the centre so now it should have more space
![image.png](https://cdn.hackclub.com/019fa53e-7b7f-72a6-bd6e-a7546b361b2e/image.png)
I dont remember if i did anything else today but whatever

# 2026-07-26: Simple design adds ( idk what title to put)

**Total time spent: 2 hours**

changed the colors to vizualize better the final result added the valinor icon in the back but i want to add more stuff more purple touches but i am not sure what. Also i am still at a dyleam if i should just 3d print the multicolor using the ams or just print them seperatly and glue them beacause the petg (black) is cf and i dont know if it will stick together well and also i dont have much and i dont want to waste it. Started working on a better switch instead of being the plain black switchy thing. Added "Start" and "Select" to the buttons and i decided i will actually make the buttons purple.

![2026-07-26_233637.png](https://cdn.hackclub.com/019fa025-4e3f-7f94-9cf4-ca83f99b44dc/2026-07-26_233637.png)
![2026-07-26_233628.png](https://cdn.hackclub.com/019fa025-6943-7a30-99c9-66cc05428977/2026-07-26_233628.png)
![2026-07-26_233610.png](https://cdn.hackclub.com/019fa025-75b9-79fd-9cc1-2e791e588f64/2026-07-26_233610.png)
![2026-07-26_233550.png](https://cdn.hackclub.com/019fa025-8334-72c3-8963-e93e57acdd6c/2026-07-26_233550.png)

# 2026-07-24: USB labeling& cutouts  and ventilation

**Total time spent: 55 minutes**

Today i added the usbs for the esp32 s3 i went with a different design than the power i mean that it has like a cutout (idk how to explain it) thats 2 mm while the power has all the way to the pther side (explanation: the usb will be burried a bit and the shell has a thickness of 3mm so the cable wouldnt be able to reach and connect that why i need to make a bigger hole so the whole plastick thingy goes in the shell. I added some icons idicating waht each port is and some ventilation for the esp32 brain which i dont know if it is needed and if it actually gets hot but it wont hurt if it exists

![image.png](https://cdn.hackclub.com/019f958a-6c2d-702a-8c8b-ea9926d33877/image.png)
![image.png](https://cdn.hackclub.com/019f958a-ab0a-791f-80d2-2d7a6df12cea/image.png)
![image.png](https://cdn.hackclub.com/019f958a-dc0d-78d2-bb98-c46cb8851356/image.png)

# 2026-07-23: Buttons design

**Total time spent: 32 minutes**

Nothing crazy today I just bade the buttons for the other side I chose to do arrows I also added some small little thingies so the buttons worn rotate around. And made some mount holes for the esp32 perfboard a little further apart so the the esp32 will actually fit. 
![image.png](https://cdn.hackclub.com/019f9061-8774-7f71-a216-6b427c69c650/image.png)

# 2026-07-22: Other electronic compontents mounts

**Total time spent: 2.5 hours**

i figured out whats the best place to put all the electronic compontents. The plan is easy i will use a s big perfboard for the esp32 s3 so i have easy acces to each pin and then the amplifier, mpu6050, mcp23017, the motor driver, the diodes, the voltage regulator will go to a different perfboard that will be between the battery and the tft screen i will have to cut the pins a bit to fit better but no worries.the powerbank module goes to the right side which is closer to the battery and i will probably add a 1000mf capacitor. I imported and created (the ones i couldnt find) components to the assemlby so i have a more complete view of the space and everything. Lastly i made the buttons actually unique like A B X Y but i dont know waht to do with the other side might go for arrows. so i will have to do something so the actual parts hold together with eachother and then i will probably focus on the asthetics and final touches.

![image.png](https://cdn.hackclub.com/019f8b95-ec23-711b-8929-958415fba110/image.png)
![image.png](https://cdn.hackclub.com/019f8b96-2bd4-78ff-a007-c05b596a2555/image.png)
![image.png](https://cdn.hackclub.com/019f8b96-d9c6-7485-a035-91a4480c080d/image.png)
![image.png](https://cdn.hackclub.com/019f8b97-0b10-720c-8b7c-021fa8b2ebe0/image.png)
![image.png](https://cdn.hackclub.com/019f8b97-731e-70bd-a21f-04ce1518a918/image.png)

# 2026-07-21: Minor 3d design tolerances fix

**Total time spent: 1 minute**

Today I didn’t have much free time because of lessons so I just fixed some tolerances that were either too big or too tight since I had forgotten to fix them. Forgot to lapse it but it was like 10 minutes so that’s alright. 
![image.jpeg](https://cdn.hackclub.com/019f863a-5325-7134-9a2f-f76721801dc8/image.jpeg)

# 2026-07-20: battery design mount 

**Total time spent: 46 minutes**

So for the battery i closed on the old phone battery its a 2100 mah 3.8 v battery so at 3.7 i estimate about 1800mah. I added the hold for the battery and the little battery contact thingy and designed a cover that attactches with 2 screws to easily take out the battery. Now i have to figure out where to put the esp32 s3 since it take some space and it needs to be vertical so i can acces the usb to programm it.

![image.png](https://cdn.hackclub.com/019f8141-503f-71a7-8c12-6ea48601ad29/image.png)
![image.png](https://cdn.hackclub.com/019f8141-9e6e-7085-8fa0-e1fadd31fb50/image.png)
![image.png](https://cdn.hackclub.com/019f8141-e130-72b1-a192-c17ee1ca5d00/image.png)

# 2026-07-19: Even more 3d mount deisngs (tft & fixes)

**Total time spent: 1 Hour 7 minutes**

Added:

->Mount holes for the tft screen might be a little weird since the screws i have are a bit too long and the screen might be like burried(could be good to protect from falls though)

->Mounting holes for the start/select button perfboard

->Cleared holes for the usb and type c charging that i didnt do yesterday

Fixed:

->Some position misscalculations like the button mounts and a clearance hole for a screw head

->The rear button rotation holder, i bade it a bit thicker so it can hold on better and added a hole in the middle so i can add a nail for stronger support since i might have to print it face flat so it will be along with the layer lines therfore weak (like all the mounting stuff)

![image.png](https://cdn.hackclub.com/019f7c0f-8338-7a17-82b9-4057e636925c/image.png)
![image.png](https://cdn.hackclub.com/019f7c10-18dc-7b0c-82d5-8757f4b3ca28/image.png)
![image.png](https://cdn.hackclub.com/019f7c10-3f38-7a58-bd9c-231ecce49617/image.png)

# 2026-07-18: More 3d design mounts 

**Total time spent: 17 minutes**

I added some mounts for the joysticks like realllyyyy simple might be one of the worst designs I have made because it’s like I didn’t even try but I think that’s the best way it will get mounted to accept the force from the thumb. Also added some screw holes for the power bank module by I also need to cut out the shell for the usb and type c. 
![image.png](https://cdn.hackclub.com/019f768d-aa20-74a4-a210-353839d1bec8/image.png)
![image.png](https://cdn.hackclub.com/019f768d-dc4e-778f-9a21-1c8306798d46/image.png)

# 2026-07-17: Mounting stuff 3d design

**Total time spent: 1.5 hours**

to keep it short i added a mount for the vibration motors simple like slide in just to hold it and use the double sided tape at the back so it doesnt slide back out same with the speaker on the font of the console but i might switch it to the back bacause it looks a bit ugly with the hole but i dont want the hand to block it or the sound being more "indirect". Lasty i added some mounting pillars with holes for the button-perfbaord thingy and some supports in the centre, i thought of like mounting it on the top shell but it could be weak since some force is applied downwards and also it would be harder to asseble.

![image.png](https://cdn.hackclub.com/019f718e-725c-7f30-9146-8837b468324a/image.png)
![image.png](https://cdn.hackclub.com/019f718f-1e00-7477-b9df-b253f8af05f9/image.png)
![image.png](https://cdn.hackclub.com/019f718f-6486-761e-928d-d6f5eb305986/image.png)
![image.png](https://cdn.hackclub.com/019f718f-8e00-7e8a-86a8-cf7d6ce9d3d4/image.png)
![image.png](https://cdn.hackclub.com/019f7190-0a8a-7232-b0c1-6db09f963781/image.png)

# 2026-07-16: Backbutton spring design

**Total time spent: 45 minutes**

I decided to add a little spring to retrieve the back button to the original position. It took me a while since it’s my first time designing springs. I am not sure if I need to change the design of the button to be like a slider instead of rotating. 
![image.jpeg](https://cdn.hackclub.com/019f6c5f-f1f4-714c-b9d6-abc50566ca6f/image.jpeg)

# 2026-07-15: 3d back button design 

**Total time spent: 1 hour**

I remembered that I had to do some 3d designing as well for this project and so I started designing the back button. Nothing crazy I will use a limit switch and I hope it doesn’t like get stuck and has enough force to go back to unpressed also I hope you don’t accidentally press it while holding it. Pretty rough design so I can improve later. 
![image.png](https://cdn.hackclub.com/019f6788-6e4b-79c4-af54-6b335e309f3b/image.png)
![image.png](https://cdn.hackclub.com/019f6788-b61d-7a2a-9d17-f09caed6489a/image.png)

# 2026-07-14: Wiring thinking 

**Total time spent: 12 minutes**

I have a dilemma I can’t decide if I want to use perfboard for the wiring like a big central board with the esp the mcp the amplified the mpu and the tft or I should like just mount everything in the case and connect wires to all the components. I am sure I will use for the buttons and the mcp chip probably for the esp32 too. 
![image.jpeg](https://cdn.hackclub.com/019f623f-2209-7efd-9da4-37c3a99b625e/image.jpeg)

# 2026-07-13: Gamepad kinda working

**Total time spent: 2.5 hours**

Making the console a ble gamepad was supposed to be like an easy implementation. Turns out it’s not always there is something going on conflicting with the ble gamepad I figured it’s the i2s audio so I will need to somehow bypass that probably deinit the audio when on ble mode. I temporarily disabled it and I got it to work I used and online gamepad tester the button mapping is way off but it is a simple fix. At the start the joystick wasn’t shown on the tester but it was because I had disabled the z axis I think. After I enabled it showed but I don’t know if it’s now the correct one but I will test with playing a game. So for tomorrow I will probably fix the button mapping since I won’t have much time. 
![image.jpeg](https://cdn.hackclub.com/019f5d2a-1191-7d21-ad35-eee0994d58bc/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019f5d2a-4d04-7eff-ae53-0b10614463f3/image.jpeg)

# 2026-07-12: Gamepad

**Total time spent: 2 hours**

I finally made the tab but I had only problems which I still haven’t fixed. The ble gamepad isn’t shown for some reason. The strangest part is that if I try to initialise the ble gamepad at the setup it works and shows on the Bluetooth discovery. I really don’t know why this happens but it might like fight with something else I will try and figure out what that is. 

[on setup]
![image.jpeg](https://cdn.hackclub.com/019f57d6-6679-7a74-8a7c-9faaaaa47f24/image.jpeg)

# 2026-07-11: Controller mode

**Total time spent: 20 minutes**

So I started working on a new feature which basically turn the console into a controller that can connect to the pc via Bluetooth I tried searching for it to be able to connect to Xbox and ps but it says it’s not possible. So far I managed to kind of construct the new tab but didn’t actually get it to work because I had no time to fix some bugs and re upload it. I found a ble library which is called esp32 ble gamepad which I think fits to what I need. 
![image.jpeg](https://cdn.hackclub.com/019f5293-16b5-7696-91a6-3a68f3ba4499/image.jpeg)

# 2026-07-10: Pc launch game

**Total time spent: 10 minutes**

So I am trying to get a function working but I yet have to figure out how I will achieve it. I am trying to like have a list with the available games on the pc and the esp32 shows the menu and you can choose one and run it. This way you choose a game and it launches on the pc then it captures only this window and all controls are send there. But I need to make some big changes since now I connect to the WiFi only when it starts streaming but to give the list to the esp32 it needs to be connected to the pc. I really want that feature but it’s kinda too “complicated” (needs lot of adjustments) so I might skip it for now. I have started working on it but really not well it just doesn’t work it shows the whole screen or nothing no list. 
![image.jpeg](https://cdn.hackclub.com/019f4d7e-ff37-74bd-8a48-5e9bb7fa5644/image.jpeg)

# 2026-07-09: Pc streaming fixes

**Total time spent: 1.25 hours**

So I did some fixes on the pc screen mirror like adding the cursor which was not shown at all. I initially thought it was just too small and that why I couldn’t see it but turns out the mss libra try I use in python ignores the cursor when screenshotting so I fixed it by drawing a red cursor at the corresponding position which should be costumazample for future. I also fixed the joystick cursor control I had made a mistake the python expected info about the joystick every time while the sketch only sent when it changed so I changed the python to move till next update. 

I played some Roblox too
![image.jpeg](https://cdn.hackclub.com/019f48a1-0d9f-769e-8fcf-facf30185ae8/image.jpeg)

# 2026-07-07: Ui redesign ideas

**Total time spent: 4 minutes**

Thought of some ways I can change the ui of the console so it looks more finished and nice. However I won’t be making the changes for now since I wanna firstly complete the whole software functionality and hardware. For example here is a quick sketch of how I am thinking on changing the games menu 
![image.jpeg](https://cdn.hackclub.com/019f3e45-1045-7165-b623-cdd9c4df48c2/image.jpeg)


# 2026-07-03: Pc tab pt4 

**Total time spent: 1.25 hours**

SO.. I I got the screen mirror to work reallyyyy well it now reaches like 28 fps which is plenty for this. I fixed the buttons being pressed while on screen mirror and messing the whole thing up and I added a menu which shows up when you press button a and b simultaneously but I might change it to start and select button so it shows a “menu” b:exit a: continue.  Now I need to actually work on the controlled mode so I need to make the joysticks move the cursor and assign the buttons to the main keyboard keys and then expand this to game playing. What I am hoping to achieve is that the python scans the pc for the games you have downloaded on the pc and sends the list to esp32 then esp32 can simply say launch this game so then it opens up the game on the pc and screen mirrors only it and you play it I can’t explain it exactly but that’s the main flow I am thinking. However I haven’t tried something similar yet so I am not sure if it’s possible and how well it will work. 
![image.jpeg](https://cdn.hackclub.com/019f296d-66c0-77e1-becf-24e2bafd9326/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019f296d-a466-79b5-9138-42f4bd224ba8/image.jpeg)
Also I found out that the amplifier was defective and the gain pin was tied to the vin so when I tried increasing the gain by putting it on gnd it froze the whole system (I was lucky the short didn’t affect anything) so i changed it with a good one and now the speakers are louder by a fair amount. 
![image.jpeg](https://cdn.hackclub.com/019f296f-7f9e-7417-8af1-22f9791d6375/image.jpeg)

# 2026-07-02: Pc tab 3

**Total time spent: 40 minutes**

Started to actually work in the pc functions so far I have gotten in to actually screen mirror but it need some fixes such as disabling the buttons when on sm and adding a menu to exit. Pretty good fps around 20 stable but that’s because I have limited it there could probably get more. 
![upload failed]()
![Uploading image.jpeg...]()

# 2026-07-01: Pc tab pt2

**Total time spent: 20 minutes**

Added some like connecting to WiFi etc screens so it’s a bit more visual and started working on the actual like screen mirror. I previously have achieved it so I will need to like adapt it for here which might be a bit challenging. 
![image.jpeg](https://cdn.hackclub.com/019f1f13-57fc-7322-b58e-e57dac3b947d/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019f1f13-8118-7a22-96fa-03b8ef07ec8c/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019f1f13-a889-715b-8498-090d99af66cd/image.jpeg)

# 2026-06-29: Pc tab

**Total time spent: 1 hour**

Made the pc tab that will have screen mirror sm with control and launch games that are installed on the pc.  ![image.jpeg](https://cdn.hackclub.com/019f150d-0250-732d-9019-63ad86b28ce2/image.jpeg)

# 2026-06-28: Vibrating motors coding

**Total time spent: 1 hour**

Firstly I have to mention that I changed some wires because I think those jumper wires are poor in carrying signals. I also made the code for the vibrating motors it is split in 3 channels left right and both it has functions to start vibrating and how much it will a stop function and a play pattern function which is basically an array of pairs strength and duration. Passed them in lua and they seem to work just fine. 
![image.jpeg](https://cdn.hackclub.com/019f0fd5-5212-7e41-a482-77c08fc29307/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019f0fd5-6f32-7891-a6c0-e64bcd0bc6c0/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019f0fd5-916e-7676-be2b-c5abde1f432f/image.jpeg)

# 2026-06-27: Filament choice

**Total time spent: 2 minutes**

I chose the filament color for the design more specifically the purple that I will use for the details it’s a bit lighter than I thought but I think it will fit. For the main black color I got a Petg carbon fiber that will give a nice finish and I hope it makes it look more “professional”. 
![image.png](https://cdn.hackclub.com/019f0aae-43cb-75f6-8f07-5f4986b8f470/image.png)

# 2026-06-26: Vibrating motor wiring 

**Total time spent: 4 minutes**

Today nothing crazy since I was on foot all day long and I didn’t have time. However I did the wiring of the vibration motors so simple just connected a transistor so it won’t burn the esp32 by drawing too much current. I connect them to separate gpios so I have left and right control but I might switch it to one gpio if I run out of them and I need them. Forgot to take a picture but will upload one tomorrow. 

Update:I changed it to a motor driver because I am afraid of the motors back feeding voltage and burning the esp32 while the motor driver I think has diodes already. 

![image.jpeg](https://cdn.hackclub.com/019f054f-4f7f-71c9-8954-91826426c63f/image.jpeg)

![image.jpeg](https://cdn.hackclub.com/019f0fd2-23c4-7a88-8c15-da4960af4d88/image.jpeg)

# 2026-06-25: To do list

**Total time spent: 0 hours**

Today I had a lot of lessons so I don’t have the time to work on the project much but I wanted to so I just made a simple to do list so I will be more organised. 
![image.jpeg](https://cdn.hackclub.com/019f001e-8980-7b17-aea8-680dc31d0d8b/image.jpeg)

# 2026-06-21: Schematic and pcb? Pt.2

**Total time spent: 1 hour**

Nothing crazy for today just me strugling to make correct footprints for my components. I think i did it but i am really not sure if they are correctly sized/positioned since its my first time doing this. what i am having most issues with are the joysticks which are some replacement joysticks for nitendo switch which i really liked because they are thin but i forgot to find connectors for the ribbon cables and i dont think i can order from ali again because of some new taxes. here is the schematic so far
![Στιγμιότυπο οθόνης 2026-06-21 171820.png](https://cdn.hackclub.com/019eea91-1988-7f32-880b-203f7579b67a/%CE%A3%CF%84%CE%B9%CE%B3%CE%BC%CE%B9%CF%8C%CF%84%CF%85%CF%80%CE%BF%20%CE%BF%CE%B8%CF%8C%CE%BD%CE%B7%CF%82%202026-06-21%20171820.png)
this is the powerbank module footprint i made
![Στιγμιότυπο οθόνης 2026-06-21 171833.png](https://cdn.hackclub.com/019eea91-5778-760f-b4f4-3403c2c65b88/%CE%A3%CF%84%CE%B9%CE%B3%CE%BC%CE%B9%CF%8C%CF%84%CF%85%CF%80%CE%BF%20%CE%BF%CE%B8%CF%8C%CE%BD%CE%B7%CF%82%202026-06-21%20171833.png)
and this is my try with the joysticks
![Στιγμιότυπο οθόνης 2026-06-21 171846.png](https://cdn.hackclub.com/019eea91-884b-77b2-8d68-0825ca3fc132/%CE%A3%CF%84%CE%B9%CE%B3%CE%BC%CE%B9%CF%8C%CF%84%CF%85%CF%80%CE%BF%20%CE%BF%CE%B8%CF%8C%CE%BD%CE%B7%CF%82%202026-06-21%20171846.png)

# 2026-06-20: Schematic and pcb? Pt.1

**Total time spent: 2 hours**

As I have said before I am unsure if I will make a pcb because of the cost for shipping and lack of experience. However I am learning kicad so I made most of the schematic and found some suitable footprint for the pcb. I am not certain that I did it correctly but it shouldn’t be bad. I really struggled though with finding the correct symbol and footprint since I am new to all of this and still haven’t learned how to speed things up. I made some custom footprints for the amplifier and the speakers which should be fine. One more thing I am no sure about is if I decide to make a pcb should it be with the development boards or should I include the bare chips with all of their resistors capacitors and everything separately. First option could be easier and better for assembly and cheaper since I own the dev boards already however it might get a bit bulky and is a bit unprofessional which I could ignore.  Here is a pic from the schematic (I forgot to take a better one so this is kinda blurry and old version)
![image.jpeg](https://cdn.hackclub.com/019ee653-52e4-7d07-9700-58f8f4cf8d72/image.jpeg)



# 2026-06-19: Pcb learning

**Total time spent: 0 hours**

Today I worked on the project on an indirect way I started learning kicad for schematics and pcb however I am not sure if I will make a pcb for the project since I am not really familiar with the manufacturers.  Also I don’t have any proof so I won’t count any time. But I have to show the 3d printed pcb I made as the test

![image.jpeg](https://cdn.hackclub.com/019ee125-038f-71e3-9a85-ca14082afcc6/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019ee125-29fd-757c-b583-075df837d3bb/image.jpeg)

# 2026-06-18: Final joystick page

**Total time spent: 1 hour**

Completed the calibration and the live show for the joysticks and everything is now set. Will update this journal tomorrow. Update: fixed the calibration to actually work on the calculation by subtracting the offset this might not be the best approach but will keep for now. I also made a setting (in setting manager) for all the offsets so there is no need for calibration each time. I only have one concern and that’s a wrongfully done calibration. Let me explain if the user calibrates when the joysticks are on moved to a side then it will centre there so when you leave them the menu will constantly move and you might have to tryhard to re calibrate them.
![image.jpeg](https://cdn.hackclub.com/019edc70-15ac-74dd-bc61-391aa6813547/image.jpeg)

# 2026-06-17: Joystick settings page

**Total time spent: 1.4 hours**

I wanted a way to see the input from the joysticks live on the screen so I added a page in the settings to view live the input on a axis kind of system and added a center (calculate offset) button. It’s really close to actually working but the last compile had error and I didn’t have the time to fix it so the full working thing should be done tomorrow within 15 minutes. I also should make the offset actually be included in the axis calculations. Most of the time was actually experimenting with online web editors for ui and tft espi. I have to say I still haven’t liked any that much and I will search more to find a better one. 

Here is what I have so far 
![image.jpeg](https://cdn.hackclub.com/019ed70c-c3cd-7479-a1c6-deb8465873ea/image.jpeg)

I am also thinking of a full hi redesign but I think I will do it once the whole project is finished. 

# 2026-06-16: Some joystick design

**Total time spent: 0.5 hours**

Ummm I tried adding the joysticks to the nes emulator it wasn’t hard I just registered it as button presses after a set value but I had some problems with random movements. I am not sure what is causing it but I will figure it out tomorrow. I tried printing the values to see if they are okay but they had some offset so I put a new function which calculates the offsets but it is really draft work and I haven’t included it to the actual axis calculation. So that’s my to do list for tomorrow. Added the functions for the joysticks in the lua engine so lua games can accessthe data pretty simple by passing a table with all the values. 
![image.jpeg](https://cdn.hackclub.com/019ed178-b5e1-78b3-b53b-fee3ffeb4f14/image.jpeg)

# 2026-06-15: Joysticks added 

**Total time spent: 45 minutes**

The title is pretty self explanatory. For today I chose to to add the joysticks to my project so after finding a spare breadboard (my last one) I wired those 2 joysticks which will not be the ones in the final project (I have some other slimmer ones) but I hope the others will work exactly the same. I made a simple cpp and header file with getLX getLY and same for the right it has a dead zone so it won’t drift. However I am not sure yet how I will implement them in the project will I make new logic to include the joysticks in the menus etc or will I just register them as button presses. What I am thinking is I make it like button presses for the tabs and the emulator and for the lua it will be switchable. 

![image.jpeg](https://cdn.hackclub.com/019ecc95-2b15-7264-b028-e3a7904b5275/image.jpeg)

# 2026-06-14: More rough modeling

**Total time spent: 1 hour**

Today not anything crazy just some rought 3d designing of the back of the console. the design is no where finish and its just a prototype to see the sizes and how it will look.  (I am not sure how to put my timelapse here but will update when i learn how)
![image.png](https://cdn.hackclub.com/019ec75d-14d6-7449-bd3e-c67ea6cef551/image.png)

# 2026-06-13: NES emul final

**Total time spent: 1.5 hours**

Today I finished the nes emulator intregration and now it works amazingly well with no issues. I also added to id a master volume value in the osd.cpp of the library that changes the audio volume and added a function so I can change it and sync it with the actual volume of the console. That moved me and I worked on the volume up and down buttons which I added in the audio handler of my project. Fortunately it was pretty easy since the button manager already has callbacks for button presses etc so it didn’t need any more new logic I just added a listener for when a button is pressed it checks if it’s either volume up or down and changes the setting. What I actually want to do is add like a bar that shows the volume temporarily when you change the volume but needs a bit of work so it repairs the background when it hides. Lastly and most simple I changed the mpu to work on the same i2c wire as the mcp it was just replacing wire1 with plain wire. I am not sure what I will do after I am thinking either I try something with the touch screen or joysticks or maybe the vibration motors that I still haven’t put them in use. I have to do some calculations to see if the pins are enough for everything since I would need 1-2 more pins for the touch (if I put it in use) 4-6 pins for the joysticks ( depends if I use the switches and if yes if I plug them into the mcp) and 1-2 pins for the vibration motors (depends if I separate them left and right for more control) and I will probably need 2 more pins if I add external Bluetooth support and 1 more if I add the backlight of the tft into a gpio for brightness control can’t think of anymore stuff for now but that’s 6 pins at best and 13 at most. I counted and I have 14 gpios free but they might be strapping pins or something. 
![image.jpeg](https://cdn.hackclub.com/019ec17c-b043-7da0-8afa-2ae9eeee5b3a/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019ec17c-e262-726c-8155-69d1df3f99e7/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019ec17d-07d1-75d6-91c0-1aab7772a532/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019ec17d-3764-7353-90d0-42de25ee18f5/image.jpeg)

# 2026-06-12: NES emul part.2

**Total time spent: 1.25 hours**

After making the the nes emul tab I wanted to actually make the games run. Thought it would be pretty easy which was up to a point. I had some issues with the connection to my esp32 and bad uploads but that’s irrelevant the problem was that the audio in the nes game worked fine at first launch but when exiting and relaunching the audio wouldn’t work. I wasn’t sure what was causing this and at first I thought that it didn’t clean up correctly after exiting however that was not the case the library actually has a flag if the audio is initialised and I forgot to actually change it when cleaning up causing it not to initialise after the first time. 
![image.jpeg](https://cdn.hackclub.com/019ebd9d-7cc5-73bd-8bd9-0fd107ac9843/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019ebd9d-ab05-79a2-8c28-fc6689e46d06/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019ebd9d-d053-7ceb-b571-e3bbfb6d508a/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019ebd9d-f36e-7c51-9076-867c5006b024/image.jpeg)
I thought I had an image of the menu but it seems like I forgot to take one might update tomorrow. 

# 2026-06-10: NES emul tab

**Total time spent: 4 hours**

I am going to keep this journal short for now and update it tomorrow because I am really tired and will go to sleep. As said yesterday I got functions in the library to launch/stop games. Made an nes emulator cpp/header files for the project with i2s fixes. Also worked on a new nes emul tab but the better approach might was to include it in the games tab. I still haven’t fully integrated it into the full project. 

Update: I have no idea and can’t remember what more I wanted to write😬

Changed controller to work with the button manager 
![image.jpeg](https://cdn.hackclub.com/019eb349-d616-75f6-8641-fdc8d221e8e2/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019eb34a-00b9-7acc-9076-615c53596ac7/image.jpeg)
Don’t mind the bg color will fix it. 

![Uploading image.jpeg...]()

# 2026-06-09: Nes emulator

**Total time spent: 2.5 hours**

I did some searching around (just a simple google search) and I found that emulators are pretty legal the problem is mostly on how you get and download the actual games which in most cases break copyright laws. I tried embedding the emulator on the complete project but it’s more complicated than I thought since it is more like stand alone project rather than an actual library so I will probably need to turn it to a more library like form that includes methods to simply call and launch or stop a game and then integrate it. I did some tries and I am pretty close to achieving it but sadly there is an error that I can’t find how to debug it has to do with the i2s sound which I think the library for the song playback use different api version and they are conflicting badly. Giving this error 
![image.jpeg](https://cdn.hackclub.com/019eae12-a959-76eb-bb61-354dba63b2f8/image.jpeg)

I initially wanted to work on the volume button today so I solder some pins to easily put on the breadboard 
![image.jpeg](https://cdn.hackclub.com/019eae13-d31c-7aa5-b945-ea2c01930e0d/image.jpeg)
The supplier didn’t have like what each pin is what so I missed the ground but that doesn’t matter because in the next like 10 mins this happened 
![image.jpeg](https://cdn.hackclub.com/019eae14-b3b2-7c91-84a4-29e2029c8874/image.jpeg)
Yep the pads just broke off so I just turned to the emulator that I mentioned above. Tomorrow I will probably retry to fix the sounds conflicts and complete the integration and I might as well add the vibration motors if I get spare time. 

# 2026-06-08: NES emulator 

**Total time spent: 1 hour**

So I was searching about esp32 consoles and I came across retro go but it’s only esp idf which I wouldn’t want to switch now and I wouldn’t be able to embed in my project. After some search about some dsn library which is basically a nes emulator. I made some adjustments and got it working on my current setup with the mcp23017.  However I didnt try to integrate it to the whole project. It run really good with no glitches. I am quite skeptical about if I will be able to adjust it to fit my project since its more like a complete project rather than a library it basically is already init the tft the sd the max amplifier and everything so I will need to dig into this and really spend sometime in adjustments which I will probably have in this week. I also want to search if its like illegal under copyright laws to include it or whatever but I think its legal to make an emulator so I should be good but a bit research wont hurt. 

![image.jpeg](https://cdn.hackclub.com/019ea8dc-58ba-7277-8c72-cb25e2c3f0ad/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019ea8dc-9db1-7afb-8f33-a1f57db12ab4/image.jpeg)

# 2026-06-07: Lua mpu6050

**Total time spent: 1 hour**

So the title is pretty self explanatory I just added the get mpu data function to lua so the games can use it. Nothing crazy just a new mpuGetData function which returns the angle and acceleration. I can’t remember if mpu6050 provides temperature so i will search it and decide if I will use it. I made a simple lua game to test the mpu function it’s just a cube sliding in the screen as the mpu rotates. Tomorrow I will most probably be too busy studying so I might just do something really small like adding the temperature or maybe the vibration motors. 
![image.jpeg](https://cdn.hackclub.com/019ea3a6-f6bb-7b7b-a742-f8d38658884e/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019ea3a7-48e1-7d95-9433-b9ab9825fd9b/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019ea3a7-7606-70ba-b3d2-ce1fa7c94614/image.jpeg)

# 2026-06-06: Mpu6050 integration

**Total time spent: 2 hours**

So today I decided to add the mpu from yesterday to the main project. I turned it into a simple cpp and h file. However I quickly got to errors with failing to initialise. I spent like half an hour trying to debug this thing because it worked on the previous sketch. At the end it was the mcp chip which I had forgotten which uses i2c too. So I just changed the mpu to be on wire1 but I might just share the same pins with different addresses if it doesn’t affect anything. I also added a define for whether the z is enabled (so it is corrected ) or no. 
![image.jpeg](https://cdn.hackclub.com/019e9c6e-8c9f-7d23-9dc9-2a36828e2fad/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e9c6e-aac0-72b4-ad96-58dfad2bf148/image.jpeg)

# 2026-06-05: Rough design & mpu6050 tests

**Total time spent: 2 hours**

So today I woke up with much energy to work on my project but I had to study first so I lost it all. I literally couldn’t focus on one task without getting bored exhausted or frustrated. However I did some rough 3d design (reallyyyy draft) just to see how it could look but I think I will change the whole thing because it will end up looking like just box console which I don’t really like. After working on it for like 30mins I gave up and tried testing the mpu6050. As always I had problems connecting it but hopefully I remember what is always the problem something with “WHO AM I” I don’t really get what’s that but whatever. I tied using a library by electronic cats but couldn’t be connected and I switched to mpu6050 light. The readings seemed pretty stable except of course the z angle which I kinda fixed with a calibration trick I saw on tik tok. Basically you get set the mpu to be perfectly still and it takes like 3000 samples in the span of 6 seconds adds all the z angles and divide them by the samples getting the drift speed. After you have the drift speed you basically just subtract it all the time from the z angle. This approach limited the drift but didn’t eliminate it. Sadly I didn’t have enough energy to actually integrate it to the main project but it shouldn’t be hard. Also I decided that I will probably won’t even need the z angle so I could just ignore it. Also I worked a bit on my little lua game but also gave up quickly because I will probably build it from the start and maybe change the lua engine so it can execute like more than one lua script so I get split the code because it’s really messy and hard to edit. I am not sure if I will do this since idk how possible it is so I will probably just work on different aspects of the project for now. 

Now that I am looking I only took photos from the 3d model but will update if I remember it tomorrow. 

![upload failed]()

# 2026-06-04: Max98357A wav/mp3 playback

**Total time spent: 3 Hours**

So as I said yesterday I was working on audio in the whole system. Today I got the max98357a to actually play songs from the sd card. Fortunately it was pretty easy I used the esp32 audio i2s library and found an example which was basically what I needed.  I took the example and just made some simple changes to make it a cpp file instead of ino and integrated it into the project. However there is a drawback to this library which really troubles me it can’t play 2 sounds at once which basically cancel like the sounds effects with background music. I am not sure how to solve it but I will probably let it as it is for now. Also fixed the pins in the code that I changes yesterday. Some minor fixes in music tab with the progress bar which wouldn’t erase the whole previous one and just drew the new numbers and kinda became a mess. Also should mention that I made the audio loop run on core 0 so it doesn’t freeze the other tasks but it might be unnecessary and not actually freeze anything. Added the sound function to the lua but haven’t tested them yet. Lastly I fixed the rename button on the WiFi file manager and added a download button. 

[Nice playback (Iceman🔛🔝) ]
![image.jpeg](https://cdn.hackclub.com/019e9429-0470-7d66-8e17-393674004050/image.jpeg)

![image.jpeg](https://cdn.hackclub.com/019e9429-5aa3-739c-930f-6ce3a01e3e70/image.jpeg)

[Clean desk 😌]
![image.jpeg](https://cdn.hackclub.com/019e942a-5a5f-7f7a-8cb3-20f9c57dcdeb/image.jpeg)

# 2026-06-03: MAX98357A re-breaboarding

**Total time spent: 1.5 hours**

So far today I re wired the whole thing by putting a second breadboard for the esp32 so both side of gpios are accessible easily. That change forced me to rewire everything because the cables were short to reach the other side. I forgot to change the pins in the code but will soon. I also worked on the sound I added an amplifier max98357A which uses an i2s which was really easy I just choose 3 pins in random of course ones that don’t mess up with internal stuff. I used a standard i2s library and some examples I found online and it worked just fine apart from a weird sound which the speaker makes when it stops/starts but it might be fixable. However the worse thing was that the speakers that I bought and was planning on using are actually veryyy quiet and basically hard to hear them. At start I thought that it was a coding issue but even after adjusting the volume other speakers played fine except those so sadly I won’t be using those probably except if I find a fix which is unfortune since they really fit the design. Later today I will make actual playback from sd card after I tidy up my desk because it’s a real mess. I have to say that I tried plugging in some motor and it actually kinda played the tunes. 
![image.jpeg](https://cdn.hackclub.com/019e8d9c-de89-7086-9ae5-f208b2dc7bcd/image.jpeg)
[the weak speakers]
![image.jpeg](https://cdn.hackclub.com/019e8d9d-4d35-716f-8ff5-584f3ac731ca/image.jpeg)
[best replacement candidate(since I got 2)]
![image.jpeg](https://cdn.hackclub.com/019e8d9d-d461-7d41-8313-76f87be4c5da/image.jpeg)


[the before mess]

![image.jpeg](https://cdn.hackclub.com/019e8d9e-b7f9-70ad-ae2f-5e4dd32234c5/image.jpeg)

![image.jpeg](https://cdn.hackclub.com/019e8d9e-f5a5-7b9c-9c0c-daa895c4cf8f/image.jpeg)

# 2026-06-02: Esp32 s3 migration

**Total time spent: 3 hours**

So after some wait my esp32 s3 and bigger screen have arrived so at first I tried some basic draws. Sadly I quick realised that dma on tft espi doesn’t work on esp32 s3 for some reason so I will have to skip it for now and maybe find a solution later. This isn’t such big concern since JPEG files that I am using are small so it would have little to no impact. What’s bad though is that I didn’t do proper research and I bought a screen that has ili9341 driver chip which caps at 40mhz in contrast to stv7789 which supports 80mhz making it slower in raw speed however the stronger esp chip kinda compensates for this  but if I order again I will probably get one that supports 80mhz. I faced a couple issues with the spi busses in the tft espi basically you have to force use hspi or it just crashes there is a fix you can make in a header file but I just went along with hspi. After removing the dma from the test sketch it worked fine so I went ahead and made changes in the console sketch such as removing the dma and the Bluetooth audio since esp32 s3 doesn’t support classic Bluetooth as I mentioned before that lead to changes in settings tab and after some line commenting it finally worked just fineee. Actually I got it to work quicker than what I expected given that I struggled to debug just the test sketch. Also did some messing around as yesterday and managed to basically mirror my pc screen to the tft display via WiFi which worked even better because the WiFi in the s3 is better.(i did kinda added the buttons to work and played Minecraft…… won’t count the hours though because it ain’t part of the project… or should it be, will think about it). Plan for tomorrow is adding sound which is big part and maybe if I get them working quickly I add the vibration motors or something else. I do have to admit though that I noticed that my prev tft didn’t have miso which is why the read pixels didn’t work now I just attached it to a gpio and all good after some tweaking with the swap bytes. 
![image.jpeg](https://cdn.hackclub.com/019e89f6-bf10-7b2a-8c6a-97a0deb41382/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e89f6-fec8-7418-8f51-8a50aaffa779/image.jpeg)

[the crash with the spi]
![image.jpeg](https://cdn.hackclub.com/019e89f7-82f2-7251-ba4d-aa092ef4d5fe/image.jpeg)



![image.jpeg](https://cdn.hackclub.com/019e89f7-d1c1-7fa1-83dd-d740be4ac783/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e89f8-1325-7249-b86a-24a280d0e3cc/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e89f8-2ecb-7b9a-9c52-7b5995eea2a7/image.jpeg)

# 2026-06-01: Video

**Total time spent: 2hours**

So today after the successes with the jpeg I thought about playing a video by drawing a sequence of jpgs one after an other however this didn’t work quite well because the sd has some kind of overhead or something like that which kept on getting bigger so the draw speed went from 60 to 56 and then all the way up to 110ms basically too little fps for actual nice video playback. After some digging around I found about some .bin files which basically only need to be opened once reducing each draw by 20ms and keeping it stable using this I achieved 33.3 FPS which is amazing considering most movies are 24 fps either way. After that I got excited and did more messing around but to keep it short since it’s not part of the project I made the pc screen mirror to the tft display via WiFi which worked great after some tweaking reaching stable 20fps(I caped it there )

![image.jpeg](https://cdn.hackclub.com/019e84f0-ffa3-7539-9a3e-6d93c55eccc9/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e84f1-2b5c-7f92-8a90-fb2bb3c0145c/image.jpeg)

# 2026-05-31: Sd speed test and tft tests

**Total time spent: 2 hours**

So today I didnt really have much time because I gotta study since I am in middle of exam season. So I said yesterday I was thinking about sd mmc so I tun some tests for both sd mmc 1bit and sd spi i didnt bother to test 4bit since it requires much more setup for small benefits as i read. In general the sd mmc was 2x faster or even 3x a bmp file read in about 150ms in the spi while mmc took 70ms big drop however I noticed that Jpeg took 3-4ms in mmc and in spi 5-6 which is only 3ms gain so it’s basically neglactable. So after some calculations (1000/read ms) the jpg just by the read would limit the fps to 333(mmc) or 166(spi) while bmp would be 14 and 7 that’s wayyy too little since with all the drawing it would probably max out 4-5 fps using spi sd or 10fps with mmc so i thought my best option would be jpeg and trying to get the fastest decode and draw so i could probably push it to 25fps realistically. So I got to work and searched for the best decode library which I found is a jpegdec by bitbank2 which reallyyyy changed everything using this library I managed to surpass previous attempts by farrr reaching 55ms for full redraw to even 45 if dropped the quality to lowest (isn’t worth it though) just for reference the example of tft espi to draw jpeg from INTERNAL memory was only 76ms and from sd I believe around 117 or 157 can’t remember. So by the calculation it’s around 18.5fps which with esp32 s3 hope that will reach 20+fps. Weird thing is the test sketch which actually draw the jpeg says that the open from the sd is 20ms which is much more compared to the previous 6ms. I don’t think it’s worth changing from spi to mmc since I will be going with jpeg which the difference is too small and also mmc is annoying since I had to use a pull up resistor (1k) in pin2 which blocked the flashing and had to remove and place again all the time. 
![image.jpeg](https://cdn.hackclub.com/019e7fd2-31b4-779e-8c2e-9f4790930547/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e7fd2-8029-73cc-8fa7-0418964bbd75/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e7fd2-ca37-7a54-aced-5b6db8c87af1/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e7fd2-f05b-7f67-a9de-38e498fd564f/image.jpeg)

# 2026-05-30: Sd research 

**Total time spent: 0.5 hours**

So I was kinda skeptical about the speed of the whole draw display which is around 200ms per full screen redraw using a tft espi example draw jpg from sd got 117ms but that’s still around 8 fps max very slow. After some tests I found out that the biggest bottleneck is the sd read which is only around 1mbs and if my math is correct that’s around 170ms for bmp and that’s why jpg is faster since it smaller file size. I did some research and I found out about the sd mmc which esp32 provides which would basically make it 3 times+ faster so that’s a real save. Also I found that some people say that tft espi is outdated and loyvangfx is faster (I think it’s called that) so tomorrow I will try combining those 2 to see if it really makes it faster. I am optimistic that it’s possible I can get less than 50ms for full screen which would be around 20 fps max but I am unsure if that is possible. Since I don’t have an sd mmc breakout I will just solder plain pins in an sd adapter based on a photo I found ![image.png](https://cdn.hackclub.com/019e7a35-48ed-781f-82a1-b86531e3276b/image.png)

# 2026-05-29: SD WiFi config & Preferences

**Total time spent: 3.5 hours**

So how my system works is really close to the sd since everything required is stored there including settings.json games music image for the menu and basically every file need except of course the arduino sketch. However I quickly got exhausted from constantly unplugging the sd card plugging it to pc and then back to the console just to fix a small typo or wrong name. I thought this was the perfect time to develop a WiFi system for configuring the sd card files. I have to admit though that it was easier than what I was planning and I managed to get it working in around 3 hours instead of working on it the whole day. Hardest part of it was the html JavaScript part which I haven’t really worked with it besides school. However I found some pretty nice tools in google for live visual feedback and made it work with a bit of help of Claude that I used mainly for debugging and questions about html/js methods. The WiFi system is fairly simple I could say. So you head to the settings and press the file config which gives you 2 options either WiFi ap or WiFi sta. there is a difference on how you connect to it but other than that it’s the same system. WiFi ap works by creating it’s own network which you can connect like any other WiFi and you open the browser and head to http://192.something I don’t remember. WiFi sta actually needs configuration (local ssid and password ) first which can be done by the WiFi ap. It basically connects to your home network and you head to http://…… and it’s the same website as in WiFi ap. each one has its downsides and benefits like in WiFi ap you don’t have access to internet while you are connected to the network but it works everywhere even in the middle of the ocean( could also be faster since connection is direct but haven’t run tests). WiFi sta provides internet whitout need to switch networks all the time to change files but needs configuration for local network. I am planning on adding a usb config as well but I am waiting for my esp32 s3 to arrive which has the right port. Forgot to mention that it has the ability to read edit upload and rename files (idk if it worth noting but the files names are sent in a json format for faster speed and the file uploads are done in small chunks because ram is limited)  .I also should note that I have set it up to start only when you press the button in settings cause it takes a lot of heap memory so having it in the background would stop other stuff from working. Apart from that I took like half an hour to set up a header file which basically holds the preferences such as text color bg color selected color fonts and I might add more later (changed the selected color to purple at it fits so well)

![image.jpeg](https://cdn.hackclub.com/019e7466-1936-7eb0-87e0-a6fe5b238783/image.jpeg)

![image.jpeg](https://cdn.hackclub.com/019e7466-5866-744f-bb68-5c2c92f4e955/image.jpeg)

![image.jpeg](https://cdn.hackclub.com/019e7466-a042-75db-9f76-2f8083507932/image.jpeg)

(Look how pretty😌)
![image.jpeg](https://cdn.hackclub.com/019e7467-4eed-7950-8c1f-6eadc1ccf2df/image.jpeg)

# 2026-05-28: Sd rewiring & sprite fix

**Total time spent: 1.25 hour**

So today I focused on yesterday’s issue with the screen flickering when drawing anything. I first suspected that tft.startWrite was causing this but after a quick test it didn’t do anything so then I turned to the sd card. Turns out sd was really causing the problem even though they are in different spi buses but when I called sd.open it flicker. At first I tried looking around the code but no visible problem so the I thought it must be a power problem so I added some capacitors in the power rail but the issue persisted. My next thought was to change the pins and maybe the gpios I had chosen were internally connected to something so I used the default hspi pins. However pin12 caused an issue something with internal flash so I changed it to 16 but it was less unstable I am not sure why. But I did understand something from it since I had to use normal breadboard cables and no jumper wires. The cables seemed to have better contact with the breadboard so the signal was more stable. After understanding that I switched back to initial pins using the breadboard cables and the issue dropped by a fair amount still not perfect but I am now guessing that once everything is soldered together the signal will be even better and practically eliminate the problem. The sprite fix was a 2 minute job I just forgot to pass a transparent color value to the function so it kept the background so I just added it to the lua functions and in the sprite manager and now it’s just fine.

[the problem with pin12]
![image.jpeg](https://cdn.hackclub.com/019e6fe6-c127-7d23-89b4-6c736e02ce75/image.jpeg)

[first reroute]
![image.jpeg](https://cdn.hackclub.com/019e6fe7-8f02-7b1a-a2f6-a82241099d34/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e6fe7-c467-7fa8-9d32-cfa19d3a7a6c/image.jpeg)

[final connection]
![image.jpeg](https://cdn.hackclub.com/019e6fe8-6390-7a0a-89d3-8084903a1e17/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e6fe8-88b9-7892-9e69-124d2cb4d21f/image.jpeg)

I don’t have a picture that clearly shows the sprite fix since I forgot to take one.

# 2026-05-27: Little game try

**Total time spent: 0 hours**

So I made a little game using some assets by an awesome guy. I will link his website tomorrow since I don’t recall right now and I can’t find it. It’s just a simple test that the lua works fine only thig it does is move around and stop at obstacles like houses but I am facing an issue while I only draw a specific region the whole display seems to turn on and off but I am unsure what is causing this. I am not registering any hours since as it’s only for testing and fooling around. ![image.jpeg](https://cdn.hackclub.com/019e6aef-2f32-73c6-9dbd-abfabed0cebc/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e6aef-5e78-7d8e-8104-580b721b6438/image.jpeg)

# 2026-05-26: GitHub readme

**Total time spent: 0.25 Hours**

I finally updated the GitHub readme and now it has emojis which for some reason took me much time and complete feature list and issue that I am working on which I hope I will remember to update. Unfortunately I still haven’t uploaded the arduino sketch and wiring diagrams since I don’t have access to my pc right now.![image.png](https://cdn.hackclub.com/019e6590-8175-7176-a28e-cdda30cafc20/image.png)

# 2026-05-25: Sanity crisis

**Total time spent: 4.25 Hours**

So the title sums everything up. I decided that today’s task was to implement a lua interpreter to run games from the sd card. I imagined it would be simple since I have worked on a similar thing before.(I have to note that the previous time was incomplete). But as I said I lost all my sanity trying to achieve it. There were always errors saying that the memory was not enough while the lua file was only 2kb so I blamed the lua wrapper that I was using which to be fair lacks many methods. So I switched to a different library I think called lua for esp32 or something like that much better it’s basically the whole lua well kinda.. . After a lot of time trying to understand each method what to use why it errored I managed to make a basic run/ stop function and inderstood how to register functions. (I spent like half an hour trying to debug a L which was internally used by the library so it failed). After building the basic I added more functions including showText fillScreen millis stopLua and more so now they can be called inside the lua script. But I have to say what the biggest headache was.. there was an error showing that had to do with a lua.h and lua.cpp inside my sketch which I had before but I deleted them so I had to check 20 times through the files and nothing. After some searching and painkillers I found out that they were stored in cache and I had to clear it which fortunately was easy. After all of that I made a simple snake game which run just fine after couple of performance and appearance fixes. Almost forgot to mention that I had to disable the Bluetooth because it consumed a lot of heap memory and lua couldn’t run fortunately I have ordered an esp32 s3 which has psram so there won’t be any limits BUT the worst thing is that the s3 doesnt support Bluetooth classic therefore it isn’t able to play music or receive via Bluetooth so I either forget about those Bluetooth functions and cry about the time I spent to getting them work or use a double chip method like 2 boards which communicate with each other but that would consume more physical space and energy. I guess I could search for a classic esp32 with psram but I am unsure if it does exist and I really don’t want to order again
![image.jpeg](https://cdn.hackclub.com/019e60b0-a969-7a21-a23e-5315451b73b7/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e60b0-cd5a-7f2e-bae6-c4ed52849ba5/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e60b1-3fe7-7e73-a26c-de3a81364e87/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e60b1-6baf-7b6f-b726-9ee578cf4f86/image.jpeg)

# 2026-05-24: Bluetooth fixes

**Total time spent: 2.25 Hours**

So I got some time between studying and I read the header file of the Bluetooth library I am using and I understood that I was using many methods wrong. Fixed the whole scanning for devices functions and reworked the logic so now it doesn’t freeze but I might add an end() some where so it doesn’t overload the cpu when Bluetooth isn’t in use. I remade mostly of the btaudio cpp and h with more correctly approaches but I am facing some issues with Bluetooth states like I tested and it return 0-3 depending if it’s connected or connecting disconnected etc but for some reason the if(…=1) seems to break the whole connect thingy so I am unsure on what to do. Doing this the scan menu is much cleaner so now when you press scan it doesn’t freeze the whole system like it did before but when it finds a new device it instantly shows it as available. Also I fixed the auto reconnect feature which I previously used a custom one which checked a json that was created with info and if it wasconnected but now I simply switched to set_auto_connect() which works much much better. 
![image.jpeg](https://cdn.hackclub.com/019e5b91-65db-7fe0-8814-91cd14e865b7/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e5b91-9b39-7bb1-8638-7a9dc0452ed1/image.jpeg)
(Note: there aren’t any visible changes from previous version because I can’t show them in images )

# 2026-05-23: Settings tab pt2

**Total time spent: 3 Hours**

Previously the settings tab was just the subtabs it has but now I actually add functionality. There are 4 subtabs but I might add more. There is display which you change brightness and sleep time out but I still haven’t worked on actually getting those to work and I don’t know if I am going to soon. Bluetooth subtab which has scan disconnect and auto reconnect settings and an indicator showing connected device. To be honest it needs improvement with stuff like scanning since when you press scan it “pauses” the whole thing for 15 seconds and then shows the results also I should add a connecting screen which shows that the connect is being processed and shows if connected or failed. Also there is the audio subtab which has volume and audio output but I need to change couple things like remove the audio output selection from music tab and make it when connects to Bluetooth it switches to it automatically and back when disconnected. (Note that the volume will be changed from buttons so you dont need to run to settings each time). And lastly there is settings subtab which shows info like uptime and free heap and sd status. I am thinking of adding a subtab to change the appearance but i will have to rework a lot of stuff so not for now. I faced some problems such as screen flickering but i managed to solve it with only redrawing the needed places. Forgot to mention that I added a settingsmanager which stores all the settings to a json in the sd card so I don’t have to change them all the time.(it was kinda hard since I thought about it after a built the whole thing)![image.jpeg](https://cdn.hackclub.com/019e54e0-1d71-79da-8f1a-a17c68864915/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e54e0-4d92-7cdf-9a58-db82f031aa09/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e54e0-85a4-7036-86bc-0722099d3b6d/image.jpeg)

# 2026-05-22: Settings tab design

**Total time spent: 0.5 hours**

So I created a simple like setting screen with a list of the settings I think I will need but I still haven’t created the actual setting change and the subtabs of each selection. 
![image.jpeg](https://cdn.hackclub.com/019e50f0-b411-739c-a700-da59cb485d8a/image.jpeg)

# 2026-05-21: Pam8403

**Total time spent: 1.5 hour**

Made a lilts demo sketch for the pam8403 but I couldn’t get it to work properly. It just made weird noises. I just figured out that pam8403 ain’t really great with an esp32 so I just left it. I will order some better i2s amplifier and will try those ones on the meanwhile i am going to ignore music and sound for a while or only use Bluetooth. 
![image.jpeg](https://cdn.hackclub.com/019e4ba2-f891-71eb-98fc-dba7de90ea38/image.jpeg)

# 2026-05-20: Music tab coding

**Total time spent: 4.5 hours**

So after 5 hours I managed to make the tab system that I wanted. So it uses a simple flow when you enter the music tab you select the output either the built in speaker or Bluetooth headphones (actual playing and speakers aren’t added yet but will probably add them soon not sure when since it mid exams season). After you choose the output there is a list of playlists/albums (folders found at /music on the sd card) pressing each one let you choose the song from the folder. The folder als has an info.json which includes artist release year and name and a cover.jpg. One of the hardest parts was the progress bar since it needs good optimisation because it changes frequently. Also include functions for pause/resume song and next/previous. What’s left is to add a button to play the playlist and not individually each song and to include the actual player for the music either Bluetooth or speakers which shouldn’t be a problem. 
![image.jpeg](https://cdn.hackclub.com/019e46d9-977a-7e59-8bf3-ee6250b9d8cb/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e46da-1bc2-7ac9-8d8e-09e8aa45622b/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e46da-5111-7fe3-a8a8-bc3d37603a77/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e46da-8ea6-7911-b8df-593b3b2bf42d/image.jpeg)

# 2026-05-18: Inner tab game code

**Total time spent: 1 hour**

So I coded the inner tab design of the games tab as I said before. So it’s like a game selection tab with scrolling features that’s expandable it reads the games from the sd and I am going to add a launch feature next time. Note those shown are ghost games and don’t actually exist I just took a bunch of folders I had and dropped them in the sd card.
![image.jpeg](https://cdn.hackclub.com/019e3c5e-f0f8-7e21-8823-b47f51dacf9b/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e3c5f-5337-79ce-878a-2d5aa39164ce/image.jpeg)

![image.jpeg](https://cdn.hackclub.com/019e3c5f-8dc5-7061-bfb5-114c5c1fc075/image.jpeg)

# 2026-05-17: Tabs basic coding 

**Total time spent: 3.5 Hours**

So I did the basic coding for the tabs. By tabs I mean the screens at the start like setting games music etc the reason why it took that much time is because I tried making clean reusable code so I could extend it in the future and also I had to recompile each time until I found the best design. Pretty satisfying result but now I need to continue to the “inside” tab drawing. 
![image.jpeg](https://cdn.hackclub.com/019e374e-150e-73c0-bfd1-1546817cf6e9/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e374e-404e-75b7-a92a-db09972feeab/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e374e-6633-70d4-8dcf-97602c90c72c/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e374e-a037-7c15-8511-c1382ead801e/image.jpeg)

# 2026-05-17: Buttons Coding

**Total time spent: 1.25 Hours**

An important aspect of this project is how the buttons are handled. So there needs to be a  main code which makes things simple to use later on. This piece of code includes functions  like isDown pressed anyPressed etc and callbacks like addListener. Its built for the MCP23017 chip and it works kinda like an input manager. This way there wont be many if statements in the rest of the code so the implementing buttons will be fairly simple (as i hope at least). I faced some issues with something called NACK still not sure what it really is but i managed to fix it. It took a bit more time than i planned since i had to do some searching for code examples about the chip.
![image0 (7).jpeg](https://cdn.hackclub.com/019e3638-d713-71bd-9730-d94d0a833318/image0%20(7).jpeg)
![image1 (3).jpeg](https://cdn.hackclub.com/019e3638-f60e-738c-b633-7000776c31f8/image1%20(3).jpeg)

# 2026-05-16: Mcp23017

**Total time spent: 0.5 Hours**

So I added the mcp23017 chip so now I can add up to 16 buttons with only 3 gpios instead of 16 which is pretty good since there are more available pins for other components that will be added on the future. I had some trouble wiring because I don’t have the right wire length for breadboard but I managed by combining everything also I was missing 2 resistors 4.7k ohms between 3.3v and sda/scl so I couldn’t understand why it didn’t work. Tested with a simple sketch and everything seems fine and even better because the chip has interupt pins so there isn’t a need to loop checks. 
![image.jpeg](https://cdn.hackclub.com/019e316b-408e-774a-b59e-916c3c6a041e/image.jpeg)
![image.jpeg](https://cdn.hackclub.com/019e316b-78dc-735f-beb6-d4ad081714e7/image.jpeg)

# 2026-05-16: Breadboard Assembly

**Total time spent: 1 Hours**

So I made a quick prototype of the console in a breadboard but its basically very limited compared to the project i am planning, i mean that it doesnt have all the components just sd card esp32 tft display and the buttons. I am going to test it and find the best work flow for everything. In the next version i will try adding a chip called mcp23017 which lets you read many buttons with only 2 or 3 pins so i have more available gpios. I should also note that i added an antenna to the esp32 by scrapping the pcb and soldering one, there are plenty tutorials if you want but I don’t recall which exactly I followed .

![image0 (1).jpeg](https://cdn.hackclub.com/019e310d-16e6-7357-9cfe-5a690bb06e65/image0%20(1).jpeg)
![image0.jpeg](https://cdn.hackclub.com/019e310d-329f-7d30-b5a3-2b034d7442a3/image0.jpeg)

