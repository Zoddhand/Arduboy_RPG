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
  void print();
  void toggle();
  void checkAndPrintDialog(GameObject& p, Map& m, uint8_t x, uint8_t y, const char*);
  const char* getMessage();
  const bool getOpen();  // Changed the getter to const
  void setOpen(bool);
  const bool getWasPressed();  // Changed the getter to const
  void setWasPressed(bool);
  void printDialog(const char* t);
  void togglePrintDialog(const char* text);

private:
  const char* message;
  bool textPrinted;
  bool typeWriterEffect;  // Flag to control typewriter effect
};