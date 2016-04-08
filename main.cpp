#include "Game.h"

int main(int argc, char **argv) {
    cout << "Starting program..." << endl;
    Game g;
    g.init(640, 480);
    cout << "Finished initializing, beginning event loop" << endl;
    while (true) {
        g.handleEvents();
        SDL_Delay(100);
    }
    return 0;
}