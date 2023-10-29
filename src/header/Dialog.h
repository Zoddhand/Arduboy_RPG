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
  void checkAndPrintDialog(GameObject& p, Map& m, uint8_t x, uint8_t y, const char*);
  const bool getOpen();
  void draw();

private:
  void setText(const char* text);
  void print();
  void toggle();

  bool typeWriterEffect;  // Flag to control typewriter effect
  const char* textToPrint;
};