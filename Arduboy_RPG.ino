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

  unsigned long currentTime = millis();
	unsigned long deltaTime = currentTime - previousTime;
	previousTime = currentTime;

  e.input();
  e.update(deltaTime);
  e.draw();
}

