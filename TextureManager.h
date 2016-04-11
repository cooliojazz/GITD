#ifndef TEXTUREMANAGER_H
#define	TEXTUREMANAGER_H

#include <string>
#include <iostream>
#include "SDL.h"
#include "structs.h"

using namespace std;

class TextureManager {
    SDL_Texture* texs[7][4];
    
public:
    void loadTexture(SDL_Renderer* renderer, string file, tileT type);
    
    SDL_Texture* getTexture(tileT type, directionT rot);

};
#endif	/* TEXTUREMANAGER_H */
