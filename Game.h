#ifndef GAME_H
#define	GAME_H

#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Level.h"
#include "Player.h"
#include "TextureManager.h"
#include "SDL_ttf.h"
#include "utils.h"

using namespace std;

int renderloop(void* v);
int physloop(void* v);
int soundtrkloop(void* v);

class Game {
	int levelCount;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* mask = NULL;
	TTF_Font* font = NULL;
	TextureManager texman;
	bool done = false;
	//Sound North 
	//Sound East 
	//Sound South 
	//Sound West 

public:

	Player* player;
        bool musicpause = false;

	void init(int width, int height);

	void render();

	void assignSounds();

	void handleEvents();

	SDL_Texture * loadFromRenderedText(string textureText, SDL_Color textColor);

	bool isRunning();
};

#endif	/* GAME_H */

