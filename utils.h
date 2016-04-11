#ifndef UTILS_H
#define	UTILS_H

#include "SDL.h"

SDL_Rect* createRect(int x, int y, int w, int h);

bool contains(SDL_Rect* r, int x, int y);

bool intersects(SDL_Rect* r1, SDL_Rect* r2);

#endif	/* UTILS_H */