#pragma once
#include <Arduboy2.h>
#include "Engine.h"

#define DOWN  0
#define LEFT  1
#define RIGHT 2
#define UP    3

class GameObject
{
  public:

    struct Entity
    {
      // declare using only the exact bits we need out of each byte (8bits).
      float x; // Entity X position. 10 bits used this gives me a max of 1023
      float y; // Entity Y position. 
      int8_t velx : 2; // Entity vel. 1 bit gives me -9 to 9
      int8_t vely : 2;
      byte speed : 1;
      byte dir : 2;
      const char* name;
      //byte reserved : 8; // reserve the left over bits to complete the byte.
    }entity;
    const uint8_t* image[4];

          // Default constructor
    GameObject(const char*);
    void update(uint8_t dt);
    void draw(float offX, float offY);
    void setBitmapData(const uint8_t* down,const uint8_t* left,const uint8_t* right,const uint8_t* up);

    private:
      void animate();
      byte frame;
      byte deltaTime;
};