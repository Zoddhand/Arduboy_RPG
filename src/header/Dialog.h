#pragma once

#include "engine.h"
#include "GameObject.h"
#include "Map.h"

class Dialog {
public:
  Dialog();

  void drawDialogBox();
  void printDialog(const char* t);
  void checkAndPrintDialog(GameObject& p, Map& m, uint8_t x, uint8_t y, const char*, uint8_t level = 1);
  const bool getOpen();
  void draw();
  void update();

private:
  void setText(const char* text);
  void print();
  void toggle();
  uint16_t delay = 1000;
  struct S
  {
    bool open : 1;
    bool typeWriterEffect : 1;
    const char* textToPrint;
  }s;
};