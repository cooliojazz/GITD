#ifndef PTEXTURE_H
#define	PTEXTURE_H

#include <string>
#include <iostream>
#include "SDL.h"
//#include "SDL_image.h"

using namespace std;

class pTexture {  
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
public:
    pTexture();
    
    ~pTexture();
    
    void render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

    bool loadFile(string path);
    
    void free();
};

pTexture PlayerSpriteSheet;

#endif	/* PTEXTURE_H */

