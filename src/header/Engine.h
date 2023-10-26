#pragma once
#include <Arduboy2.h>

static Arduboy2 arduboy;

// Constants
constexpr uint8_t tileSize = 16;
static uint8_t mapSizeX = 20;
static uint8_t mapSizeY = 18;
static uint16_t fullMapWidth = mapSizeX * tileSize;
static uint16_t fullMapHeight = mapSizeY * tileSize;
constexpr uint8_t screenSizeX = 128;
constexpr uint8_t screenSizeY = 64;

static const uint8_t frameRate = 60;

class Engine {
  public:
    Engine();
    void input();
    void update(uint8_t);
    void draw();
    void setup();
    
    unsigned long deltaTime;

    static bool checkCol(float, float);
    
    private:
};