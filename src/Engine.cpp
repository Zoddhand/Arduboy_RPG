#include "header/Engine.h"
#include "header/GameObject.h"
#include "header/Map.h"
#include "header/Camera.h"
#include "header/Dialog.h"
#include "header/BattleScreen.h"
#include "header/Player.h"


Player p("Hero");
Map m;
Camera cam;
Dialog d;
Battle b(d);

// GLOBALS
uint8_t mapSizeY = 18;
uint8_t mapSizeX = 20;
uint16_t fullMapHeight = (mapSizeY * tileSize);
uint16_t fullMapWidth = (mapSizeX * tileSize);
uint8_t curLevel = 1;

const char* dialogs[] = {
  "Reds Home... It's Unlocked.", // 0
  "Blue's Home.", // 1
  "Thank you for staying off the flowers.", // 2
  "Welcome to Pallet Town.", // 3
  "This is supposed to be a TV." // 4 
};

Engine::Engine() {}

void Engine::setup() {
    arduboy.begin();
    arduboy.setFrameRate(frameRate);
    arduboy.initRandomSeed();

    p.setBitmapData(HERO_WALK_DOWN, HERO_WALK_LEFT, HERO_WALK_RIGHT, HERO_WALK_UP);
    p.entity.x = 160;
    p.entity.y = 0;
}

void Engine::input() {
    arduboy.pollButtons();
    if (!d.getOpen() && !b.getBattleState())
        p.input();
    else { p.entity.velx = 0; p.entity.vely = 0; }

    if (b.getBattleState())
        b.input();

    checkSigns();
}

void Engine::update(uint8_t dt) {
    deltaTime = dt;
    if (m.getTile(p.entity.x / tileSize, p.entity.y / tileSize) == 127 && p.entity.velx + p.entity.vely >= 1)
        b.getRandomEncounter();
    d.update();
    if (b.getBattleState())
      b.update();
    else 
    {
      cam.update(p);
      p.update(deltaTime);
      changeLevel(&p);
    }
}

void Engine::draw() {
    if (!b.getBattleState()) {
        m.draw(cam, curLevel);
        printAtPlayer(Grass, 127);
        p.draw(cam.c.OffsetX, cam.c.OffsetY);
        d.draw();
    }
    else
        b.draw(); 
}

static bool Engine::checkCol(float x, float y)
{
    //Draw col rect
    //arduboy.drawRect((p.entity.x + 4) - cam.cOffsetX * tileSize, (p.entity.y + 4) - cam.cOffsetY * tileSize , tileSize / 2, tileSize / 2, WHITE);
    const uint8_t colBoxSize = (tileSize / 2);
    const uint8_t colBoxOffset = colBoxSize / 2;

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

void Engine::checkSigns()
{
  if(arduboy.justPressed(A_BUTTON))
  {
    d.checkAndPrintDialog(p, m, 3, 5, dialogs[0],LEVEL1);
    d.checkAndPrintDialog(p, m, 11, 5, dialogs[1],LEVEL1);
    d.checkAndPrintDialog(p, m, 7, 9, dialogs[2],LEVEL1);
    d.checkAndPrintDialog(p, m, 13, 13, dialogs[3],LEVEL1);
    d.checkAndPrintDialog(p, m, 3, 1, dialogs[4],REDS_HOUSE_F2);
    d.checkAndPrintDialog(p, m, 4, 1, dialogs[4],REDS_HOUSE_F2);
  }
}
/*
static bool Engine::checkTile(const Point& point, uint8_t tileNumber)
{
    uint8_t mapX = point.x / tileSize;
    uint8_t mapY = point.y / tileSize;

    // Use the getTile function to get the tile number at the specified point
    uint8_t currentTile = m.getTile(mapX, mapY);

    // Check if the tile at the specified point equals the given tile number
    return (currentTile == tileNumber);
}*/

void Engine::printAtPlayer(const uint8_t* bm, uint8_t tileIndex, uint8_t frame = 0)
{
    // Calculate the tile coordinates based on the player's position
    int tileX = (p.entity.x + tileSize / 2) / tileSize;
    int tileY = (p.entity.y + tileSize / 2) / tileSize;

    // Calculate the screen coordinates based on the tile coordinates and camera offset
    int x = (tileX - cam.c.OffsetX) * tileSize;
    int y = (tileY - cam.c.OffsetY) * tileSize;

    // Draw a new tile at the calculated screen coordinates if the current tile is 127
    if (m.getTile(tileX, tileY) == tileIndex) {
        Sprites::drawOverwrite(x, y, bm, frame);
    }
}


