#include "IMenu.h"
#include "MenuController.h"


void SettingsMenu::menuLoop(){
  IScrollableMenu::menuLoop();
  if(digitalRead(bttn1)==0){
    while(digitalRead(bttn1)==0);
    switch(currentOption){
      default:
      case 0:
        if(lcd.getBacklight())
          lcd.noBacklight();
        else
          lcd.backlight();
        break;
      case 1:
        MenuController::Instance().showResultsSetting = !MenuController::Instance().showResultsSetting;
        break;
    }

    displayMenu();
  }

  if(digitalRead(bttn4)==0){
    while(digitalRead(bttn4)==0);
      MenuController::Instance().changeMenu(new MainMenu());
  }
}

SettingsMenu::SettingsMenu(){
  //setup();
  currentOption = 0;
  this->menuOptionsSize = 2;
  this->menuOptions = new String[this->menuOptionsSize]{"Backlight on/off", "Show votes"};
  displayMenu();
  //this->lcd.cursor();
  //this->lcd.blink();
}

void SettingsMenu::displayMenu()
{
  lcd.clear();
  lcd.setCursor(0,0);

  lcd.print(menuOptions[currentOption]);
  lcd.setCursor(0, 1);
  
  bool setOption;
  switch(currentOption){
    defult:
    case 0:
      setOption = lcd.getBacklight();
      break;
    case 1:
      setOption = MenuController::Instance().showResultsSetting;
      break;
  }
    
  lcd.print("<   ");
  if(setOption)
    lcd.print("I");
  else
    lcd.print("O");

  lcd.print("   >      x");

  delay(100);
}

