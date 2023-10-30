#pragma once

#include "engine.h"
#include "GameObject.h"
#include "Map.h"


extern bool open;
extern bool buttonWasPressed;

class Dialog {
public:
  Dialog();

  void drawDialogBox();
  void printDialog(const char* t);
  void checkAndPrintDialog(GameObject& p, Map& m, uint8_t x, uint8_t y, const char*, uint8_t level = 1);
  const bool getOpen();
  void draw();
  void update(uint8_t);

private:
  void setText(const char* text);
  void print();
  void toggle();
  uint8_t currentLevel;
  bool typeWriterEffect;  // Flag to control typewriter effect
  const char* textToPrint;
};