// BATTLESCREEN.CPP

#include "header/BattleScreen.h"
#include "header/Dialog.h"
#include "header/Sprites.h"

static constexpr Point arrowPoint[3] = {
  {71, 36},      // Point 1
  {71, 36 + 8},  // Point 2
  {71, 36 + 16}  // Point 3
};

Battle::Battle() : arrowLoc(0), battle(false) 
{
  uint8_t tmp;
  for(int8_t i = 0 ; i <= 26; i ++)
  {
    tmp = (rand() % 20) + 1;
    mon[i].x = 128;
    mon[i].hp = 500;
    mon[i].attack = tmp;
    mon[i].defense = tmp;
    mon[i].special = tmp;
    mon[i].speed = tmp;
  }
}

void Battle::startBattle() {
  draw();
}

void Battle::getRandomEncounter() {
  if (arduboy.everyXFrames(30) && !battle) {
    number = (rand() % 8) + 1;  // 1-8
    if (number == 8) {
      flashScreen();
      randEnemy = random(26);
      battle = true;
      showRightMenu = true;
      startBattle();
    }
  }
}

void Battle::input() {
  if (arrowLoc >= 2) arrowLoc = 2;  // Don't let arrow go out of bounds.
  else if (arrowLoc <= 0) arrowLoc = 0;

  if (battle && showRightMenu) {
    if (arduboy.justPressed(DOWN_BUTTON) && arrowLoc < 2) arrowLoc++;
    if (arduboy.justPressed(UP_BUTTON) && arrowLoc > 0) arrowLoc--;
  }
  if (battle) menuSelect();
}

void Battle::menuSelect() {
  if (arrowLoc == 0) {
    //d.togglePrintDialog("You deal 5 damage!, wow you're so cool");
    if(arduboy.justPressed(A_BUTTON)) 
    {
      textIndex = 0;
      showRightMenu = false;
      arduboy.setCursor(3, arrowPoint[0].y + 8);
      arduboy.print((mon[0].attack * 2) - mon[0].defense);
      arduboy.print(" damage.");
    }
  } else if (arrowLoc == 1) {
     if(arduboy.justPressed(A_BUTTON)) 
    {
      textIndex = 2;
      showRightMenu = false;
    }
  } else if (arrowLoc == 2) {
       if(arduboy.justPressed(A_BUTTON)) 
      {
        textIndex = 3;
        showRightMenu = false;
      }
    }
}


void Battle::endBattle() {
  battle = false;
  d.setOpen(false);
  mon[0].x = 128;
}

void Battle::update() {
}

void Battle::draw() {
  if (battle) {
    //if (!arduboy.notPressed(A_BUTTON)) showRightMenu = false;
    monsterTransition();
    d.drawDialogBox();

    Sprites::drawOverwrite(mon[0].x, 0, Enemies, randEnemy);
    arduboy.setCursor(48+32+8, 0);
    arduboy.print(mon[0].hp);
      if (showRightMenu) {
      Sprites::drawSelfMasked(70, 34, BATTLE_RIGHT_MENU, 0);
      Sprites::drawPlusMask(arrowPoint[arrowLoc].x, arrowPoint[arrowLoc].y, ARROW, 0);
      arduboy.setCursor(arrowPoint[arrowLoc].x + 8, arrowPoint[0].y);
      arduboy.print("Fight");
      arduboy.setCursor(arrowPoint[arrowLoc].x + 8, arrowPoint[1].y);
      arduboy.print("Items");
      arduboy.setCursor(arrowPoint[arrowLoc].x + 8, arrowPoint[2].y);
      arduboy.print("Run");
      arduboy.setCursor(0, 0);
      }
      if(!showRightMenu)
      {
        arduboy.setCursor(48+32+8, 0);
        arduboy.print(mon[0].hp);
        d.toggle();
        for(int i = 0; i < 20; i ++)
        {
          d.printDialog(text[textIndex]);
          
        }
        while(d.hasPrinted())
        {
          arduboy.pollButtons();
          if(arduboy.justPressed(A_BUTTON)) d.setPrinted(false);
            showRightMenu = true;
          if(textIndex == 3)
            endBattle();
        }
        if(textIndex == 0);
          lowerHp();
      }
  }
}

void Battle::monsterTransition()
{
  if(!d.getOpen() && battle)
  {
    mon[0].x --;
    if(mon[0].x <= 48) mon[0].x = 48;
  }
}

bool Battle::lowerHp()
{
    mon[0].hp -= mon[0].attack;
    return true;
}

void Battle::flashScreen() {
  bool inv = false;
  const uint8_t flashNum = 4;
  arduboy.invert(inv);
  for(uint8_t i = 0; i <= flashNum; i ++)
  {
    inv = !inv;
    arduboy.invert(inv);
    arduboy.delayShort(400);
  }
  arduboy.invert(false);
}