#pragma once
#include <Arduboy2.h>
#include "Sprites.h"
#include "Engine.h"
#include "Camera.h"
#include "Levels.h"

// game idea, grass where you fight rpg battles that drop seeds or items to farm with.
class Map {
	
  public:
    Map();
    void draw(Camera, uint8_t level); // Pass the current level as a parameter
    int getTile(int x, int y);
    private:
      const uint8_t* getLevel(uint8_t);
    const uint8_t* currentLevelArray = nullptr;
};