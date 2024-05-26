
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  cs225::PNG png;      png.readFromFile("../tests/lantern.png");
  FloodFilledImage image(png);
  BFS bfs(png, Point(40, 40), 0.5);
  RainbowColorPicker rainbow(0.5);
  image.addFloodFill(bfs, rainbow );
  FloodFilledImage image2(png);
  DFS dfs(png, Point(40, 40), 0.5);
  SolidColorPicker blue(HSLAPixel(200, 1, .5));
  image.addFloodFill(dfs, blue);

  Animation animation = image.animate(200);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  //animation.write("myFloodFill.gif");
  


  return 0;
}
