/* 
 * File:   Level.h
 * Author: Ricky
 *
 * Created on March 11, 2016, 2:48 AM
 */

#ifndef LEVEL_H
#define	LEVEL_H

#include "Tile.h"
#include <vector>

using namespace std;

class Level {

    typedef vector<Tile*> row;
    typedef vector<row> matrix;

    matrix tileArray; //Double vector to hold all of the tiles in the level
    Tile *start; //The start tile within the level
    Tile *end; //The end tile of the level
    Level *next; //The level that comes next in the game

public:

    Level();

    void insertTile(int tileType, int orientation, int x, int y);

    Tile* getEnd();

    void setEnd(Tile* theEnd);

    Tile* getStart();

    void setStart(Tile* theStart);

    Level* getNextLevel();

    void setNext(Level* nextLevel);

    Tile* getTile(int xDest, int yDest);

    void setTile(int xDest, int yDest, Tile* inTile);

};

#endif	/* LEVEL_H */

