#include "game.hpp"

int main() {
    Game game;

    if (!game.init()) {
        cerr << "Impossible de démarrer le jeu." << endl;
        return 1;
    }

    while (!WindowShouldClose() && !game.shouldExit()) {
        game.tick();    // input + logique
        game.render();  // rendu
    }

    return 0;
}
