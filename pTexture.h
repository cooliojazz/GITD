#ifndef PTEXTURE_H
#define	PTEXTURE_H

#include <string>
#include <iostream>
#include "SDL.h"
//#include "SDL_image.h"

using namespace std;

const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
SDL_Rect WalkDownClips[WALKING_ANIMATION_FRAMES];
SDL_Rect WalkUpClips[WALKING_ANIMATION_FRAMES];
SDL_Rect WalkRightClips[WALKING_ANIMATION_FRAMES];
SDL_Rect WalkLeftClips[WALKING_ANIMATION_FRAMES];
SDL_Rect DownIdle[1];
SDL_Rect UpIdle[1];
SDL_Renderer* gRenderer = NULL;

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

