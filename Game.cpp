#include "Game.h"
// I work on dis now.
void Game::init(int width, int height) {
    cout << "Initializing game..." << endl;
    
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    
    //Init SDL
    cout << "Initializing SDL..." << endl;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw new runtime_error("Cannot Initialize SDL.");
    }
    window = SDL_CreateWindow("GITD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    cout << "SDL Initialized." << endl;
    
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
        if (firstChar == 'A')  {
            //First Animation is walk North
            //Second - East
            //Third - South
            //Fourth - West
        } else if (firstChar == 'T') {
            string path;
            int type;
            inputLine >> path >> type;
            cout << "Adding texture from " << path << " as " << type << endl;
            texman.loadTexture(renderer, path, (tileT)type);
        } else if (firstChar == 'S') {
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
        } else if (firstChar == '{') {
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
    cout << "Starting game threads" << endl;
    SDL_CreateThread((SDL_ThreadFunction)&renderloop, "Render", (void*)this);
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

void Game::render() {
    Level* l = player->getLevel();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
//    SDL_Point center = {47, 47};
    for (int x = 0; x < l->getWidth(); x++) {
        for (int y = 0; y < l->getHeight(); y++) {
            Tile* t = l->getTile(x, y);
            SDL_RenderCopy(renderer, texman.getTexture(t->getType(), t->getRot()), NULL, createRect(x * 96, y * 96, 96, 96));
//            SDL_RenderCopyEx(renderer, texman.getTexture(t->getType()), NULL, createRect(x * 95, y * 95, 95, 95), t->getRot() * 90, &center, SDL_FLIP_NONE);
        }
    }
    player->render(renderer);
    SDL_RenderPresent(renderer);
}


void Game::handleEvents() {
    SDL_Event e;
    SDL_PollEvent(&e);
    
    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    if (e.type == SDL_QUIT) {
        done = true;
    }
    
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

bool Game::isRunning() {
    return !done;
}
