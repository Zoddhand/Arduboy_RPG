#pragma once
#include "GameObject.h"
#include "Engine.h"

class Camera {
	
  public:
  Camera();
  void update(GameObject);

  const uint8_t visibleTilesX = screenSizeX / tileSize;
	const uint8_t visibleTilesY = screenSizeY / tileSize;
	float cOffsetX = 0.0f;
  float cOffsetY = 0.0f;
  const uint8_t halfVisibleTilesX = visibleTilesX / 2.0f;
  const uint8_t halfVisibleTilesY = visibleTilesY / 2.0f;
  
  private:
};