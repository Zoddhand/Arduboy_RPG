#include "header/GameObject.h"
#include "header/Engine.h"
#include "header/Sprites.h"
#include "header/Camera.h"

GameObject::GameObject()
{
}

void GameObject::input()
{
    arduboy.pollButtons();

    // Reset velocities
    entity.velX = 0;
    entity.velY = 0;

    // Horizontal movement
    if (arduboy.pressed(LEFT_BUTTON))
    {
        entity.velX = -entity.speed;
        entity.dir = LEFT;
        spr_frame = HERO_WALK_LEFT;
        mask_frame = HERO_WALK_LEFT_MASK;
    }
    else if (arduboy.pressed(RIGHT_BUTTON))
    {
        entity.velX = entity.speed;
        entity.dir = RIGHT;
        spr_frame = HERO_WALK_RIGHT;
        mask_frame = HERO_WALK_RIGHT_MASK;
    }

    // Vertical movement
    if (arduboy.pressed(UP_BUTTON))
    {
        entity.velY = -entity.speed;
        entity.dir = UP;
        spr_frame = HERO_WALK_UP;
        mask_frame = HERO_WALK_VERT_MASK;
    }
    else if (arduboy.pressed(DOWN_BUTTON))
    {
        entity.velY = entity.speed;
        entity.dir = DOWN;
        spr_frame = HERO_WALK_DOWN;
        mask_frame = HERO_WALK_VERT_MASK;
    }

    // Screen boundaries
    if (entity.x < 0)
    {
        entity.x = 0;
    }
    else if (entity.x > fullMapWidth - tileSize)
    {
        entity.x = fullMapWidth - tileSize;
    }

    if (entity.y < 0)
    {
        entity.y = 0;
    }
    else if (entity.y > fullMapHeight - tileSize)
    {
        entity.y = fullMapHeight - tileSize;
    }
    
    // This basically fixes letting you slide on the wall with two buttons pressed. if we're going down or up and not touching a wall, dont allow velX movement.
    if(entity.dir == DOWN && !Engine::checkCol(entity.x + entity.velX, entity.y + entity.velY) || entity.dir == UP && !Engine::checkCol(entity.x + entity.velX, entity.y + entity.velY))
      entity.velX = 0;
}

void GameObject::update(unsigned long dt)
{
    deltaTime = dt;
    animate();

    // Calculate the intended new position for the player
    float newX = entity.x + entity.velX;
    float newY = entity.y + entity.velY;

    // Check for collisions before updating the position
    bool collisionX = Engine::checkCol(newX, entity.y);
    bool collisionY = Engine::checkCol(entity.x, newY);

    // Update the position only if there is no collision
    if (!collisionX)
    {
        entity.x = newX;
    }

    if (!collisionY)
    {
        entity.y = newY;
    }
}

void GameObject::draw(float offX, float offY)
{
  int fps = 1000 / deltaTime;
  arduboy.println(Engine::checkCol(entity.x, entity.y));
  Sprites::drawExternalMask(entity.x - (offX * tileSize),entity.y - (offY * tileSize), spr_frame, mask_frame,frame, frame);
  Sprites::drawExternalMask(16, 16,  Dialog, Dialog_mask, 1,1);
}

void GameObject::animate()
{
  switch (entity.dir)
  {
    case DOWN:
      if(entity.velY == 0)
      {
        mask_frame = HERO_WALK_VERT_MASK;
        spr_frame = HERO_WALK_DOWN;
        frame = 2;
      }
      break;
    case LEFT:
      if(entity.velX == 0)
      {
        mask_frame = HERO_WALK_LEFT_MASK;
        spr_frame = HERO_WALK_LEFT;
        frame = 2;
      }
      break;
    case RIGHT:
      if(entity.velX == 0)
      {
        mask_frame = HERO_WALK_RIGHT_MASK;
        spr_frame = HERO_WALK_RIGHT;
        frame = 2;
      }
      break;
    case UP:
      if(entity.velY == 0)
      {
        mask_frame = HERO_WALK_VERT_MASK;
        spr_frame = HERO_WALK_UP;
        frame = 2;
      }
      break;
  }

  // Animate frame rate
  if (arduboy.everyXFrames(15))
  {
    /* walking frame animations */
    if(entity.velX != 0 || entity.velY != 0)
      frame ++;
    if(frame > 3)
      frame = 0;
  }
}



































