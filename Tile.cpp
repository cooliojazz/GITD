#include "Tile.h"

Tile::Tile(int type, int rotation, int x, int y) {
    xLoc = x;
    yLoc = y;
    tileType = type;
    orientation = rotation;
}

bool Tile::moveValid (directionT direction) {
    switch (tileType) {
        case 1 || 0:
            if (direction == orientation) return true;
        case 2:
            if ((direction % 2) == (orientation % 2))  return true;
        case 3:
            if(direction == orientation || (direction - 1) == orientation || (orientation == 3 && direction == 0)) return true;
        case 4:
            if ((direction % 2) == (orientation % 2)) {
                    if (direction != orientation)
                            return false;
            }
            return true;
        case 5:
            return true;
    }
    return false;
}

int Tile::getXLoc() {
    return xLoc;
}

int Tile::getYLoc() {
    return yLoc;
}

int Tile::getType() {
    return tileType;
}