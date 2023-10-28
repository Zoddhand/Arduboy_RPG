#pragma once
#include "engine.h"
#include "Dialog.h"



class Battle
{

  public:
    Battle();
  void startBattle();
  void getRandomEncounter();
  void startTurn();
  void playerTurn();
  void opponentTurn();
  void endTurn();
  void update();
  void draw();
  bool getBattleState(){ return battle; }
  void endBattle();
  void input();
  uint8_t arrowLoc = 0;
  void menuSelect();
  bool battle = false;
  private:
    Dialog d;
    uint8_t* number;
    uint8_t randEnemy;   
};