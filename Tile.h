/* 
 * File:   Tile.h
 * Author: Ricky
 *
 * Created on March 11, 2016, 2:46 AM
 */

#ifndef TILE_H
#define	TILE_H

enum directionT {NORTH = 0, SOUTH = 1, EAST = 2, WEST = 3};
//enum tileT {START = 0, DEADEND = 1, STRAIGHT = 2, BEND = 3, TJUNCT = 4, FOURWAY = 5, EXIT = 6};

class Tile {
    int tileType; 
    int orientation; // this * 90 to get rotation
    int xLoc; //The X-coordinate in the :level of the tile
    int yLoc; //The Y-coordiante in the level of the tile

public:

    Tile (int type, int rotation, int x, int y);

    bool moveValid (directionT direction);

    int getXLoc();

    int getYLoc();
    
    int getType();

};

#endif	/* TILE_H */

