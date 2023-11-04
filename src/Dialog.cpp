// DIALOG.CPP

#include "header/Dialog.h"

#define length(array) ((sizeof(array)) / (sizeof(array[0])))


Dialog::Dialog() { s.typeWriterEffect = false; }

void Dialog::drawDialogBox() {
  for (uint8_t k = 32, frame = 0; k < 64; k += 16) {
    for (uint8_t i = 0; i < 128; i += 16) {
      frame = (i == 0 && k == 32) ? 0 :
              (i == 0 && k == 48) ? 2 :
              (i == 112 && k == 32) ? 1 :
              (i == 112 && k == 48) ? 3 :
              (k == 32) ? 5 : 4;

      SpritesB::drawOverwrite(i, k, DIALOG_BOX, frame);
    }
  }
}

void Dialog::printDialog(const char* t) {
  toggle();
  setText(t);
}

void Dialog:: update()
{
}
void Dialog::draw()
{
  print();
}
////////////////////////////////////////////////////////////////////////////////////////
void Dialog::print() {
  if (!s.open || s.textToPrint == nullptr) {
    return; // Dialog is closed or no text to print
  }

  drawDialogBox();

  arduboy.setCursor(3, 35);
  arduboy.setTextWrap(false);
  uint8_t lineLength = 20;
  uint8_t textLength = strlen(s.textToPrint);
  uint8_t currentPos = 0;
  uint8_t linesPrinted = 0;
  uint8_t currentPageLines = 0;
  

  while (currentPos < textLength && linesPrinted < 3) {
    if (currentPageLines == 0) {
      arduboy.fillRect(3, 35, 120, 24, BLACK);
    }
    uint8_t lineStart = currentPos;
    uint8_t lineEnd = min(currentPos + lineLength, textLength);
    int lastSpace = -1;

    for (uint8_t i = lineEnd - 1; i >= lineStart; --i) {
      if (s.textToPrint[i] == ' ') {
        lastSpace = i;
        break;
      }
    }

    lineEnd = (lastSpace != -1) ? lastSpace + 1 : lineEnd;

    for (uint8_t i = lineStart; i < lineEnd; ++i) {
      if (s.typeWriterEffect) {
        arduboy.write(s.textToPrint[i]);
        arduboy.delayShort(50);
        arduboy.display();
      } else {
        arduboy.write(s.textToPrint[i]);
      }
    }

    // If we are on the 3rd line, reset the cursor position and manage pages
    if (++currentPageLines == 3) {
      linesPrinted++;
      currentPageLines = 0;
      arduboy.setCursor(3, 35);

      // Introduce a delay after the 3rd line of each page except the last one
      if (linesPrinted <= 2) {
        arduboy.delayShort(delay);  // Adjust the delay time as needed
      }
    } else {
      arduboy.setCursor(3, arduboy.getCursorY() + 8);
    }
    currentPos = lineEnd;
  }
  arduboy.setCursor(0, 0);
  if (s.typeWriterEffect && currentPos == textLength) {
    s.typeWriterEffect = false;
    delay = 0;
  }
}


///////////////////////////////////////////////////////////////////////////////////////
void Dialog::toggle() {
  s.open = !s.open;
  s.typeWriterEffect = true;
  delay = 1000;
}

void Dialog::checkAndPrintDialog(GameObject& p, Map& m, uint8_t x, uint8_t y, const char* text, uint8_t level = 1) {
  if ((int)(p.entity.x + 8) / tileSize == x && (int)(p.entity.y) / tileSize == y && curLevel == level && p.entity.dir == UP) {
      printDialog(text);
  }
}

const bool Dialog::getOpen() {
  return s.open;
}

void Dialog::setText(const char* text) {
    s.textToPrint = nullptr;
    s.textToPrint = text;
}
