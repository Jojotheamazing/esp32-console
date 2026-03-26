#include "display.h"


void setup() {
  // put your setup code here, to run once:
  initTFT();
  
  //if (!initSd()) { 
   // return;
 // }

}

void loop() {
  // put your main code here, to run repeatedly:
  flashColors();
}
