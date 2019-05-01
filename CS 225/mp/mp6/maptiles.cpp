/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{     
    MosaicCanvas* result = new MosaicCanvas(theSource.getRows(),theSource.getColumns());
    vector<Point<3>> temp1;
    map<Point<3>,TileImage> tempM;
    for(size_t k = 0; k < theTiles.size(); k++){
       RGBAPixel temp2  =  theTiles[k].getAverageColor();
        double setPoint[3];
        setPoint[0] = temp2.red;
        setPoint[1] = temp2.green;
        setPoint[2] = temp2.blue;
        Point<3> temp(setPoint);
        tempM[temp] = theTiles[k];
        temp1.push_back(temp);
     }
    
    KDTree <3> kdTemp (temp1);     
    
    for (int i = 0; i<theSource.getRows();i++) {
       for ( int k = 0; k<theSource.getColumns();k++) {
         RGBAPixel ori = theSource.getRegionColor(i,k);
          double tempD [3]; 
          tempD[0] = ori.red;
          tempD[1] = ori.green;
          tempD[2] = ori.blue;
          Point<3> oriPoint(tempD); 
          Point<3> tempF = kdTemp.findNearestNeighbor(oriPoint);
          auto lookup = tempM.find(tempF);
          TileImage finalI = lookup->second;
          result->setTile(i,k,finalI);
       } 
     }
    return result;
}

