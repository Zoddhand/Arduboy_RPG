// BATTLESCREEN.CPP

#include "header/BattleScreen.h"
#include "header/Dialog.h"
#include "header/Sprites.h"
#include "header/Monster.h"

Monster monster;

static constexpr Point arrowPoint[3] = {
  {71, 36},      // Point 1
  {71, 36 + 8},  // Point 2
  {71, 36 + 16}  // Point 3
};

Battle::Battle(Dialog& dialog) : arrowLoc(0), battle(false) 
{
  d = dialog;
  uint8_t tmp;
  monStartX = 128;
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
  if(arduboy.justPressed(A_BUTTON)) 
  {
    if (arrowLoc == 0) 
    {
        d.printDialog(("You deal %d damage!"));
        if(showRightMenu == false)
          monster.takeDamage(monster.getAttack());
    }
    if (arrowLoc == 1) 
      d.printDialog("You used a Potion!     ");
    if (arrowLoc == 2)
    {
      d.printDialog("You ran away...         ");
        if(!d.getOpen())
          endBattle();
    }
    showRightMenu = false;
  }
}

void Battle::startBattle() {
  showRightMenu = true;
  monID = (rand() % 26) + 1;
  monster = MonsterFactory::createRandomMonster();
}

void Battle::endBattle() {
  battle = false;
  monStartX = 128;
  showRightMenu = false;
}

void Battle::update() 
{
  monsterTransition();
  if(!d.getOpen())
    showRightMenu = true;
  if(monster.getHP() == 0)
  {
    d.printDialog("You won!");
      if(!d.getOpen())
      {
        arduboy.delayShort(3000);
        endBattle();
      }
  }
}

void Battle::draw()
 {
    d.drawDialogBox();
    Sprites::drawOverwrite(monStartX, 0, Enemies, monster.getID() - 1);
    arduboy.print("ID: ");
    arduboy.print(monster.getID());
    arduboy.print("\nName:");
    arduboy.print(monster.getName());
    arduboy.print("\nHealth: ");
    arduboy.print(monster.getHP());

    if (showRightMenu) 
      rightMenu();
    d.draw();
}

void Battle::rightMenu()
{
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

void Battle::monsterTransition()
{
  monStartX --;
  if(monStartX <= 48) monStartX = 48;
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

bool Battle::getBattleState() { return battle; }