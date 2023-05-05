#ifndef IMENU_H
#define IMENU_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define bttn0 3
#define bttn1 4
#define bttn2 5
#define bttn3 6
#define bttn4 7



class IMenu{
  protected: 
    static const LiquidCrystal_I2C lcd;
  public:
    static void setup();
    virtual void menuLoop() = 0;
};

class IScrollableMenu: public IMenu
{
  protected:
    int menuOptionsSize;
    int currentOption;


    void changeOption(int change);
  public: 
    static void setupMenus();
    virtual void displayMenu() = 0;
    virtual void menuLoop();
};

class MainMenu : public IScrollableMenu{
  private:
    String* menuOptions;

    void displayMenu();
  public:
    MainMenu();
    void menuLoop();
};

class VotingMenu: public IMenu{
  private:
    int scores[4];
    String* names;
    void startNewVote();
    void printCurrentScores(int changedIndex = -1);
    void printScore(int& score);
    void finishVoting();

    long int blinkStartTime;
    long int blinkTime = 100;
    bool blinking;
    bool showVotesSetting;
  public:
    VotingMenu();
    void menuLoop();
};

class SettingsMenu: public IScrollableMenu{
  private:
    void displayMenu();
    String* menuOptions;
  public:
    SettingsMenu();
    void menuLoop();
};

class ResultMenu: public IMenu{
  private:
    int menuOptionsSize;
    int currentOption;

    String* names;
    int* scores;

    void displayMenu();
    void changeOption(int change);
  public:
    ResultMenu();
    void menuLoop();
    ~ResultMenu();
};



class NameChangeMenu: public IScrollableMenu
{
  private:
    String* menuOptions;
    void changePosition(int direction);
    void changeLetter(int direction);

    int currentLetter;
    bool editingNameMode;
  public:
    NameChangeMenu();
    void menuLoop();
     void displayMenu();
};
#endif