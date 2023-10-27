#pragma once
#include <Arduboy2.h>       // required to build for Arduboy
#include <ArduboyFX.h>
static Arduboy2 arduboy;

// Externals
extern uint8_t mapSizeY;
extern uint16_t fullMapHeight;
// Constants
constexpr uint8_t tileSize = 16;
constexpr uint8_t mapSizeX = 20;
constexpr uint16_t fullMapWidth = (mapSizeX * tileSize);
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