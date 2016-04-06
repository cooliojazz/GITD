#include "Level.h"

Level::Level() {
    tileArray;
    start = NULL;
    end = NULL;
    next = NULL;
}

void Level::insertTile(int tileType, int orientation, int x, int y) {
    Tile* temp = new Tile(tileType, orientation, x, y);
    tileArray[x][y] = temp;
}

Tile* Level::getEnd() {
    return end;
}

void Level::setEnd(Tile* theEnd) {
    end = theEnd;
}

Tile* Level::getStart() {
    return start;
}

void Level::setStart(Tile* theStart) {
    start = theStart;
}

Level* Level::getNextLevel() {
    return next;
}

void Level::setNext(Level* nextLevel) {
    next = nextLevel;
}

Tile* Level::getTile(int xDest, int yDest) {
    return tileArray[xDest][yDest];
}

void Level::setTile(int xDest, int yDest, Tile* inTile) {
    tileArray[xDest][yDest] = inTile;
}

