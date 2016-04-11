#include "TextureManager.h"

void TextureManager::loadTexture(SDL_Renderer* renderer, string file, tileT type) {
    cout << "Loading texture files for " << file << "..." << endl;
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
			texs[type][i - 1] = SDL_CreateTextureFromSurface(renderer, ttex);
			SDL_FreeSurface(ttex);
		}
    }
}

SDL_Texture* TextureManager::getTexture(tileT type, directionT rot) {
    return texs[type][rot];
}