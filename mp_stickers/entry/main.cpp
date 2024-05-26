#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  cs225::Image alma;     alma.readFromFile("../tests/alma.png");
  cs225::Image i;        i.readFromFile("../tests/i.png");
  cs225::Image expected; expected.readFromFile("../tests/expected-3.png");

  
  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 40, 200);
  sheet.addSticker(i, 100, 100);
  
  return 0;
}
