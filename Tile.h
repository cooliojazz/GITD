#ifndef TILE_H
#define	TILE_H

#include <iostream>
#include <vector>
#include "structs.h"
#include "utils.h"

using namespace std;

class Tile {
    tileT tileType; 
    directionT orientation; // this * 90 to get rotation
    int xLoc; //The X-coordinate in the :level of the tile
    int yLoc; //The Y-coordiante in the level of the tile

public:

    Tile (int type, int rotation, int x, int y);

    bool moveValid (directionT direction);
    
    bool moveValid(SDL_Rect* p);

    int getXLoc();

    int getYLoc();
    
    tileT getType();
    
    directionT getRot();

};

#endif	/* TILE_H */

