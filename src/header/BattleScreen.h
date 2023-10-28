#pragma once

#include "engine.h"
#include "Dialog.h"

class Battle {
public:
  Battle();

  void startBattle();
  void getRandomEncounter();
  void endBattle();
  void input();
  void update();
  void draw();

  bool getBattleState() const { return battle; }

private:
  Dialog d;
  uint8_t randEnemy;
  uint8_t number;
  bool battle;
  uint8_t arrowLoc;
  void flashScreen();
  void menuSelect();
};