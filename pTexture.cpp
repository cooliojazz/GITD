#include "pTexture.h"

const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
SDL_Rect WalkDownClips[WALKING_ANIMATION_FRAMES];
SDL_Rect WalkUpClips[WALKING_ANIMATION_FRAMES];
SDL_Rect WalkRightClips[WALKING_ANIMATION_FRAMES];
SDL_Rect WalkLeftClips[WALKING_ANIMATION_FRAMES];
SDL_Rect DownIdle[1];
SDL_Rect UpIdle[1];
SDL_Renderer* gRenderer = NULL;

bool pTexture::loadFile(string path) {
    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        cout << "Unable to load image %s! SDL_image Error: %s\n " << endl << path.c_str(), IMG_GetError();
    } else {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            cout << "Unable to create texture from %s!SDL Error : %s\n" << endl << path.c_str(), SDL_GetError();
        } else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

bool loadMedia(string path) {
    bool success = true;
    if (!PlayerSpriteSheet.loadFile(path.c_str())) {
        cout << "Failed to load player texture! %s\n" << endl;
        success = false;
    } else {
        int imgXValue = 0;
        int index = 0;
        int index1 = 0;
        int index2 = 0;
        int index3 = 0;
        int index4 = 0;
        int i;
        for (i = 0; i < 18; i++) {
            //int index = 0;
            if (i <= 3) {
                WalkDownClips[index1].x = imgXValue;
                WalkDownClips[index1].y = 0;
                WalkDownClips[index1].w = 32;
                WalkDownClips[index1].h = 32;
                index1++;
            }
            else if (i = 4) {
                index = 0;
                DownIdle[index].x = imgXValue;
                DownIdle[index].y = 0;
                DownIdle[index].w = 32;
                DownIdle[index].h = 32;
            }
            else if (i >= 5 && i < 9) {
                WalkUpClips[index2].x = imgXValue;
                WalkUpClips[index2].y = 0;
                WalkUpClips[index2].w = 32;
                WalkUpClips[index2].h = 32;
                index2++;
            } else if (i = 9) {
                index = 0;
                UpIdle[index].x = imgXValue;
                UpIdle[index].y = 0;
                UpIdle[index].w = 32;
                UpIdle[index].h = 32;
            } else if (i >= 10 && i < 14) {
                WalkRightClips[index3].x = imgXValue;
                WalkRightClips[index3].y = 0;
                WalkRightClips[index3].w = 32;
                WalkRightClips[index3].h = 32;
                index3++;
            } else if (i >= 14) {
                WalkLeftClips[index4].x = imgXValue;
                WalkLeftClips[index4].y = 0;
                WalkLeftClips[index4].w = 32;
                WalkLeftClips[index4].h = 32;
                index4++;
            }
            imgXValue += 32;
        }
    }
    return success;
}

pTexture::~pTexture() {
    free();
}

pTexture::pTexture() {
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

void pTexture::free() {
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

bool pTexture::loadFile(string path) {
    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        cout << "Unable to load image %s! SDL_image Error: %s\n " << endl << path.c_str(), IMG_GetError();
    } else {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            cout << "Unable to create texture from %s!SDL Error : %s\n" << endl << path.c_str(), SDL_GetError();
        } else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

void pTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);

}