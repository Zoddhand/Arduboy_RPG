#include "header/Engine.h"
#include "header/GameObject.h"
#include "header/Map.h"
#include "header/Camera.h"
#include "header/Dialog.h"
#include "header/BattleScreen.h"

GameObject p;
Map m;
Camera cam;
Dialog d;
Battle b();

// GLOBALS
uint8_t mapSizeY = 18;
uint16_t fullMapHeight = mapSizeY * tileSize;

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
  if(!d.isOpen())
    p.input();

  d.checkAndPrintDialog(p, m, 3, 44, dialogs[0]);
  d.checkAndPrintDialog(p, m, 11, 5, dialogs[1]);
  d.checkAndPrintDialog(p, m, 7, 9, dialogs[2]);
  d.checkAndPrintDialog(p, m, 13, 13, dialogs[3]);
}

void Engine::update(uint8_t dt) {
  deltaTime = dt;
  changeLevel(&p,cam);
  
  cam.update(p);
  p.update(deltaTime);
}

void Engine::draw() {
  m.draw(cam,curLevel);
  p.draw(cam.cOffsetX, cam.cOffsetY);
  arduboy.drawRect((p.entity.x + 4) - cam.cOffsetX * tileSize, (p.entity.y + 4) - cam.cOffsetY * tileSize , tileSize / 2, tileSize / 2, WHITE);
}

static bool Engine::checkCol(float x, float y)
{
    const uint16_t colBoxSize = (tileSize / 2);
    const uint16_t colBoxOffset = colBoxSize / 2;

    // Convert player coordinates to map coordinates for the top-left corner
    uint16_t mapX1 = (x + colBoxOffset) / tileSize;
    uint16_t mapY1 = (y + colBoxOffset) / tileSize;

    // Convert player coordinates to map coordinates for the bottom-right corner
    uint16_t mapX2 = (x + colBoxSize - colBoxOffset) / tileSize + .5;
    uint16_t mapY2 = (y + colBoxSize - colBoxOffset) / tileSize + .5;

    // Check collision for both corners of the player
    bool collisionX = !isTileWalkable(m.getTile(mapX1, mapY1)) || !isTileWalkable(m.getTile(mapX2, mapY1)) || !isTileWalkable(m.getTile(mapX1, mapY2)) || !isTileWalkable(m.getTile(mapX2, mapY2));
    bool collisionY = !isTileWalkable(m.getTile(mapX1, mapY1)) || !isTileWalkable(m.getTile(mapX2, mapY1)) || !isTileWalkable(m.getTile(mapX1, mapY2)) || !isTileWalkable(m.getTile(mapX2, mapY2));

    return collisionX || collisionY;
}







