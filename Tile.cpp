#include "Tile.h"

Tile::Tile(int type, int rotation, int x, int y) {
    xLoc = x;
    yLoc = y;
    tileType = (tileT)type;
    orientation = (directionT)rotation;
}

bool Tile::moveValid(directionT direction) {
    switch ((int)tileType) {
        case 1 || 0:
            if (direction == orientation) return true;
        case 2:
            if ((direction % 2) == (orientation % 2))  return true;
        case 3:
            if(direction == orientation || (direction - 1) == orientation || (orientation == 3 && direction == 0)) return true;
        case 4:
            if ((direction % 2) == (orientation % 2)) {
                if (direction != orientation) return false;
            }
            return true;
        case 5:
            return true;
    }
    return false;
}

bool Tile::moveValid(SDL_Rect* p) {
    vector<SDL_Rect*> rects;
    rects.push_back(createRect(0, 0, 29, 29));
    rects.push_back(createRect(67, 0, 29, 29));
    rects.push_back(createRect(67, 67, 29, 29));
    rects.push_back(createRect(0, 67, 29, 29));
    vector<int> erects;
    switch ((int)getType()) {
        case STRAIGHT:
            erects.push_back(1);
            erects.push_back(3);
            break;
        case START:
        case EXIT:
        case DEADEND:
            erects.push_back(1);
        case BEND:
            erects.push_back(2);
        case TJUNCT:
            erects.push_back(3);
            break;
    }
    erects = erects + (int)getRot();
    erects = erects % 4;
    for (int i : erects) {
        cout << i << endl;
        switch (i) {
            case 0:
                rects.push_back(createRect(67, 29, 29, 38));
                break;
            case 1:
                rects.push_back(createRect(29, 67, 38, 29));
                break;
            case 2:
                rects.push_back(createRect(0, 29, 29, 38));
                break;
            case 3:
                rects.push_back(createRect(29, 0, 38, 29));
                break;
        }
    }
    cout << endl;
    for (SDL_Rect* r : rects) if (intersects(r, p)) return false;
    return true;
}

int Tile::getXLoc() {
    return xLoc;
}

int Tile::getYLoc() {
    return yLoc;
}

tileT Tile::getType() {
    return tileType;
}

directionT Tile::getRot() {
    return orientation;
}