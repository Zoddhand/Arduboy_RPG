#pragma once
#include <Arduboy2.h>       // required to build for Arduboy
#include <ArduboyFX.h>
static Arduboy2 arduboy;

// Externals
extern uint8_t mapSizeY;
extern uint8_t mapSizeX;
extern uint16_t fullMapHeight;
extern uint16_t fullMapWidth;
extern uint8_t curLevel;
// Constants
constexpr uint8_t tileSize PROGMEM  = 16;
constexpr uint8_t screenSizeX PROGMEM = 128;
constexpr uint8_t screenSizeY PROGMEM = 64;
constexpr uint8_t numLevels = 5 + 1;




static const uint8_t frameRate = 60;

class Engine {
public:
    Engine();
    void input();
    void update(uint8_t dt);
    void draw();
    void setup();
    
    uint8_t deltaTime;
    static bool checkCol(float x, float y);
    static bool checkTile(const Point& point, uint8_t tileNumber);
    static inline void changeMapSize(uint8_t x, uint8_t y) {
        mapSizeX = x;
        mapSizeY = y;
    }

private:
    void checkSigns();
};

