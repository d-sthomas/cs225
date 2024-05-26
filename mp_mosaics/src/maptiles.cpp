/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    size_t rows = theSource.getRows();
    size_t cols = theSource.getColumns();
    MosaicCanvas* newCanvas = new MosaicCanvas(rows, cols);

    std::map<Point<3>, TileImage*> pointToTile;
    vector<Point<3>> tileColors;
    tileColors.resize(theTiles.size());

    for(size_t i = 0; i < theTiles.size(); i++){
      tileColors[i] = convertToXYZ(theTiles[i].getAverageColor());
      pointToTile[tileColors[i]] = &(theTiles[i]);
    }

    KDTree<3> tiles(tileColors);

    for (size_t j = 0; j < cols; j++){
      for (size_t k = 0; k < rows; k++){
        Point<3> closest = tiles.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(k,j)));
        newCanvas->setTile(k,j, pointToTile[closest]);
      }
    }
    return newCanvas;
}

