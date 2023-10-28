// DIALOG.CPP

#include "header/Dialog.h"

#define length(array) ((sizeof(array)) / (sizeof(array[0])))

bool open = false;
bool buttonWasPressed = false;

Dialog::Dialog() : typeWriterEffect(false) {}

void Dialog::drawDialogBox() {
  for (uint8_t k = 32, frame = 0; k < 64; k += 16) {
    for (uint8_t i = 0; i < 128; i += 16) {
      frame = (i == 0 && k == 32) ? 0 :
              (i == 0 && k == 48) ? 2 :
              (i == 112 && k == 32) ? 1 :
              (i == 112 && k == 48) ? 3 :
              (k == 32) ? 5 : 4;

      SpritesB::drawSelfMasked(i, k, DIALOG_BOX, frame);
    }
  }
}

void Dialog::printDialog(const char* t) {
  drawDialogBox();

  arduboy.setCursor(3, 35);
  arduboy.setTextWrap(false);
  uint8_t lineLength = 20;
  uint8_t textLength = strlen(t);
  uint8_t currentPos = 0;

  while (currentPos < textLength) {
    uint8_t lineStart = currentPos;
    uint8_t lineEnd = min(currentPos + lineLength, textLength);
    int lastSpace = -1;

    for (uint8_t i = lineEnd - 1; i >= lineStart; --i) {
      if (t[i] == ' ') {
        lastSpace = i;
        break;
      }
    }

    lineEnd = (lastSpace != -1) ? lastSpace + 1 : lineEnd;

    for (uint8_t i = lineStart; i < lineEnd; ++i) {
      if (typeWriterEffect) {
        arduboy.write(t[i]);
        arduboy.delayByte(50);
        arduboy.display();
      } else {
        arduboy.write(t[i]);
        printed = true;
      }
    }

    arduboy.setCursor(3, arduboy.getCursorY() + 8);
    if (currentPos < textLength) arduboy.setCursor(3, arduboy.getCursorY());

    currentPos = lineEnd;
  }

  if (typeWriterEffect && currentPos == textLength) {
    typeWriterEffect = false;
  }
  arduboy.setCursor(0, 0);
}

void Dialog::toggle() {
  open ^= true;
  typeWriterEffect ^= true;
  if (!typeWriterEffect) {
    typeWriterEffect = false;
  }
}

void Dialog::checkAndPrintDialog(GameObject& p, Map& m, uint8_t x, uint8_t y, const char* text) {
  if ((int)(p.entity.x + 8) / tileSize == x && (int)(p.entity.y) / tileSize == y) {
    if (!buttonWasPressed && arduboy.pressed(A_BUTTON)) {
      toggle();
      typeWriterEffect = true;
      buttonWasPressed = true;
    } else if (!arduboy.pressed(A_BUTTON)) {
      buttonWasPressed = false;
    }

    if (open) {
      printDialog(text);
      p.entity.velX = 0;
      p.entity.velY = 0;
    }
  }
}

void Dialog::togglePrintDialog(const char* text) {
  /*
  if (arduboy.pressed(A_BUTTON) && !buttonWasPressed) {
    toggle();
    typeWriterEffect = true;
    buttonWasPressed = true;
  } else if (!arduboy.pressed(A_BUTTON)) {
    buttonWasPressed = false;
  }

  if (open) {
    printDialog(text);
  }*/
}

const bool Dialog::getOpen() {
  return open;
}

void Dialog::setOpen(bool b) {
  open = b;
}

const bool Dialog::getWasPressed() {
  return buttonWasPressed;
}

void Dialog::setWasPressed(bool b) {
  buttonWasPressed = b;
}

 const bool Dialog::hasPrinted()
 {
    return printed;
 }

  void Dialog::setPrinted(bool b) { printed = b;}
