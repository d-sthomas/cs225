#include "cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(std::string filename1) {
	png_.readFromFile(filename1);
}

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  	HSLAPixel cur_pix = png_.getPixel(x % png_.width(), y % png_.width());
  	if (cur_pix.l > .1) {  // If white pixel
  		cur_pix = HSLAPixel(HSLAPixel(200, 1, .5));
  	}
  	return cur_pix;
}
