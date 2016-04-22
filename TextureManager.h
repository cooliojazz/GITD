#ifndef TEXTUREMANAGER_H
#define	TEXTUREMANAGER_H

#include <string>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "structs.h"
#include "utils.h"

using namespace std;

class TextureManager {
    SDL_Texture* tiletexs[7][4];
    SDL_Texture* playtexs[4][4];
    
public:
    void loadTileTexture(SDL_Renderer* renderer, string file, tileT type);
    
    SDL_Texture* getTileTexture(tileT type, directionT rot);
    
    void loadPlayTexture(SDL_Renderer* renderer, string file);
    
    SDL_Texture* getPlayTexture(directionT rot, int anim);

};
#endif	/* TEXTUREMANAGER_H */
