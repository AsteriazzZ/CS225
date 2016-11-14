/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

// #include <iostream>
// #include <map>
// #include "maptiles.h"
// 
// #include <utility> 
// 
// using namespace std;
// 
// MosaicCanvas* mapTiles(SourceImage const& theSource,
//                        vector<TileImage> const& theTiles)
// {
//     /**
//      * @todo Implement this function!
//      */
//     int row = theSource.getRows();
//     int col = theSource.getColumns();
//     MosaicCanvas * ret = new MosaicCanvas(row, col);
//     
//     map<Point<3>, TileImage> color2tiles;
//     vector<Point<3>> color;
//     
//     for(size_t i=0;i<theTiles.size();i++)
//     {
//         RGBAPixel tilesColor = theTiles[i].getAverageColor();
//         double tilesColorArr[3] = {(double)tilesColor.red, (double)tilesColor.green, (double)tilesColor.blue};
//         Point<3> tilesColorPoint(tilesColorArr);
//         pair<Point<3>, TileImage> newPair = make_pair(tilesColorPoint, theTiles[i]);
//         color2tiles[tilesColorPoint] =  theTiles[i];
//         
//         color.push_back(tilesColorPoint);
//     }
//     
//     // create kdtree with points of all colors from tilesImages
//     
//     KDTree<3> colorTree(color);
//     
//     for(int i=0; i<row; i++){
//         for(int j=0; j<col; j++){
//             RGBAPixel source = theSource.getRegionColor(i,j);
//             double arrSource[3] = {(double)source.red, (double)source.green, (double)source.blue};
//             Point<3> sourceColorPoint(arrSource);
//             Point<3>  foundTile = colorTree.findNearestNeighbor(sourceColorPoint);
//             TileImage targetTileImage = color2tiles[foundTile];
//             ret->setTile(i, j, targetTileImage);
//         }
//     }
//     
//     return ret;
// }

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
    /**
     * @todo Implement this function!
     */

     //build a KDtree for tiles
     vector<Point<3>> tiles;
     map<Point <3>, TileImage> map;
     for(size_t i = 0; i < theTiles.size(); i++){
     	RGBAPixel currPixel = theTiles[i].getAverageColor();
     	Point<3> tilePoint(currPixel.red, currPixel.green, currPixel.blue);

     	map[tilePoint] = theTiles[i];
     	tiles.push_back(tilePoint);
     }

     KDTree<3> tileTree(tiles);

     //for MasaicCavas
     int row = theSource.getRows();
     int col = theSource.getColumns();
     MosaicCanvas *canvas = new MosaicCanvas(row, col);
     for(int i = 0; i < row; i++){
     	for(int j = 0; j < col; j++){
     		RGBAPixel regionColor = theSource.getRegionColor(i, j);
     		Point<3>::Point regionPoint(regionColor.red, regionColor.green, regionColor.blue);
     		Point<3>::Point nearestNeighbor = tileTree.findNearestNeighbor(regionPoint);
     		TileImage regionTile = map[nearestNeighbor];
     		canvas->setTile(i, j, regionTile);
     	}
     }


	return canvas;
}
