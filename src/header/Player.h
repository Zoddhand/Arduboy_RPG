#pragma once
#include "GameObject.h"
#include "Engine.h"

class Player : public GameObject
{
  public:
    Player(const char* name) : GameObject(name){}
    void input();
  private:

};