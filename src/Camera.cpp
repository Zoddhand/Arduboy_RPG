#include "header/Camera.h"
#include "header/Engine.h"

Camera::Camera()
{
  visibleTilesX = screenSizeX / tileSize;
	visibleTilesY = screenSizeY / tileSize;
}

void Camera::update(GameObject p) {
  cameraX = p.entity.x;
  cameraY = p.entity.y;

  const float halfVisibleTilesX = visibleTilesX / 2.0f;
  const float halfVisibleTilesY = visibleTilesY / 2.0f;

  cOffsetX = (cameraX / tileSize) - halfVisibleTilesX + 0.5f;
  cOffsetY = (cameraY / tileSize) - halfVisibleTilesY + 0.5f;

  // Clamp offsets
  cOffsetX = fmaxf(0.0f, fminf(cOffsetX, static_cast<float>(mapSizeX - visibleTilesX)));
  cOffsetY = fmaxf(0.0f, fminf(cOffsetY, static_cast<float>(mapSizeY - visibleTilesY)));
}