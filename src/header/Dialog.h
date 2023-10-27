#pragma once

#include "engine.h"
#include "GameObject.h"
#include "Map.h"

inline static void drawDialogBox()
{
    // this code formats and displays the dialog tiles to create the box
  for (uint8_t k = 32, frame = 0; k < 64; k += 16)
  {
    for (uint8_t i = 0; i < 128; i += 16)
    {
      frame = (i == 0 && k == 32) ? 0 : 
              (i == 0 && k == 48) ? 2 : 
              (i == 112 && k == 32) ? 1 : 
              (i == 112 && k == 48) ? 3 : 
              (k == 32) ? 5 : 4;

      SpritesB::drawPlusMask(i, k, Dialog_plus_mask, frame);
    }
  }
}

class Dialog {
public:
  Dialog();
  void print();
  void toggle();
  void checkAndPrintDialog(GameObject& p, Map& m, uint8_t x, uint8_t y, const char*);
  const char* getMessage() const;  // Add a getter for the message
  bool isOpen() const;  // Add a getter for the isOpen property
  void printDialog(const char* t);
  bool open;
private:
  const char* message;
  bool buttonWasPressed = false;
  
};