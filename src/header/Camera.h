#pragma once
#include "GameObject.h"

class Camera {
	
  public:
  Camera();
  void update(GameObject);

  int visibleTilesX, visibleTilesY; 
	float cOffsetX = 0.0f;
  float cOffsetY = 0.0f;
  
  private:
};