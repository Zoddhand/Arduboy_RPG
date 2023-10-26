#include "header/map.h"
#include "header/Camera.h"



Map::Map(){}

void Map::draw(Camera c, uint8_t level)
{
    currentLevel = level;
    const uint16_t* currentLevelArray = getLevel(level);
    if (currentLevelArray == nullptr) {
        // Handle invalid level number
        return;
    }
    //having uint8_t might be a problem. may need 16.
    const uint8_t startRow = c.cOffsetY;
    const uint8_t endRow = startRow + c.visibleTilesY + 1;
    const uint8_t startCol = c.cOffsetX;
    const uint8_t endCol = startCol + c.visibleTilesX + 1;

    for (int i = startRow; i < endRow; ++i) {
        for (int k = startCol; k < endCol; ++k) {     
            //20 is the common # of column in each row [18][20] / [36][20]
            Sprites::drawOverwrite16((k - c.cOffsetX) * tileSize, (i - c.cOffsetY) * tileSize, Tileset, pgm_read_word(&(currentLevelArray[i * 20 + k])));
        }
    }
}

int Map::getTile(int x, int y) {
    const uint16_t* currentLevelArray = getLevel(currentLevel);
    if (currentLevelArray == nullptr) {
        // Handle invalid level number
        return -1;
    }
    return pgm_read_word(&(currentLevelArray[y * 20 + x]));
}