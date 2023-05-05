#include "IMenu.h"
#include "MenuController.h"

void MainMenu::displayMenu()
{
  lcd.clear();
  lcd.setCursor(0,0);

  lcd.print(menuOptions[currentOption]);
  lcd.setCursor(0, 1);
  lcd.print("<   +   >");

  delay(100);
}

MainMenu::MainMenu()
{
  currentOption = 0;
  menuOptionsSize = 4;
  menuOptions = new String[menuOptionsSize]{"Start new voting","Settings","Results history","Change names"};
  displayMenu();
};

void MainMenu::menuLoop()
{
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

  if(digitalRead(bttn1)==0){
    while(digitalRead(bttn1)==0);
    switch(currentOption){
      default:
      case 0:
        MenuController::Instance().changeMenu(new VotingMenu());
        break;
      case 1:
        MenuController::Instance().changeMenu(new SettingsMenu());
        break;
      case 2:
        MenuController::Instance().changeMenu(new ResultMenu());
        break;
      case 3:
        MenuController::Instance().changeMenu(new NameChangeMenu());
        break;
    }
  }
};