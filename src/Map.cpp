#include "header/map.h"
#include "header/Camera.h"



Map::Map()
{
  
}

void Map::draw(Camera c) {
    const uint8_t startRow = c.cOffsetY;
    const int endRow = startRow + c.visibleTilesY + 1;
    const int startCol = c.cOffsetX;
    const int endCol = startCol + c.visibleTilesX + 1;

    for (int i = startRow; i < endRow; ++i) { // mapY
        for (int k = startCol; k < endCol; ++k) { // mapX
            Sprites::drawOverwrite16((k - c.cOffsetX) * tileSize, (i - c.cOffsetY) * tileSize, Tileset, pgm_read_word(&(level[i][k])));
        }
    }
}

void Map::update()
{

}

void Map::setTile()
{

}

int Map::getTile(int x, int y)
{
  return pgm_read_word(&(level[y][x]));
}
void Map::loadMap()
{

}
