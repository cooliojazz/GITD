/* 
 * File:   Game.h
 * Author: Ricky
 *
 * Created on March 11, 2016, 2:56 AM
 */

#ifndef GAME_H
#define	GAME_H

#include "SDL.h"
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
    SDL_Window* win = NULL;
    SDL_Renderer* renderer = NULL;
    //Sound North 
    //Sound East 
    //Sound South 
    //Sound West 

    void init();

    void assignSounds();

    void handleEvent(SDL_Event e);
};


#endif	/* GAME_H */

