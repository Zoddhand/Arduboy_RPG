#include "Dialog.h"
#include "Sprites.h"

#define length(array) ((sizeof(array)) / (sizeof(array[0])))

void Dialog::printDialog(const char* t)
{
  // this code formats and displays the dialog tiles to create the box
  for (int k = 32, frame = 0; k < 64; k += 16)
  {
    for (int i = 0; i < 128; i += 16)
    {
      frame = (i == 0 && k == 32) ? 0 : 
              (i == 0 && k == 48) ? 2 : 
              (i == 112 && k == 32) ? 1 : 
              (i == 112 && k == 48) ? 3 : 
              (k == 32) ? 5 : 4;

      SpritesB::drawPlusMask(i, k, Dialog_plus_mask, frame);
    }
  }

  arduboy.setCursor(3, 35);
  arduboy.setTextWrap(false);
  int lineLength = 20;
  int textLength = strlen(t);
  int currentPos = 0;

  while (currentPos < textLength)
  {
    int lineStart = currentPos;
    int lineEnd = min(currentPos + lineLength, textLength);
    int lastSpace = -1;

    for (int i = lineEnd - 1; i >= lineStart; --i)
    {
      if (t[i] == ' ')
      {
        lastSpace = i;
        break;
      }
    }

    lineEnd = (lastSpace != -1) ? lastSpace + 1 : lineEnd;

    for (int i = lineStart; i < lineEnd; ++i)
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

void Dialog::checkAndPrintDialog(GameObject& p, int x, int y, const char* text) {
  if ((int)p.entity.x / tileSize == x && (int)p.entity.y / tileSize == y) {
      printDialog(text);
      p.entity.velX = 0;
      p.entity.velY = 0;
    
  }
}

const char* Dialog::getMessage() const {
  return message;
}

bool Dialog::isOpen() const {
  return open;
}
