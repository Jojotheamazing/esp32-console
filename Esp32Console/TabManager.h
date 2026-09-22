#pragma once
#include "Scene.h"

struct Tab {
  const char* name;       
  const char* imagePath;  
  Scene*      scene;      
};

//static void drawPreview();
void tabManagerSetup();
void tabManagerLoop();