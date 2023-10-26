#include <Arduboy2.h>
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
  if(!arduboy.nextFrame())
		return;

  //unsigned long currentTime = millis();
  uint8_t deltaTime = millis() - previousTime;
	previousTime = millis();
  arduboy.clear();
  e.draw();
  e.input();
  e.update(deltaTime);
  arduboy.display();
}

