/* 
 * File:   Game.h
 * Author: Ricky
 *
 * Created on March 11, 2016, 2:56 AM
 */

#ifndef GAME_H
#define	GAME_H

#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Level.h"
#include "Player.h"

using namespace std;

class Game {
    int levelCount;
    Player* player;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    //Sound North 
    //Sound East 
    //Sound South 
    //Sound West 
    
public:
    
    void init(int width, int height);
    
    void render();

    void assignSounds();

    void handleEvent(SDL_Event e);
};


#endif	/* GAME_H */

