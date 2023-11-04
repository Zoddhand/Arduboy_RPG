#include "header/Monster.h"
#include <avr/pgmspace.h>

void Monster::drawMonster(const Monster& monster) {
    arduboy.print(F("ID: "));
    arduboy.print(monster.getID());
    arduboy.setCursor(0, 10);
    arduboy.print(F("Name: "));
    arduboy.print(monster.getName());
    arduboy.setCursor(0, 20);
    arduboy.print(F("HP: "));
    arduboy.print(monster.getHP());
    arduboy.setCursor(0, 30);
    arduboy.print(F("Attack: "));
    arduboy.print(monster.getAttack());
    arduboy.setCursor(0, 40);
    arduboy.print(F("Defense: "));
    arduboy.print(monster.getDefense());
    arduboy.setCursor(0, 50);
    arduboy.print(F("Speed: "));
    arduboy.print(monster.getSpeed());
    arduboy.setCursor(0, 60);
    arduboy.print(F("Special: "));
    arduboy.print(monster.getSpecial());
}

// Definition of strings in Program Space

// Function to get the monster name based on the ID
