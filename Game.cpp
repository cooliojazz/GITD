#include "Game.h"

void Game::init(int width, int height) {
    Level* currLevel = NULL;
    int posX = 0, posY = 0, levelX = 0, levelY = 0;
    string line;
    char firstChar;

    //read file stuff...
    ifstream gameFile("GITDTextDoc.txt");
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
            //Second - East
            //Third - South
            //Fourth - West
        } else if (firstChar == 'L') {//create new level when level header (length, height) is read
            //LevelX = first read, levelY = second read
            inputLine >> levelX >> levelY;
            Level *newLevel = new Level();

            if (currLevel != NULL) {
                currLevel->setNext(newLevel);
            } else {
                player->setLevel(newLevel);
            }

            currLevel = newLevel;
            posX = 0;
            posY = 0;
        } else if (firstChar == '(') {
            int count = 0;
            while (posX < levelX) {
                if (count % 2 == 1) {
                    Tile* temp = new Tile(inputLine.get(), inputLine.get(), posX, posY);
                    currLevel->setTile(posX, posY, temp);
                    count++;
                    posX++;
                } else {
                    inputLine.get();
                    count++;
                }
            }

            posX = 0;
            posY++;
        }

    }
    
    //Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw new runtime_error("Cannot Initialize SDL.");
    }
    window = SDL_CreateWindow("GITD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture getTileTex(int type) {
    return NULL;
}

void Game::render() {
    Level* l = player->getLevel();
    for (int x = 0; x < ?; x++) {
        for (int y = 0; y < ?; y++) {
            Tile* t = l->getTile(x, y);
            SDL_RenderCopy(renderer, getTileTex(t->getType()), new SDL_Rect(?), new SDL_Rect(?));
        }
    }
}

void Game::assignSounds() {
    int start = rand() % 4;

    switch (start) {
            //case 0 is default
        case 1:				//Maybe?
            //sound temp = North
            //sound north = east
            //sound east = south
            //sound south = west
            //sound west = temp
            true;
        case 2:				//Maybe?
            //sound temp1 = North
            //sound temp2 = east
            //sound north = south
            //sound east = west
            //sound south = temp
            //sound west = east
            true;
        case 3:				//Maybe?
            //sound temp = north
            //sound north = west
            //sound west = south
            //sound south = east
            //sound east = temp
            true;
    }
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
