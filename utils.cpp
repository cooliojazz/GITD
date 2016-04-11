#include "utils.h"

SDL_Rect* createRect(int x, int y, int w, int h) {
    SDL_Rect* rect = new SDL_Rect();
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
    return rect;
}

bool contains(SDL_Rect* r, int x, int y) {
    return x >= r->x && x <= r->x + r->w && y >= r->y && y <= r->y + r->h;
}

bool intersects(SDL_Rect* r1, SDL_Rect* r2) {
    return
            contains(r1, r2->x, r2->y) ||
            contains(r1, r2->x + r2->w, r2->y) ||
            contains(r1, r2->x + r2->w, r2->y + r2->h) ||
            contains(r1, r2->x, r2->y + r2->h);
}

vector<int> operator+(const vector<int>& v, int a) {
    vector<int> ret = v;
    for (unsigned int i = 0; i < ret.size(); i++) ret[i] += a;
    return ret;
}

vector<int> operator%(const vector<int>& v, int a) {
    vector<int> ret = v;
    for (unsigned int i = 0; i < ret.size(); i++) ret[i] %= a;
    return ret;
}