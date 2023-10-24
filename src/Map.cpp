#include "header/map.h"
#include "header/Camera.h"



Map::Map()
{
}

void Map::draw(Camera c) {
    const int startRow = c.cOffsetY;
    const int endRow = startRow + c.visibleTilesY + 1;
    const int startCol = c.cOffsetX;
    const int endCol = startCol + c.visibleTilesX + 1;

    for (int i = startRow; i < endRow; ++i) {
        for (int k = startCol; k < endCol; ++k) {
            Sprites::drawOverwrite((k - c.cOffsetX) * tileSize, (i - c.cOffsetY) * tileSize, tileSheet, pgm_read_byte(&(level[i][k])));
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
  return pgm_read_byte(&(level[y][x]));
}
void Map::loadMap()
{

}
