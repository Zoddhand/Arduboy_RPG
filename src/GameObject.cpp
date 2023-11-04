#include "header/GameObject.h"

GameObject::GameObject(const char* name) {
    entity.name = name;
    entity.x = 0;
    entity.y = 0;
    entity.speed = 1;
    entity.velx = 0;
    entity.vely = 0;
    frame = 0;
}

void GameObject::setBitmapData(const uint8_t* down,const uint8_t* left,const uint8_t* right,const uint8_t* up)
{
  image[DOWN] = down;
  image[LEFT] = left;
  image[RIGHT] = right;
  image[UP] = up;
}

void GameObject::update(uint8_t dt)
{
  animate();

  // Calculate the intended new position for the player
    float newX = entity.x + entity.velx;
    float newY = entity.y + entity.vely;

    // Check for collisions before updating the position
    if (!Engine::checkCol(newX, entity.y)) {
        entity.x = newX;
    }

    if (!Engine::checkCol(entity.x, newY)) {
        entity.y = newY;
    }
}

void GameObject::draw(float offX, float offY)
{
  Sprites::drawPlusMask(entity.x - (offX * tileSize),entity.y - (offY * tileSize), image[entity.dir], frame);
}

void GameObject::animate()
{
    // Animate frame rate
  if (arduboy.everyXFrames(15))
  {
    /* walking frame animations */
    if(entity.velx != 0 || entity.vely != 0)
      frame += 1;
    if(frame > 3)
      frame = 0;
  }

  if(entity.vely == 0 && entity.velx == 0)
  {
    frame = 2;
  }
  arduboy.println("Frame:");
  arduboy.print(frame);
}