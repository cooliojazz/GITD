#include "Player.h"

void Player::move(directionT direction) {
    if (currentTile->moveValid(direction)) {
        switch (direction) {				//Note: Doesn't contain any code for playing movement animation
            case NORTH:
                currentTile = currentLevel->getTile(currentTile->getXLoc(), currentTile->getYLoc() - 1);
            case EAST:
                currentTile = currentLevel->getTile(currentTile->getXLoc() + 1, currentTile->getYLoc());
            case SOUTH:
                currentTile = currentLevel->getTile(currentTile->getXLoc(), currentTile->getYLoc() + 1);
            case WEST:
                currentTile = currentLevel->getTile(currentTile->getXLoc() - 1, currentTile->getYLoc());
        }

        if (currentLevel->getEnd() == currentTile) {
            currentLevel = currentLevel->getNextLevel();
            currentTile = currentLevel->getStart();
        }
    }
}

void Player::useBell() {
    int xDiff = currentTile->getXLoc() - currentLevel->getEnd()->getXLoc(); //The X-difference between the players current tile and the level's end tile
    int yDiff = currentTile->getYLoc() - currentLevel->getEnd()->getYLoc(); //The Y-difference between the players current tile and the level's end tile

    int distance = sqrt(xDiff ^ 2 + yDiff ^ 2);  //The straight distance between the player's tile and the end

    if (xDiff > 0)
        //Play sound for West (send in distance as param for volume/loudness)
        true;
    else if (xDiff < 0)
        //Play sound for East (send in distance as param for volume/loudness)
        true;

    if (yDiff > 0)
        //Play sound for North (send in distance as param for volume/loudness)
        true;
    else if (yDiff < 0)
        //Play sound for South (send in distance as param for volume/loudness)
        true;
}

void Player::laserOn(directionT direction) {
    //Use SDL_SetRenderDrawColor(renderer, 0, 255, 0, ?) to get a green color
    //Use SDL_RenderDrawLine(renderer, playerX, playerY, destX, destY) to draw a line
    //Need a direction in the input params
    //Need to test where there is a wall (? tiles in desired direction, if not, to edge of screen
    laser = true;
}

void Player::laserOff() {
    //?????????????????????
    laser = false;
}

Level* Player::getLevel() {
    return currentLevel;
}

void Player::setLevel(Level *inLevel) {
    currentLevel = inLevel;
}

void Player::setTile(Tile *inTile) {
    currentTile = inTile;
}