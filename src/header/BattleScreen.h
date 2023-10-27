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
  private:
    Dialog d;
};