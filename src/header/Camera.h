#pragma once
#include "GameObject.h"

class Camera {
	
  public:
  Camera();
  void update(GameObject);

  int visibleTilesX, visibleTilesY; 
	float cameraX = 0.0f, cameraY = 0.0f; 
	float cOffsetX = 0, cOffsetY = 0;
  
  private:
};