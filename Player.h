#ifndef PLAYER_H
#define	PLAYER_H

#include <math.h>
#include "SDL_mixer.h"
#include "SDL.h"
#include "Tile.h"
#include "Level.h"
#include "utils.h"

class Player {
    Tile *currentTile; //The tile the player is currently on
    Level *currentLevel; //The level the player is currently on
    bool laser;
    int x = 32;
    int y = 32;
    
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

    void render(SDL_Renderer* renderer);
};

#endif	/* PLAYER_H */

