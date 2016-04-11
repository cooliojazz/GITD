#ifndef GAME_H
#define	GAME_H

#include "SDL.h"
//#include "SDL_image.h"
#include "SDL_mixer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Level.h"
#include "Player.h"
#include "TextureManager.h"
#include "utils.h"

using namespace std;

int renderloop(void* g);

class Game {
    int levelCount;
    Player* player;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    TextureManager texman;
    bool done = false;
    //Sound North 
    //Sound East 
    //Sound South 
    //Sound West 
    
public:
    
    void init(int width, int height);
    
    void render();

    void assignSounds();

    void handleEvents();
    
    bool isRunning();
};

#endif	/* GAME_H */

