#include "Dialog.h"
#include "Sprites.h"

#define length(array) ((sizeof(array)) / (sizeof(array[0])))

void Dialog::printDialog(const char* t)
{
  drawDialogBox();

  arduboy.setCursor(3, 35);
  arduboy.setTextWrap(false);
  uint8_t lineLength = 20;
  uint8_t textLength = strlen(t);
  uint8_t currentPos = 0;

  while (currentPos < textLength)
  {
    uint8_t lineStart = currentPos;
    uint8_t lineEnd = min(currentPos + lineLength, textLength);
    int lastSpace = -1;

    for (uint8_t i = lineEnd - 1; i >= lineStart; --i)
    {
      if (t[i] == ' ')
      {
        lastSpace = i;
        break;
      }
    }

    lineEnd = (lastSpace != -1) ? lastSpace + 1 : lineEnd;

    for (uint8_t i = lineStart; i < lineEnd; ++i)
      arduboy.write(t[i]);

    arduboy.setCursor(3, arduboy.getCursorY() + 8);
    if (currentPos < textLength)
      arduboy.setCursor(3, arduboy.getCursorY());

    currentPos = lineEnd;
  }

  arduboy.setCursor(0, 0);
}

Dialog::Dialog() {}


void Dialog::toggle() {
  open = !open;
}

void Dialog::checkAndPrintDialog(GameObject& p, Map& m, uint8_t x, uint8_t y, const char* text) {
  if(p.entity.dir == UP)
    y = y;
  else if(p.entity.dir == DOWN)
    y = y + 1;

  if ((int)(p.entity.x + 8) / tileSize == x && (int)(p.entity.y) / tileSize == y) { 
    if (!buttonWasPressed && arduboy.pressed(A_BUTTON)) {
      toggle();
      buttonWasPressed = true;
    }
    else if (!arduboy.pressed(A_BUTTON)) {
      buttonWasPressed = false;
    }

    if (open) {
      printDialog(text);
      p.entity.velX = 0;
      p.entity.velY = 0;
    }
  }
}


const char* Dialog::getMessage() const {
  return message;
}

bool Dialog::isOpen() const {
  return open;
}
