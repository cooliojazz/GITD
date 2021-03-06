#include "Player.h"
#include "Game.h"

void Player::physics(double ticks) {
    if (currentLevel != NULL) {
        double tx = x + vx * ticks;
        vx /= 1.1;
        if (currentLevel->getTile(((int)tx) / 96, getY() / 96)->moveValid(createRect(((int)tx) % 96, getY() % 96, 32, 32))) {
            x = tx;
            currentTile = currentLevel->getTile(getX() / 96, getY() / 96);
            if (currentTile->getType() == EXIT && currentTile->getXLoc() * 96 + 32 - x < 5 && currentTile->getYLoc() * 96 + 32 - y < 5) {
                cout << "Level finished!" << endl;
                currentLevel = currentLevel->getNextLevel();
                if (currentLevel != NULL) {
                    currentTile = currentLevel->getStart();
                    x = currentTile->getXLoc() * 96 + 32;
                    y = currentTile->getYLoc() * 96 + 32;
                    assignSounds();
                    battery = 100;
                } else {
                    return;
                }

            }
        } else {
            vx = 0;
        }
        double ty = y + vy * ticks;
        vy /= 1.1;
        if (currentLevel->getTile(getX() / 96, ((int)ty) / 96)->moveValid(createRect(getX() % 96, ((int)ty) % 96, 32, 32))) {
            y = ty;
            currentTile = currentLevel->getTile(getX() / 96, getY() / 96);
            if (currentTile->getType() == EXIT && currentTile->getXLoc() * 96 + 32 - x < 5 && currentTile->getYLoc() * 96 + 32 - y < 5) {
                cout << "Level finished!" << endl;
                currentLevel = currentLevel->getNextLevel();
                if (currentLevel != NULL) {
                    currentTile = currentLevel->getStart();
                    x = currentTile->getXLoc() * 96 + 32;
                    y = currentTile->getYLoc() * 96 + 32;
                    assignSounds();
                    battery = 100;
                } else {
                    return;
                }

            }
        } else {
            vy = 0;
        }

        //Do animation
        if (sqrt(vx * vx + vy * vy) > 0.1) {
            anim += 0.1 * ticks;
            if (anim >= 4) anim = 1;
        } else {
            anim = 0;
        }

        //Recompute laser
        if (laser) {
            battery -= .05 * ticks;
            if (battery <= 0) {
                battery = 0;
                laserOff();
            }
        }
        int tlx;
        int tly;
        switch (facing) {
            case NORTH:
                tlx = getX() + 26;
                tly = getY() + 14;
                break;
            case EAST:
                tlx = getX() + 10;
                tly = getY() + 24;
                break;
            case SOUTH:
                tlx = getX() + 26;
                tly = getY() + 21;
                break;
            case WEST:
                tlx = getX() + 20;
                tly = getY() + 24;
                break;
        }
        while (tlx >= 0 && tlx <= 96 * getLevel()->getWidth() && tly >= 0 && tly <= 96 * getLevel()->getHeight() && currentLevel->getTile(tlx / 96, tly / 96)->moveValid(createRect(tlx % 96, tly % 96, 1, 1))) {
            switch (facing) {
                case NORTH:
                    tly--;
                    break;
                case EAST:
                    tlx++;
                    break;
                case SOUTH:
                    tly++;
                    break;
                case WEST:
                    tlx--;
                    break;
            }
        }
        lx = tlx;
        ly = tly;
    }
}

void Player::move(directionT direction) {
    facing = direction;
    switch (direction) {
        case NORTH:
            vy -= 0.01;
            if (vy < -1) vy = -1;
            break;
        case EAST:
            vx += 0.01;
            if (vx > 1) vx = 1;
            break;
        case SOUTH:
            vy += 0.01;
            if (vy > 1) vy = 1;
            break;
        case WEST:
            vx -= 0.01;
            if (vx < -1) vx = -1;
            break;
    }
}

void Player::useBell() {
    double xDiff = abs(x / 96.0 - currentLevel->getEnd()->getXLoc() - 48 / 96.0); //The X-difference between the players current tile and the level's end tile
    double yDiff = abs(y / 96.0 - currentLevel->getEnd()->getYLoc() - 48 / 96.0); //The Y-difference between the players current tile and the level's end tile

    Mix_Volume(1, (int)((currentLevel->getWidth() - xDiff) / currentLevel->getWidth() * 100.0));
    if (xDiff > 0)
        Mix_PlayChannel(1, West, 0);
    else if (xDiff < 0)
        Mix_PlayChannel(1, East, 0);
    
    Mix_Volume(2, (int)((currentLevel->getHeight() - yDiff) / currentLevel->getHeight() * 100.0));
    if (yDiff > 0)
        Mix_PlayChannel(2, North, 0);
    else if (yDiff < 0)
        Mix_PlayChannel(2, South, 0);
}

void Player::laserOn() {
    laser = true;
}

void Player::laserOff() {
    laser = false;
}

Level* Player::getLevel() {
    return currentLevel;
}

void Player::setLevel(Level *inLevel) {
    currentLevel = inLevel;
}

void Player::setTile(Tile *inTile) {
    x = 32 + inTile->getXLoc() * 96;
    y = 32 + inTile->getYLoc() * 96;
    currentTile = inTile;
}

void Player::setNorth(Mix_Chunk *newSound) {
    North = newSound;
}

void Player::setEast(Mix_Chunk *newSound) {
    East = newSound;
}

void Player::setSouth(Mix_Chunk *newSound) {
    South = newSound;
}

void Player::setWest(Mix_Chunk *newSound) {
    West = newSound;
}

void Player::assignSounds() {
    int start = rand() % 4;
    Mix_Chunk *temp1;
    Mix_Chunk *temp2;

    switch (start) {
            //case 0 is default
        case 1:
            //sound temp = North
            temp1 = North;
            //sound north = east
            North = East;
            //sound east = south
            East = South;
            //sound south = west
            South = West;
            //sound west = temp
            West = temp1;
            true;
        case 2:
            //sound temp1 = North
            temp1 = North;
            //sound temp2 = east
            temp2 = East;
            //sound north = south
            North = South;
            //sound east = west
            East = West;
            //sound south = temp
            South = temp1;
            //sound west = east
            West = temp2;
            true;
        case 3:
            //sound temp = north
            temp1 = North;
            //sound north = west
            North = West;
            //sound west = south
            West = South;
            //sound south = east
            South = East;
            //sound east = temp
            East = temp1;
            true;
    }
}

void Player::render(SDL_Renderer* renderer, TextureManager texman) {
    SDL_RenderCopy(renderer, texman.getPlayTexture(getFacing(), (int)anim), NULL, createRect(getX(), getY(), 32, 32));
}

Tile* Player::getTile() {
    return currentTile;
}

int Player::getX() {
    return (int)x;
}

int Player::getY() {
    return (int)y;
}

int Player::getLX() {
    return lx;
}

int Player::getLY() {
    return ly;
}

bool Player::getLaser() {
    return laser;
}

directionT Player::getFacing() {
    return facing;
}
