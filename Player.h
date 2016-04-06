/* 
 * File:   Player.h
 * Author: Ricky
 *
 * Created on March 11, 2016, 2:51 AM
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include "Tile.h"
#include <math.h>
#include "Level.h"
#include "SDL_mixer.h"

class Player {
    Tile *currentTile; //The tile the player is currently on
    Level *currentLevel; //The level the player is currently on
    bool laser;

	Mix_Chunk *North;
	Mix_Chunk *West;
	Mix_Chunk *South;
	Mix_Chunk *East;

public:

    void move(directionT direction);

    void useBell();

    void laserOn(directionT direction);

    void laserOff();

    Level* getLevel();
    
    void setLevel(Level *inLevel);

    void setTile(Tile *inTile);

	void assignSounds();

	void setNorth(Mix_Chunk *newSound);

	void setEast(Mix_Chunk *newSound);

	void setSouth(Mix_Chunk *newSound);

	void setWest(Mix_Chunk *newSound);


};

#endif	/* PLAYER_H */

