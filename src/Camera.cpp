#include "header/Camera.h"

Camera::Camera()
{
  c.OffsetX = 0;
  c.OffsetY = 0;
}

void Camera::update(GameObject p) {
  c.OffsetX = (p.entity.x / tileSize) - halfVisibleTilesX + 0.5f;
  c.OffsetY = (p.entity.y / tileSize) - halfVisibleTilesY + 0.5f;

  // Clamp offsets
  c.OffsetX = fmaxf(0.0f, fminf(c.OffsetX, static_cast<float>(mapSizeX - visibleTilesX)));
  c.OffsetY = fmaxf(0.0f, fminf(c.OffsetY, static_cast<float>(mapSizeY - visibleTilesY)));
}