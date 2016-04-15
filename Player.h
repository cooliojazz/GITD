#ifndef PLAYER_H
#define	PLAYER_H

#include <math.h>
#include <algorithm>
#include "SDL_mixer.h"
#include "SDL.h"
#include "Tile.h"
#include "Level.h"
#include "utils.h"

class Player {
    Tile *currentTile; //The tile the player is currently on
    Level *currentLevel; //The level the player is currently on
    directionT facing;
    bool laser;
    double vx = 0;
    double vy = 0;
    double x = 32;
    double y = 32;
    int lx = 32;
    int ly = 32;
    
    Mix_Chunk *North;
    Mix_Chunk *West;
    Mix_Chunk *South;
    Mix_Chunk *East;

public:
    
    void physics();

    void move(directionT direction);

    void useBell();

    void laserOn();

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
    
    Tile* getTile();

    int getX();

    int getY();
    
    int getLX();

    int getLY();
    
    bool getLaser();
};

#endif	/* PLAYER_H */

