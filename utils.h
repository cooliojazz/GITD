#ifndef UTILS_H
#define	UTILS_H

#include <vector>
#include "SDL.h"

using namespace std;

SDL_Rect* createRect(int x, int y, int w, int h);

bool contains(SDL_Rect* r, int x, int y);

bool intersects(SDL_Rect* r1, SDL_Rect* r2);

vector<int> operator+(const vector<int>& v, int a);

vector<int> operator%(const vector<int>& v, int a);

#endif	/* UTILS_H */