#pragma once

#include "engine.h"
#include "GameObject.h"

class Dialog {
public:
  Dialog();
  void print();
  void toggle();
  void checkAndPrintDialog(GameObject& p, int x, int y, const char*);
  const char* getMessage() const;  // Add a getter for the message
  bool isOpen() const;  // Add a getter for the isOpen property
  void printDialog(const char* t);
  bool open;
private:
  const char* message;
  
};