#include "header/Player.h"

void Player::input()
{
  entity.velx = 0;
  entity.vely = 0;
  if(arduboy.pressed(LEFT_BUTTON)){
    entity.velx = -entity.speed;
    entity.dir = LEFT;
  }
  else if(arduboy.pressed(RIGHT_BUTTON)){
    entity.velx = entity.speed;
    entity.dir = RIGHT;
  }
  if(arduboy.pressed(UP_BUTTON)){
    entity.vely = -entity.speed;
    entity.dir = UP;
  }
  else if(arduboy.pressed(DOWN_BUTTON)){
    entity.vely = entity.speed;
    entity.dir = DOWN;
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

    if (entity.y == -1)
    {
        entity.y = -1;
    }
    else if (entity.y > fullMapHeight - tileSize)
    {
        entity.y = fullMapHeight - tileSize;
    }

      // This basically fixes letting you slide on the wall with two buttons pressed. if we're going down or up and not touching a wall, dont allow velX movement.
  if(entity.dir == DOWN && !Engine::checkCol(entity.x + entity.velx, entity.y + entity.vely) || entity.dir == UP && !Engine::checkCol(entity.x + entity.velx, entity.y + entity.vely))
      entity.velx = 0;
}