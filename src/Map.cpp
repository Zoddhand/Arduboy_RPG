//MAP.CPP
#include "header/map.h"
#include "header/Camera.h"

Map::Map() {}

void Map::draw(Camera c, uint8_t level) {
    currentLevel = level;
    currentLevelArray = nullptr;
    currentLevelArray = getLevel(level);

    const uint8_t startRow = c.cOffsetY;
    const uint8_t endRow = startRow + c.visibleTilesY + 1;
    const uint8_t startCol = c.cOffsetX;
    const uint8_t endCol = startCol + c.visibleTilesX + 1;

    for (uint8_t i = startRow; i < endRow; ++i) {
        for (uint8_t k = startCol; k < endCol; ++k) {
            Sprites::DrawTiles((k - c.cOffsetX) * tileSize, (i - c.cOffsetY) * tileSize, Tileset, pgm_read_byte(&(currentLevelArray[i * mapSizeX + k])));
        }
    }
}

int Map::getTile(int x, int y) {
    return pgm_read_byte(&(currentLevelArray[y * mapSizeX + x]));
}

const uint8_t* Map::getLevel(uint8_t level) {
    switch (level) {
        case 1:
            return &level1[0][0];
        case 2:
            return &level2[0][0];
        case 3:
            return &level3[0][0];
        case REDS_HOUSE_F1:
            return &level1_Red_House_F1[0][0];
        case REDS_HOUSE_F2:
            return &level1_Red_House_F2[0][0];
        default:
            return nullptr; // Handle invalid level number
    }
}
