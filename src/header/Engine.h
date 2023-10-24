#pragma once
#include <Arduboy2.h>

static Arduboy2 arduboy;

// Constants
constexpr int tileSize = 16;
constexpr int mapSizeX = 24;
constexpr int mapSizeY = 24;
constexpr uint16_t fullMapWidth = mapSizeX * tileSize;
constexpr uint16_t fullMapHeight = mapSizeY * tileSize;
constexpr int screenSizeX = 128;
constexpr int screenSizeY = 64;

static const uint8_t frameRate = 60;

class Engine {
  public:
    Engine();
    void input();
    void update(unsigned long);
    void draw();
    void setup();

    unsigned long deltaTime;

    static bool checkCol(float, float);
    
    private:
      

};