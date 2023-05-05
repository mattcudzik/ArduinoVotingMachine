#include "IMenu.h"
#include "MenuController.h"

void ResultMenu::menuLoop(){
  
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

  if(digitalRead(bttn4)==0){
    while(digitalRead(bttn4)==0);
      MenuController::Instance().changeMenu(new MainMenu());
  }
}

ResultMenu::ResultMenu(){
  MenuController controller = MenuController::Instance();
  this->menuOptionsSize = controller.getResultSize();
  this->names = new String[this->menuOptionsSize];
  this->scores = new int[this->menuOptionsSize];

  for(int i = 0; i < this->menuOptionsSize; i++){
    this->names[i] = controller.getResult(i)->name;
    this->scores[i] = controller.getResult(i)->result;
  }

  this->currentOption = 0;
  displayMenu();
}

ResultMenu::~ResultMenu(){
  delete[] this->names;
  delete[] this->scores;
}

void ResultMenu::changeOption(int change)
{
  this->currentOption += change;
  if(this->currentOption < 0)
    this->currentOption = this->menuOptionsSize - 1;
  else if(this->currentOption >= this->menuOptionsSize)
    this->currentOption = 0;
};

void ResultMenu::displayMenu()
{
  lcd.clear();
  lcd.setCursor(0,0);

  if(this->menuOptionsSize == 0)
  {
    lcd.print("no results yet.");
    lcd.setCursor(0, 1);
    lcd.print("               x");
  }
  else
  {
    lcd.print(this->currentOption + 1);
    lcd.print(+ ". ");
    lcd.setCursor(4,0);
    lcd.print(names[this->currentOption] + ": " + scores[this->currentOption]);
    lcd.setCursor(0, 1);
    lcd.print("<       >      x");
  }


  delay(100);
}
