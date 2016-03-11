/* 
 * File:   Player.h
 * Author: Ricky
 *
 * Created on March 11, 2016, 2:51 AM
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include "Tile.h"
#include "Level.h"

class Player {
    Tile *currentTile; //The tile the player is currently on
    Level *currentLevel; //The level the player is currently on

public:

    void move(directionT direction);

    void useBell();

    void laserOn(directionT direction);

    void laserOff();

    void setLevel(Level *inLevel);

    void setTile(Tile *inTile);

};

#endif	/* PLAYER_H */

