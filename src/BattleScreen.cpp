#include "header/BattleScreen.h"
#include "header/Dialog.h"
#include "header/Sprites.h"

static constexpr Point arrowPoint[3] = {
  { 71, 36 },      // Point 1
  { 71, 36 + 8 },  // Point 2
  { 71, 36 + 16 }  // Point 3
};

Battle::Battle() {
  // Initialize other battle-related variables
}

void Battle::startBattle() {
  // Set up the battle environment
  // Get player and opponent Pokemon
  // Display initial battle screen
  //d.setOpen(true);
  draw();
}

void Battle::getRandomEncounter() {
  // Generate a random encounter
  // Set opponent Pokemon based on encounter
  if (arduboy.everyXFrames(60))
    number = rand() % 8 + 1;  // 1-9
  if (battle == false) {
    if (number == 8) {
      srand(millis());
      randEnemy = rand() % 26 + 0;
      battle = true;
      startBattle();
    }
  } else {
    if (number == 1) {
      //d.setOpen(false);
      //battle = false;
    }
  }
}

void Battle::input() {
  if (arrowLoc >= 2) arrowLoc = 2;  // dont let arrow go out of bounds.
  else if (arrowLoc <= 0) arrowLoc = 0;

  if (battle && showRightMenu == true) {
    if (arduboy.justPressed(DOWN_BUTTON))
      if (arrowLoc < 2)
        arrowLoc++;
    if (arduboy.justPressed(UP_BUTTON))
      if (arrowLoc > 0)
        arrowLoc--;
  }
  if (battle)
    menuSelect();
}

void Battle::menuSelect() {
  if (arrowLoc == 0) {  // Check if the dialog is not open
    d.togglePrintDialog("You deal 5 damage!, wow you're so cool");
  }
  if (arrowLoc == 1) {  // Check if the dialog is not open
    d.togglePrintDialog("You used a Potion!     ");
  }
  if (arrowLoc == 2) {  // Check if the dialog is not open
    if (showRightMenu == true)
      d.togglePrintDialog("You ran away...         ");
    if (arduboy.everyXFrames(10)) {
      d.togglePrintDialog("You ran away...         ");
      if (showRightMenu == false) {
        battle = false;
        d.setOpen(false);
      }
    }
  }
}
void Battle::startTurn() {
  // Handle the start of a turn (player and opponent actions)
  // Update the display with current Pokemon stats
}

void Battle::playerTurn() {
  // Implement player's turn logic
  // Allow the player to choose actions (attack, switch Pokemon, etc.)
}

void Battle::opponentTurn() {
  // Implement opponent's turn logic
  // Simulate opponent's actions (attack, switch Pokemon, etc.)
}

void Battle::endTurn() {
  // Check if the battle is over (one side's Pokemon fainted)
  // If not, proceed to the next turn
}

void Battle::endBattle() {
  battle = false;
  d.setOpen(false);
}

void Battle::update() {
  // Update battle logic
  startTurn();
  playerTurn();
  opponentTurn();
  endTurn();
}

void Battle::draw() {
  // Draw the battle screen, including sprites, health bars, etc.
  if (battle) {
    if (arduboy.pressed(A_BUTTON))
      showRightMenu = false;
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
  } else arrowLoc = 0;
}