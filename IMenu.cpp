#include "IMenu.h"
#include "MenuController.h"

const LiquidCrystal_I2C IMenu::lcd = LiquidCrystal_I2C(0x27, 16, 2);

void IMenu::setup()
{
  lcd.begin(); 
  lcd.backlight();
  lcd.setCursor(0,0);
  delay(200);
}

void IScrollableMenu::menuLoop(){
  if(digitalRead(bttn0)==0){
    changeOption(-1);
    while(digitalRead(bttn0)==0);

    displayMenu();
  }

  if(digitalRead(bttn2)==0){
    changeOption(+1);
    while(digitalRead(bttn2)==0);

    displayMenu();
  }
}

void IScrollableMenu::changeOption(int change)
{
  this->currentOption += change;
  if(this->currentOption < 0)
    this->currentOption = this->menuOptionsSize - 1;
  else if(this->currentOption >= this->menuOptionsSize)
    this->currentOption = 0;
};








