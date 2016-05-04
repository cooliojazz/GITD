#include "Game.h"

void Game::init(int width, int height) {
	cout << "Initializing game..." << endl;

	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

	//Init SDL
	cout << "Initializing SDL..." << endl;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw new runtime_error("Cannot Initialize SDL.");
	}
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("GITD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	cout << "SDL Initialized." << endl;
	if (TTF_Init() < 0) cout << "Nope" << endl;
	font = TTF_OpenFont("ufonts.com_16bit.ttf", 12);
	if (font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}

	player = new Player();
	Level* currLevel = NULL;
	int posX = 0, posY = 0, levelX = 0, levelY = 0;

	//read file stuff...
	ifstream gameFile("GITDTextDoc.txt");
	cout << "Reading game file..." << endl;
	string line;
	while (getline(gameFile, line)) {
		istringstream inputLine(line);
		char firstChar;
		inputLine >> firstChar;

		//animation stuff
		if (firstChar == 'A') {
			//First Animation is walk North
			//Second - East
			//Third - South
			//Fourth - West
		}
		else if (firstChar == 'T') {
			string path;
			int type;
			inputLine >> path >> type;
			cout << "Adding texture from " << path << " as " << type << endl;
			texman.loadTileTexture(renderer, path, (tileT)type);
		}
		else if (firstChar == 'P') {
			string path;
			inputLine >> path;
			cout << "Adding player texture from " << path << endl;
			texman.loadPlayTexture(renderer, path);
		}
		else if (firstChar == 'S') {
			char filename[256];
			//First Sound is North
			inputLine.get(filename, 64, ' ');                  //Problems with excess space?
			player->setNorth(Mix_LoadWAV(filename));
			//Second - East
			inputLine.get(filename, 64, ' ');
			player->setEast(Mix_LoadWAV(filename));
			//Third - South
			inputLine.get(filename, 64, ' ');
			player->setSouth(Mix_LoadWAV(filename));
			//Fourth - West
			inputLine.get(filename, 64, ' ');
			player->setWest(Mix_LoadWAV(filename));
		}
		else if (firstChar == 'L') {//create new level when level header (length, height) is read
									//LevelX = first read, levelY = second read
			inputLine >> levelX >> levelY;
			cout << "Adding new level of size " << levelX << "x" << levelY << endl;
			Level* newLevel = new Level(levelX, levelY);

			if (currLevel != NULL) {
				currLevel->setNext(newLevel);
			}
			else {
				player->setLevel(newLevel);
			}

			currLevel = newLevel;
			posX = 0;
			posY = 0;
		}
		else if (firstChar == '{') {
			string pair;
			cout << "Reading level line " << posY << endl;
			posX = 0;
			while (posX < levelX) {
				getline(inputLine, pair, ',');
				istringstream ipair(pair);
				int type;
				int rot;
				ipair >> type >> rot;
				if (type < 0 || type > 6 || rot < 0 || rot > 3) {
					cout << "Error reading tile at " << posX << ", " << posY << "! Exiting!" << endl;
					done = true;
				}
				cout << "Tile " << posX << " is " << type << ", " << rot << endl;
				currLevel->setTile(posX, posY, new Tile(type, rot, posX, posY));
				if (type == START) {
					player->setTile(currLevel->getTile(posX, posY));
				}
				posX++;
			}
			cout << "Finished level line " << posY << endl;
			posY++;
		}
	}
	cout << "Rendering mask..." << endl;
	mask = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 96 * 7, 96 * 7);
	SDL_SetRenderTarget(renderer, mask);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	for (int x = 96 * 2; x < 96 * 5; x++) {
		for (int y = 96 * 2; y < 96 * 5; y++) {
			int c = (int)(255 * (sqrt((x - 336.0) * (x - 336.0) + (y - 336.0) * (y - 336.0)) / 65.0));
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, min(255, c));
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
	SDL_SetRenderTarget(renderer, NULL);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(mask, SDL_BLENDMODE_BLEND);
	cout << "Starting game threads" << endl;
	SDL_CreateThread((SDL_ThreadFunction)&renderloop, "Render", (void*)this);
	SDL_CreateThread((SDL_ThreadFunction)&physloop, "Physics", (void*)this);
	SDL_CreateThread((SDL_ThreadFunction)&soundtrkloop, "Soundtrack", (void*)this);
	cout << "Done!" << endl;
}

int renderloop(void* v) {
	Game* g = ((Game*)v);
	while (g->isRunning()) {
		g->render();
		SDL_Delay(10);
	}
	return 0;
}

int physloop(void* v) {
	Game* g = ((Game*)v);
	while (g->isRunning()) {
		g->player->physics();
		SDL_Delay(10);
	}
	return 0;
}

