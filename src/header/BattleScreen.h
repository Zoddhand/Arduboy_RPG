#pragma once

#include "engine.h"
#include "Dialog.h"

class Battle {
public:
  Battle(Dialog&);

  void startBattle();
  void getRandomEncounter();
  void endBattle();
  void input();
  void update();
  void draw();

  bool getBattleState();

private:
  Dialog d;
  uint8_t randEnemy;
  uint8_t number;
  bool battle;
  uint8_t arrowLoc;
  void flashScreen();
  void menuSelect();
  void monsterTransition();

    struct Monster
  {
    uint8_t x,y;
    float hp;
    uint8_t attack;
    uint8_t defense;
    uint8_t speed;
    uint8_t special;
    const char* moves[4];
  }mon[28];
  bool ranAway = false;
  bool showRightMenu;
  void rightMenu();
};