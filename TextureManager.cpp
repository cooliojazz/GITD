#include "TextureManager.h"

void TextureManager::loadTileTexture(SDL_Renderer* renderer, string file, tileT type) {
    cout << "Loading tile texture files for " << file << "..." << endl;
    for (int i = 1; i < 5; i++) {
        string temp = file;
        temp += to_string(i);
        temp += ".bmp";
        const char* ffile = temp.c_str();
        cout << "Loading file " << ffile << "..." << endl;
        SDL_Surface* ttex = SDL_LoadBMP(ffile);
        if (ttex == NULL) {
            cout << "Error reading texture!" << endl;
        } else {
            tiletexs[type][i - 1] = SDL_CreateTextureFromSurface(renderer, ttex);
            SDL_FreeSurface(ttex);
        }
    }
}

SDL_Texture* TextureManager::getTileTexture(tileT type, directionT rot) {
    return tiletexs[type][rot];
}

void TextureManager::loadPlayTexture(SDL_Renderer* renderer, string file) {
//    SDL_Texture* newTexture = NULL;
//    SDL_Surface* loadedSurface = IMG_Load(file.c_str());
//    if (loadedSurface == NULL) {
//        cout << "Unable to load image %s! SDL_image Error: %s\n " << endl << path.c_str(), IMG_GetError();
//    } else {
//        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
//        if (newTexture == NULL) {
//            cout << "Unable to create texture from %s!SDL Error : %s\n" << endl << path.c_str(), SDL_GetError();
//        } else {
//            mWidth = loadedSurface->w;
//            mHeight = loadedSurface->h;
//        }
//
//        SDL_FreeSurface(loadedSurface);
//    }
//    mTexture = newTexture;
//    return mTexture != NULL;
    cout << "Loading player texture file for " << file << "..." << endl;
    SDL_Surface* stex = IMG_Load(file.c_str());
    if (stex == NULL) {
        cout << "Error reading texture!" << endl;
    } else {
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, stex);
        SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
        for (int rot = 0; rot < 4; rot++) {
            for (int i = 0; i < 4; i++) {
                playtexs[rot][i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 32, 32);
                SDL_SetRenderTarget(renderer, playtexs[rot][i]);
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, tex, createRect((rot * 4 + i) * 32, 0, 32, 32), createRect(0, 0, 32, 32));
                SDL_SetTextureBlendMode(playtexs[rot][i], SDL_BLENDMODE_BLEND);
                SDL_SetRenderTarget(renderer, NULL);
//                playtexs[type][rot - 1] = SDL_CreateTextureFromSurface(renderer, ttex);
            }
        }
        SDL_FreeSurface(stex);
    }
}

SDL_Texture* TextureManager::getPlayTexture(directionT rot, int anim) {
    return playtexs[rot][anim];
}