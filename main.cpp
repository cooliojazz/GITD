#include "Game.h"

int main(int argc, char **argv) {
    cout << "Starting program..." << endl;
    Game g;
    g.init(640, 480);
    while (true) {
        g.render();
        SDL_Delay(1000);
    }
    return 0;
}