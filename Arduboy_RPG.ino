#include <Arduboy2.h>       // required to build for Arduboy
#include <ArduboyFX.h>      // required to access the FX external flash
#include "src/header/Engine.h"

unsigned long previousTime = 0;

Engine e;

void setup() {
  // put your setup code here, to run once:
  e.setup();
  previousTime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!(arduboy.nextFrame()))
    return;
  arduboy.pollButtons();

  //unsigned long currentTime = millis();
  uint8_t deltaTime = millis() - previousTime;
	previousTime = millis();
  arduboy.clear();
  
  e.input();
  e.update(deltaTime);
  e.draw();
  arduboy.display();
}