int soundtrkloop(void* v) {
	Game* g = ((Game*)v);
		//The Background music.
		Mix_Music *gMusic = NULL;
		//Load music
		gMusic = Mix_LoadMUS("cave.wav");
	
		if (gMusic == NULL)
		 {
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		}
		/*while (g->isRunning()) {
		Mix_PlayMusic(gMusic,);
		}*/
		Mix_PlayMusic(gMusic, 1000);
	return 0;
	
}

SDL_Texture * Game::loadFromRenderedText(string textureText, SDL_Color textColor) //ALL OF THIS IS NEW CODE FOR THIS FUNCTION Put this as new function in game.cpp
{

	//Render text surface
	SDL_Texture* mtexture = NULL;
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mtexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mtexture == NULL)
		{
			cout << "HEY" << endl;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mtexture;
}

void Game::render() {
	Level* l = player->getLevel();
	if (l != NULL) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		for (int x = 0; x < l->getWidth(); x++) {
			for (int y = 0; y < l->getHeight(); y++) {
				if (abs(player->getTile()->getXLoc() - x) + abs(player->getTile()->getYLoc() - y) < 3) {
					Tile* t = l->getTile(x, y);
					SDL_RenderCopy(renderer, texman.getTileTexture(t->getType(), t->getRot()), NULL, createRect(x * 96, y * 96, 96, 96));
				}
			}
		}
		player->render(renderer, texman);
		SDL_RenderCopy(renderer, mask, NULL, createRect(player->getX() - 320, player->getY() - 320, 96 * 7, 96 * 7));
		if (player->getLaser()) {
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderDrawLine(renderer, player->getX() + 16, player->getY() + 16, player->getLX(), player->getLY());
		}

		SDL_Color textColor = { 255, 255, 255 };
		SDL_Texture *text;
		string batt = to_string((int)player->battery);
		text = loadFromRenderedText("Battery: " + batt, textColor);
		SDL_RenderCopy(renderer, text, NULL, createRect(0, 0, 100, 25));
	}

	else if (l=NULL){
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderDrawLine(renderer, player->getX() + 16, player->getY() + 16, player->getLX(), player->getLY());
		SDL_Color textColor = { 255, 255, 255 };
		SDL_Texture *text;
		text = loadFromRenderedText("You Surived The Maze.... This Time.", textColor);
	}

	SDL_RenderPresent(renderer);
}

void Game::handleEvents() {
	SDL_Event e;
	SDL_PollEvent(&e);

	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	if (e.type == SDL_QUIT) {
		done = true;
	}

	if (keyState[SDL_SCANCODE_W]) {
		player->move(NORTH);
	}
	if (keyState[SDL_SCANCODE_A]) {
		player->move(WEST);
	}
	if (keyState[SDL_SCANCODE_S]) {
		player->move(SOUTH);
	}
	if (keyState[SDL_SCANCODE_D]) {
		player->move(EAST);
	}
	if (keyState[SDL_SCANCODE_TAB] && player->battery >0) {
		player->laserOn();
	}
	else {
		player->laserOff();
	}
	//    if (e.type == SDL_KEYDOWN) {
	//        if ((e.key.keysym.sym == SDLK_w) || (e.key.keysym.sym == SDLK_UP)) {
	//            if (keyState[SDL_SCANCODE_Q] || keyState[SDL_SCANCODE_Z])
	//                player->laserOn(NORTH);
	//            else
	//                player->move(NORTH);
	//        } else if ((e.key.keysym.sym == SDLK_d) || (e.key.keysym.sym == SDLK_RIGHT)) {
	//            if (keyState[SDL_SCANCODE_Q] || keyState[SDL_SCANCODE_Z])
	//                player->laserOn(EAST);
	//            else
	//                player->move(EAST);
	//        } else if ((e.key.keysym.sym == SDLK_s) || (e.key.keysym.sym == SDLK_DOWN)) {
	//            if (keyState[SDL_SCANCODE_Q] || keyState[SDL_SCANCODE_Z])
	//                player->laserOn(SOUTH);
	//            else
	//                player->move(SOUTH);
	//        } else if ((e.key.keysym.sym == SDLK_a) || (e.key.keysym.sym == SDLK_LEFT)) {
	//            if (keyState[SDL_SCANCODE_Q] || keyState[SDL_SCANCODE_Z])
	//                player->laserOn(WEST);
	//            else
	//                player->move(WEST);
	//        } else if ((e.key.keysym.sym == SDLK_e) || (e.key.keysym.sym == SDLK_x)) {
	//            player->useBell();
	//        } else if ((e.key.keysym.sym == SDLK_q) || (e.key.keysym.sym == SDLK_z)) {
	//            player->laserOff();
	//        }
	//    }

}

bool Game::isRunning() {
	return !done;
}
