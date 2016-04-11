#include "Game.h"

int main(int argc, char **argv) {
    cout << "Starting program..." << endl;
    Game g;
    g.init(640, 480);
    cout << "Finished initializing, beginning event loop" << endl;
    while (g.isRunning()) {
        g.handleEvents();
        SDL_Delay(10);
    }
    SDL_Quit();
    return 0;
}