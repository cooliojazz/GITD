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
    if (font == NULL) {
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
        } else if (firstChar == 'T') {
            string path;
            int type;
            inputLine >> path >> type;
            cout << "Adding texture from " << path << " as " << type << endl;
            texman.loadTileTexture(renderer, path, (tileT)type);
        } else if (firstChar == 'P') {
            string path;
            inputLine >> path;
            cout << "Adding player texture from " << path << endl;
            texman.loadPlayTexture(renderer, path);
        } else if (firstChar == 'S') {
            char files[4][256];
            inputLine >> files[0] >> files[1] >> files[2] >> files[3];
            player->setNorth(Mix_LoadWAV(files[0]));
            //Second - East
            player->setEast(Mix_LoadWAV(files[1]));
            //Third - South
            player->setSouth(Mix_LoadWAV(files[2]));
            //Fourth - West
            player->setWest(Mix_LoadWAV(files[3]));
            
        } else if (firstChar == 'M') {
            char file[256];
            inputLine >> file;
            gMusic = Mix_LoadMUS(file);
            if (gMusic == NULL) {
                cout << "Failed to load beat music! SDL_mixer Error:" << Mix_GetError() << endl;
            }
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
                if (type == EXIT) {
                    currLevel->setEnd(currLevel->getTile(posX, posY));
                }
                if (type == START) {
                    currLevel->setStart(currLevel->getTile(posX, posY));
                }
                posX++;
            }
            cout << "Finished level line " << posY << endl;
            posY++;
        }
    }
    player->setTile(player->getLevel()->getStart());
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
    SDL_CreateThread((SDL_ThreadFunction)&renderloop, "Render", (void*) this);
    SDL_CreateThread((SDL_ThreadFunction)&physloop, "Physics", (void*) this);
    SDL_CreateThread((SDL_ThreadFunction)&soundtrkloop, "Soundtrack", (void*) this);
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
    double lticks = SDL_GetTicks() / 10.0;
    while (g->isRunning()) {
        double curticks = SDL_GetTicks() / 10.0;
        g->player->physics(curticks - lticks);
        lticks = curticks;
        SDL_Delay(10);
    }
    return 0;
}

int soundtrkloop(void* v) {
    Game* g = ((Game*)v);
    
    Mix_VolumeMusic(40);
    Mix_PlayMusic(g->gMusic, -1);
    while (g->isRunning()) {
        if (g->musicpause) {
            Mix_PauseMusic();
            while (g->musicpause) {
                g->musicpause = Mix_Playing(-1) > 0;
                SDL_Delay(1);
            }
            Mix_ResumeMusic();
        }
        SDL_Delay(1);
    }
    return 0;

}

SDL_Texture * Game::loadFromRenderedText(string textureText, SDL_Color textColor) {
    //Render text surface
    SDL_Texture* mtexture = NULL;
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    } else {
        //Create texture from surface pixels
        mtexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (mtexture == NULL) {
            cout << "HEY" << endl;
        }
        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }
    //Return success
    return mtexture;
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    Level* l = player->getLevel();
    if (l != NULL) {
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
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 50 + (int)(player->battery * 2));
            switch (player->getFacing()) {
                case NORTH:
                    SDL_RenderDrawLine(renderer, player->getX() + 26, player->getY() + 14, player->getLX(), player->getLY());
                    break;
                case EAST:
                    SDL_RenderDrawLine(renderer, player->getX() + 10, player->getY() + 24, player->getLX(), player->getLY());
                    break;
                case SOUTH:
                    SDL_RenderDrawLine(renderer, player->getX() + 26, player->getY() + 21, player->getLX(), player->getLY());
                    break;
                case WEST:
                    SDL_RenderDrawLine(renderer, player->getX() + 20, player->getY() + 24, player->getLX(), player->getLY());
                    break;
            }
        }

        SDL_Color textColor = {255, 255, 255};
        SDL_Texture *text;
        string batt = to_string((int) player->battery);
        text = loadFromRenderedText("Battery: " + batt + "%", textColor);
        SDL_RenderCopy(renderer, text, NULL, createRect(0, 0, 150, 20));
    } else if (l == NULL) {
        SDL_Color textColor = {255, 255, 255};
        SDL_Texture *text;
        text = loadFromRenderedText("You Survived The Maze.... This Time.", textColor);
        SDL_RenderCopy(renderer, text, NULL, createRect(75, 200, 500, 50));
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
    if (player->getLevel() != NULL) {
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
        if (keyState[SDL_SCANCODE_LSHIFT] && player->battery > 0) {
            player->laserOn();
        } else {
            player->laserOff();
        }
        if (keyState[SDL_SCANCODE_Q] && !musicpause) {
            musicpause = true;
            player->useBell();
        }
    }

}

bool Game::isRunning() {
    return !done;
}
