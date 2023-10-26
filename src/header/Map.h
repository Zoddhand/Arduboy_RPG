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
  void draw(Camera);
  void update();
  void setTile();
  int getTile(int, int);
  void loadMap();
  private:

};