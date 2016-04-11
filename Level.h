#ifndef LEVEL_H
#define	LEVEL_H

#include "Tile.h"
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class Level {

    typedef vector<Tile*> column;
    typedef vector<column> matrix;

    matrix tileArray; //Double vector to hold all of the tiles in the level
    Tile *start; //The start tile within the level
    Tile *end; //The end tile of the level
    Level *next; //The level that comes next in the game
    int width;
    int height;

public:

    Level(int width, int height);

    void insertTile(int tileType, int orientation, int x, int y);

    Tile* getEnd();

    void setEnd(Tile* theEnd);

    Tile* getStart();

    void setStart(Tile* theStart);

    Level* getNextLevel();

    void setNext(Level* nextLevel);

    Tile* getTile(int xDest, int yDest);

    void setTile(int xDest, int yDest, Tile* inTile);
    
    int getWidth();
    
    int getHeight();

};

#endif	/* LEVEL_H */

