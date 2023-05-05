#include "MenuController.h"

#define bttn0 3
#define bttn1 4
#define bttn2 5
#define bttn3 6
#define bttn4 7
MenuController* controller;

volatile const int resetDuration = 2500;
volatile long int timeResetStart = 0;  
void(* resetFunc) (void) = 0;

void setup() {
  pinMode(bttn0, INPUT_PULLUP);
  pinMode(bttn1, INPUT_PULLUP);
  pinMode(bttn2, INPUT_PULLUP);
  pinMode(bttn3, INPUT_PULLUP);
  pinMode(bttn4, INPUT_PULLUP);

  Serial.begin(9600);
  attachInterrupt(1,reset, CHANGE);
  

  controller = (&MenuController::Instance());
}

void loop() {
  controller->menuLoop();
}

void reset(){
  if(digitalRead(bttn0)==0){
    timeResetStart = millis();
  }
  else{
    if(millis() - timeResetStart >= resetDuration){
      resetFunc();
    }
  }
}

