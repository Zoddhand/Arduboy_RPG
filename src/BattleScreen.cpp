// BATTLESCREEN.CPP

#include "header/BattleScreen.h"
#include "header/Dialog.h"
#include "header/Sprites.h"

static constexpr Point arrowPoint[3] = {
  {71, 36},      // Point 1
  {71, 36 + 8},  // Point 2
  {71, 36 + 16}  // Point 3
};

Battle::Battle() : arrowLoc(0), battle(false) {}

void Battle::startBattle() {
  draw();
}

void Battle::getRandomEncounter() {
  if (arduboy.everyXFrames(30) && !battle) {
    number = random(1, 10);  // 1-9
    if (number == 8) {
      flashScreen();
      randEnemy = random(26);
      battle = true;
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
    d.togglePrintDialog("You deal 5 damage!, wow you're so cool");
  } else if (arrowLoc == 1) {
    d.togglePrintDialog("You used a Potion!     ");
  } else if (arrowLoc == 2) {
    if (arduboy.everyXFrames(10)) {
      d.togglePrintDialog("You ran away...         ");
      if (!showRightMenu) {
        battle = false;
        d.setOpen(false);
      }
    }
  }
}


void Battle::endBattle() {
  battle = false;
  d.setOpen(false);
}

void Battle::update() {
}

void Battle::draw() {
  if (battle) {
    if (!arduboy.notPressed(A_BUTTON)) showRightMenu = false;
    d.drawDialogBox();
    Sprites::drawOverwrite(48, 0, Enemies, randEnemy);
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
  } else {
    arrowLoc = 0;
  }
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