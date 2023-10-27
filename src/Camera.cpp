#include "header/Camera.h"

Camera::Camera()
{
}

void Camera::update(GameObject p) {
  cOffsetX = (p.entity.x / tileSize) - halfVisibleTilesX + 0.5f;
  cOffsetY = (p.entity.y / tileSize) - halfVisibleTilesY + 0.5f;

  // Clamp offsets
  cOffsetX = fmaxf(0.0f, fminf(cOffsetX, static_cast<float>(mapSizeX - visibleTilesX)));
  cOffsetY = fmaxf(0.0f, fminf(cOffsetY, static_cast<float>(mapSizeY - visibleTilesY)));
}