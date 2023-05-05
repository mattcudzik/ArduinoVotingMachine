#include "IMenu.h"
#include "MenuController.h"

void VotingMenu::menuLoop(){

  if(digitalRead(bttn0)==0){
    scores[0]++;
    while(digitalRead(bttn0)==0);
    printCurrentScores(0);
  }
  if(digitalRead(bttn1)==0){
    scores[1]++;
    while(digitalRead(bttn1)==0);
    printCurrentScores(1);
  }
  if(digitalRead(bttn2)==0){
    scores[2]++;
    while(digitalRead(bttn2)==0);
    printCurrentScores(2);
  }
  if(digitalRead(bttn3)==0){
    scores[3]++;
    while(digitalRead(bttn3)==0);
    printCurrentScores(3);
  }
  if(digitalRead(bttn4)==0){
    while(digitalRead(bttn4)==0);
    finishVoting();
  }

  if(blinking){
    if(millis() - this->blinkStartTime >= this->blinkTime){
      printCurrentScores();
      blinking = false;
    }
  }
};

VotingMenu::VotingMenu(){
  names = MenuController::Instance().names;
  startNewVote();
  printCurrentScores();
  blinking = false;
  showVotesSetting = MenuController::Instance().showResultsSetting;
};

void VotingMenu::startNewVote()
{
  for(int i = 0; i < 4; i++){
    scores[i] = 0;
  }
};

void VotingMenu::printCurrentScores(int changedIndex)
{
  lcd.clear();
  lcd.setCursor(0,0);
  for(int i = 0; i<4; i++){
    if(i == changedIndex && !showVotesSetting){
      lcd.print("    ");
      blinkStartTime = millis();
      blinking = true;
    }
    else{
      lcd.print(names[i]);
      lcd.print(" ");
    }  
  }
  if(MenuController::Instance().showResultsSetting){
    for(int i=0; i<4; i++){
        lcd.setCursor(i * 4, 1);
        printScore(scores[i]);
      }      
  }
};

void VotingMenu::printScore(int& score)
{
  if(score > 99)
    lcd.print("99+");
  else
  {
    lcd.print(" ");
    lcd.print(score);
  }
};  

void VotingMenu::finishVoting(){
  int winner = 0;
  int score = scores[0];

  for(int i = 1;i < 4; i++){
    if(scores[i] > score){
      score = scores[i];
      winner = i;
    }
  }
 

  bool isWinner = true;
  if(scores[winner] == 0)
    isWinner = false;

  for(int i = 1;i < 4; i++){
    if(i == winner)
      continue;
    if(scores[i] == scores[winner])
      isWinner = false;
  }
    lcd.clear();
    lcd.setCursor(0,0);

  if(isWinner){
    MenuController::Instance().addResult(names[winner], scores[winner]);
    lcd.print("The winner is:");
    lcd.setCursor(0,1);
    lcd.print(names[winner]);
    lcd.print(" with ");
    lcd.print(scores[winner]);
    lcd.print(" votes.");
  }  
  else{
    lcd.print("There is no");
    lcd.setCursor(0,1);
    lcd.print("winner.");
  }
  delay(50);

  //wait for button up and down
  while(digitalRead(bttn4)!=0);
  while(digitalRead(bttn4)==0);

  MenuController::Instance().changeMenu(new MainMenu());
};