#include "Level.h"

Level::Level(int width, int height) : tileArray(width, vector<Tile*>(height)) {
    tileArray;
    start = NULL;
    end = NULL;
    next = NULL;
    this->width = width;
    this->height = height;
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
    cout << "Setting tile at " << xDest << ", " << yDest << endl;
//    try {
        tileArray[xDest][yDest] = inTile;
//    } catch (exception &e) {
//        cout << "Exception! " << e.what() << endl;
//    }
}

int Level::getWidth() {
    return width;
}

int Level::getHeight() {
    return height;
}
