#include "header/map.h"
#include "header/Camera.h"


Map::Map(){}

void Map::draw(Camera c, uint8_t level)
{
    currentLevel = level;
    currentLevelArray = getLevel(level);

    //having uint8_t might be a problem. may need 16.
    const uint16_t startRow = c.cOffsetY;
    const uint16_t endRow = startRow + c.visibleTilesY + 1;
    const uint16_t startCol = c.cOffsetX;
    const uint16_t endCol = startCol + c.visibleTilesX + 1;

    for (int i = startRow; i < endRow; ++i) {
        for (int k = startCol; k < endCol; ++k) {     
            //20 is the common # of column in each row [18][20] / [36][20]
            Sprites::DrawTiles((k - c.cOffsetX) * tileSize, (i - c.cOffsetY) * tileSize, Tileset, pgm_read_word(&(currentLevelArray[i * 20 + k])));
        }
    }
}

int Map::getTile(int x, int y) {
    return pgm_read_word(&(currentLevelArray[y * 20 + x]));
}

const uint16_t* Map::getLevel(uint8_t level) {
    switch (level) {
        case 1:
            return &level1[0][0];
        case 2:
            return &level2[0][0];
        default:
            return nullptr; // Handle invalid level number
    }
}
