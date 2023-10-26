#pragma once
#include <Arduboy2.h>
#include "Engine.h"

#define DOWN  0
#define LEFT  1
#define RIGHT 2
#define UP    3

class GameObject {
	
  public:
	struct Struct
	{
    	    float x = 160;
    	    float y = 0;
    	    float velX = 0;
          float velY = 0;
          uint8_t speed = 1;
          uint8_t dir = DOWN;
	} entity;

	GameObject();
	void input();
  void update(uint8_t );
  void draw(float, float);
  void animate();
  void Collide(float x, float y,float velx, float vely);

  uint8_t deltaTime;
  const uint8_t *spr_frame;
  const uint8_t *mask_frame;
  uint8_t frame = 0;

  private:
};