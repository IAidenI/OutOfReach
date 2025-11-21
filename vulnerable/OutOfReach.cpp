#include "game.hpp"

int main() {
    Game game;

    if (!game.init()) {
        cerr << "Impossible de démarrer le jeu." << endl;
        return 1;
    }

    printf("[ DEBUG ] Adresse de Game game     : %p\n", &game);
    printf("[ DEBUG ] Adresse de Player player : %p\n", &game.getPlayer());

    while (!WindowShouldClose()) {
        game.handleGlobalInput();

        if (!game.getPause()) {
            game.handlePlayerInputs();
            game.update();
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            game.drawLevel();
            game.drawCrossAir();
        EndDrawing();
    }

    return 0;
}
