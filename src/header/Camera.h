#pragma once
#include "GameObject.h"
#include "Engine.h"

class Camera {
	
  public:
  Camera();
  void update(GameObject);

  struct C
  {
    float OffsetX;
    float OffsetY;
  }c;
  const int8_t visibleTilesX = screenSizeX / tileSize;
	const int8_t visibleTilesY = screenSizeY / tileSize;

  const int8_t halfVisibleTilesX = visibleTilesX / 2.0f;
  const int8_t halfVisibleTilesY = visibleTilesY / 2.0f;
  
  private:
};