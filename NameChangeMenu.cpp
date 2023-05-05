#include "IMenu.h"
#include "MenuController.h"

NameChangeMenu::NameChangeMenu(){
  this->menuOptionsSize = 4;
  this->currentOption = 0;
  this->menuOptions = MenuController::Instance().names;
  this->editingNameMode = false;
  this->currentLetter = 0;
  displayMenu();
};

void NameChangeMenu::menuLoop(){
  if(!this->editingNameMode){
    IScrollableMenu::menuLoop();

    if(digitalRead(bttn1)==0){
      while(digitalRead(bttn1)==0);
      this->editingNameMode = true;
      lcd.cursor();
      displayMenu();
    }
    if(digitalRead(bttn4)==0){
      while(digitalRead(bttn4)==0);
      MenuController::Instance().changeMenu(new MainMenu());
    }
  }
  else{
    if(digitalRead(bttn0)==0){
      while(digitalRead(bttn0)==0);
      changePosition(-1);
      displayMenu();
    }
    if(digitalRead(bttn1)==0){
      while(digitalRead(bttn1)==0);
      changePosition(+1);
      displayMenu(); 
    }
    if(digitalRead(bttn2)==0){
      while(digitalRead(bttn2)==0);
      changeLetter(+1);
      displayMenu();  
    }
    if(digitalRead(bttn3)==0){
      while(digitalRead(bttn3)==0);
      changeLetter(-1);
      displayMenu();
    }
    if(digitalRead(bttn4)==0){
      while(digitalRead(bttn4)==0);
        this->editingNameMode = false;
        lcd.noCursor();
        displayMenu();
    }
    
  }
  
};

void NameChangeMenu::displayMenu(){
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print(menuOptions[currentOption]);

  if(this->editingNameMode){
    lcd.setCursor(0, 1);
    lcd.print("<   >  ^   v   x");
    lcd.setCursor(6+this->currentLetter, 0);
  }
  else{
    lcd.setCursor(0, 1);
    lcd.print("<   +   >      x");
  }
  

  delay(50);
}

void NameChangeMenu::changePosition(int direction){
  this->currentLetter += direction;
  if(this->currentLetter > 2)
    this->currentLetter = 0;
  else if(this->currentLetter < 0)
    this->currentLetter = 2;
}

void NameChangeMenu::changeLetter(int direction){
  String* name = this->menuOptions + this->currentOption;
  String tmp = *name;
  char letter = tmp[this->currentLetter];

  if(direction >= 0)
    letter++;
  else
    letter--;

  if(letter == 64)
    letter = '9';
  else if(letter < '0')
    letter = '0';
  else if(letter == 58)
    letter = 'A';
  else if(letter > 'Z')
    letter = 'Z';
  
  tmp[this->currentLetter] = letter;
  *name = tmp;
}