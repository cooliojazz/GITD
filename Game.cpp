#include "Game.h"

SDL_Texture* tex;

void Game::init(int width, int height) {
    cout << "Initializing game..." << endl;
    Level* currLevel = NULL;
    int posX = 0, posY = 0, levelX = 0, levelY = 0;
    string line;
    char firstChar;

	char filename[64];

	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	

    //read file stuff...
    ifstream gameFile("GITDTextDoc.txt");
    cout << "Reading game file..." << endl;
    while (getline(gameFile, line)) {
        istringstream inputLine(line);
        inputLine >> firstChar;

        //animation stuff
        if (firstChar == 'A')  {
            //First Animation is walk North
            //Second - East
            //Third - South
            //Fourth - West
        } else if (firstChar == 'S') {
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
        } else if (firstChar == 'L') {//create new level when level header (length, height) is read
            //LevelX = first read, levelY = second read
            inputLine >> levelX >> levelY;
            cout << "Adding new level of size " << levelX << "x" << levelY << endl;
            Level* newLevel = new Level(levelX, levelY);

            if (currLevel != NULL) {
                currLevel->setNext(newLevel);
            } else {
                player->setLevel(newLevel);
            }

            currLevel = newLevel;
            posX = 0;
            posY = 0;
        } else if (firstChar == '(') {
            cout << "Reading level line " << posY << endl;
//            int count = 0;
            posX = 0;
            while (posX < levelX) {
//                if (count % 2 == 1) {
                    int type;
                    int rot;
                    inputLine >> type >> rot;
                    cout << "Tile " << posX << " is " << type << ", " << rot << endl;
                    currLevel->setTile(posX, posY, new Tile(type, rot, posX, posY));
//                    count++;
                    posX++;
//                } else {
//                    inputLine.get();
//                    count++;
//                }
            }
            cout << "Finished level line " << posY << endl;
            posY++;
        }

    }
    
    //Init SDL
    cout << "Initializing SDL..." << endl;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw new runtime_error("Cannot Initialize SDL.");
    }
    window = SDL_CreateWindow("GITD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    cout << "Creating Texture..." << endl;
    SDL_Surface* ttex = SDL_LoadBMP("Start_tile.bmp");
    tex = SDL_CreateTextureFromSurface(renderer, ttex);
    SDL_FreeSurface(ttex);
    cout << "Done!" << endl;
}


SDL_Texture* getTileTex(int type) {
    return tex;
}

SDL_Rect* createRect(int x, int y, int w, int h) {
    SDL_Rect* rect = new SDL_Rect();
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
    return rect;
}

void Game::render() {
    cout << "Render loop!" << endl;
    Level* l = player->getLevel();
    SDL_RenderClear(renderer);
    for (int x = 0; x < l->getWidth(); x++) {
        for (int y = 0; y < l->getHeight(); y++) {
            Tile* t = l->getTile(x, y);
            SDL_RenderCopy(renderer, getTileTex(t->getType()), NULL, createRect(x * 32, y * 32, 32, 32));
        }
    }
    SDL_RenderPresent(renderer);
}



void Game::handleEvent(SDL_Event e) {
    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    if (e.type == SDL_KEYDOWN) {
        if ((e.key.keysym.sym == SDLK_w) || (e.key.keysym.sym == SDLK_UP)) {
            if (keyState[SDL_SCANCODE_Q] || keyState[SDL_SCANCODE_Z])
                player->laserOn(NORTH);
            else
                player->move(NORTH);
        } else if ((e.key.keysym.sym == SDLK_d) || (e.key.keysym.sym == SDLK_RIGHT)) {
            if (keyState[SDL_SCANCODE_Q] || keyState[SDL_SCANCODE_Z])
                player->laserOn(EAST);
            else
                player->move(EAST);
        } else if ((e.key.keysym.sym == SDLK_s) || (e.key.keysym.sym == SDLK_DOWN)) {
            if (keyState[SDL_SCANCODE_Q] || keyState[SDL_SCANCODE_Z])
                player->laserOn(SOUTH);
            else
                player->move(SOUTH);
        } else if ((e.key.keysym.sym == SDLK_a) || (e.key.keysym.sym == SDLK_LEFT)) {
            if (keyState[SDL_SCANCODE_Q] || keyState[SDL_SCANCODE_Z])
                player->laserOn(WEST);
            else
                player->move(WEST);
        } else if ((e.key.keysym.sym == SDLK_e) || (e.key.keysym.sym == SDLK_x)) {
            player->useBell();
        } else if ((e.key.keysym.sym == SDLK_q) || (e.key.keysym.sym == SDLK_z)) {
            player->laserOff();
        }
    }
}
