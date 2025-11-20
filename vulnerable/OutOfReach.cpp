#include "game.hpp"

int main() {
    Game game;

    if (!game.init()) {
        cerr << "Impossible de démarrer le jeu." << endl;
        return 1;
    }

    while (!WindowShouldClose()) {
        game.handleGlobalInput();

        if (!game.getPause()) {
            game.update();
            game.handlePlayerInputs();
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            game.drawLevel();
            game.drawCrossAir();
        EndDrawing();
    }

    return 0;
}
