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
#include "SDL_image.h"

class Player {
    Tile *currentTile; //The tile the player is currently on
    Level *currentLevel; //The level the player is currently on
    bool laser;

public:

    void move(directionT direction);

    void useBell();

    void laserOn(directionT direction);

    void laserOff();

    Level* getLevel();
    
    void setLevel(Level *inLevel);

    void setTile(Tile *inTile);
	void render();
	bool loadMedia();

};
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect PlayerSpriteClips[WALKING_ANIMATION_FRAMES];
#endif	/* PLAYER_H */

