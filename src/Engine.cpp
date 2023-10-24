#include "header/Engine.h"
#include "header/GameObject.h"
#include "header/Map.h"
#include "header/Camera.h"

GameObject p;
Map m;
Camera cam;

Engine::Engine()
    {

    }
void Engine::setup()
{
  arduboy.begin();
  arduboy.setFrameRate(frameRate);
}
void Engine::input()
{
  arduboy.pollButtons();
  p.input();
}
void Engine::update(unsigned long dt)
{
  deltaTime = dt;
  p.update(deltaTime);
  cam.update(p);
}

void Engine::draw()
{
  arduboy.clear();
  m.draw(cam);
  p.draw(cam.cOffsetX, cam.cOffsetY);
  arduboy.println(m.getTile(10,10));
  arduboy.display();
}

static bool Engine::checkCol(float x, float y)
{
    // Convert player coordinates to map coordinates for the top-left corner
    int mapX1 = static_cast<int>(x / tileSize);
    int mapY1 = static_cast<int>(y / tileSize);

    // Convert player coordinates to map coordinates for the bottom-right corner
    int mapX2 = static_cast<int>((x + tileSize - 1) / tileSize);
    int mapY2 = static_cast<int>((y + tileSize - 1) / tileSize);

    // Check collision for both corners of the player
    bool collisionX = (m.getTile(mapX1, mapY1) == 3) || (m.getTile(mapX2, mapY1) == 3) || (m.getTile(mapX1, mapY2) == 3) || (m.getTile(mapX2, mapY2) == 3);
    bool collisionY = (m.getTile(mapX1, mapY1) == 3) || (m.getTile(mapX2, mapY1) == 3) || (m.getTile(mapX1, mapY2) == 3) || (m.getTile(mapX2, mapY2) == 3);

    return collisionX || collisionY;
}








