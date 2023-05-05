#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include "IMenu.h"

class MenuController{
   public:
    struct Entry{
        String name;
        int result;
        Entry* next;

        Entry(String _name, int _result) : name(_name), result(_result), next(nullptr){};
    };
    static const int maxNumOfResults = 10;

    bool showResultsSetting;
    String* names;

  private:
    IMenu* currentMenu;
    MenuController(){
      names = new String[4]{"OP1","OP2","OP3","OP4"};
      IMenu::setup();
      currentMenu = new MainMenu();
      this->numOfResults = 0;

      showResultsSetting = true;
    };
    
    Entry* firstResult;
    Entry* lastResult;

    int numOfResults;

  public:
    int& getResultSize(){
      return numOfResults;
    }

    static MenuController& Instance(){
      static MenuController instance;
      return instance;
    };

    void addResult(String name, int result){
      Entry* newEntry = new Entry(name, result);
      if(numOfResults == 0){
        this->firstResult = lastResult = newEntry;
        this->numOfResults++;
      }
      else if(this->numOfResults > 0 && this->numOfResults < this->maxNumOfResults)
      {
        lastResult->next = newEntry;
        lastResult = newEntry;
        this->numOfResults++;
      }
      else {
        lastResult->next = newEntry;
        Entry* tmp = firstResult->next;
        delete firstResult;
        firstResult = tmp;
      }
    }
    Entry* getResult(int& index){
      Entry* tmp = this->firstResult;
      for(int i=0;i<index;i++){
        tmp = tmp->next;
      }
      return  tmp;
    }

    void changeMenu(IMenu* newMenu){
      delete currentMenu;
      currentMenu = newMenu;
    };

    void menuLoop(){
      currentMenu->menuLoop();
    };
};

#endif