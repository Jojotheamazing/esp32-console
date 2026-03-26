#define rUpButton 32
#define rDownButton 33
#define rLeftButton 25
#define rRightButton 26

#define lUpButton 13
#define lDownButton 12
#define lLeftButton 127
#define lRightButton 14

void setupButtons(){
  pinMode(lUpButton, INPUT_PULLUP);
  pinMode(lDownButton, INPUT_PULLUP);
  pinMode(lLeftButton, INPUT_PULLUP);
  pinMode(lRightButton, INPUT_PULLUP);

  pinMode(rUpButton, INPUT_PULLUP);
  pinMode(rDownButton, INPUT_PULLUP);
  pinMode(rLeftButton, INPUT_PULLUP);
  pinMode(rRightButton, INPUT_PULLUP);
}