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
  void monsterTransition();
  void menuSelect();
  bool pressed = false;
  bool lowerHp();

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

  uint8_t textIndex = 0;
  const char* text[4] = {
  "Your attack did ", // 0
  mon[0].attack,
  "You have no Items.",
  "Attempting to run away." // 3
};

};

static inline uint8_t calDamage(int att, int def) { uint8_t dmg = att - def;}