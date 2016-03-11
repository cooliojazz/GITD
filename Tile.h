/* 
 * File:   Tile.h
 * Author: Ricky
 *
 * Created on March 11, 2016, 2:46 AM
 */

#ifndef TILE_H
#define	TILE_H

enum directionT {NORTH = 0, SOUTH = 1, EAST = 2, WEST = 3};

class Tile {
    int tileType; //0 for start, 1 for DeadEnd, 2 for Straight, 3 for Bend, 4 for T, 5 for 4way, 6 for Exit
    int orientation; // this * 90 to get rotation
    int xLoc; //The X-coordinate in the level of the tile
    int yLoc; //The Y-coordiante in the level of the tile

public:

    Tile (int type, int rotation, int x, int y);

    bool moveValid (directionT direction);

    int getXLoc();

    int getYLoc();

};

#endif	/* TILE_H */

