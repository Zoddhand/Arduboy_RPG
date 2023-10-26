#include "header/Engine.h"
#include "header/GameObject.h"
#include "header/Map.h"
#include "header/Camera.h"
#include "header/Dialog.h"

GameObject p;
Map m;
Camera cam;
Dialog d;

const char* dialogs[] = {
  "Milf Ketchum's Home... It's Unlocked.", // 0
  "Gary's Hot Sisters Home.",
  "Thank you for staying off the flowers.",
  "Welcome to Pallet Town." // 3
};

Engine::Engine() {}

void Engine::setup() {
  arduboy.begin();
  arduboy.setFrameRate(frameRate);
}

void Engine::input() {
  arduboy.pollButtons();
  if(arduboy.pressed(B_BUTTON))
  {
    cam.cOffsetX = 0;
    cam.cOffsetY = 0;
    changeLevel(1,&p);
  }
  if(arduboy.pressed(A_BUTTON))
  {
    cam.cOffsetX = 0;
    cam.cOffsetY = 0;
    changeLevel(2,&p);
  }
  d.checkAndPrintDialog(p, 2, 5, dialogs[0]);
  d.checkAndPrintDialog(p, 11, 5, dialogs[1]);
  d.checkAndPrintDialog(p, 7, 9, dialogs[2]);
  d.checkAndPrintDialog(p, 13, 13, dialogs[3]);
  p.input();
}

void Engine::update(uint8_t dt) {
  deltaTime = dt;
  p.update(deltaTime);
  cam.update(p);
}

void Engine::draw() {
  m.draw(cam,curLevel);
  p.draw(cam.cOffsetX, cam.cOffsetY);
}

// Old but possibly better code. change playerX to be - 8 at the start
static bool Engine::checkCol(float x, float y)
{
    const uint8_t colBoxSize = (tileSize / 2);
    const uint8_t colBoxOffset = colBoxSize / 2;

    // Convert player coordinates to map coordinates for the top-left corner
    uint8_t mapX1 = (x + colBoxOffset) / tileSize;
    uint8_t mapY1 = (y + colBoxOffset) / tileSize;

    // Convert player coordinates to map coordinates for the bottom-right corner
    uint8_t mapX2 = (x + colBoxSize - colBoxOffset) / tileSize + .5;
    uint8_t mapY2 = (y + colBoxSize - colBoxOffset) / tileSize + .5;

    // Check collision for both corners of the player
    bool collisionX = !isTileWalkable(m.getTile(mapX1, mapY1)) || !isTileWalkable(m.getTile(mapX2, mapY1)) || !isTileWalkable(m.getTile(mapX1, mapY2)) || !isTileWalkable(m.getTile(mapX2, mapY2));
    bool collisionY = !isTileWalkable(m.getTile(mapX1, mapY1)) || !isTileWalkable(m.getTile(mapX2, mapY1)) || !isTileWalkable(m.getTile(mapX1, mapY2)) || !isTileWalkable(m.getTile(mapX2, mapY2));

    return collisionX || collisionY;
}







