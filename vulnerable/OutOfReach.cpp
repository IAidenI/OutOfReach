#include "game.hpp"

int main() {
    Game game;

    while (!WindowShouldClose()) {
        game.update();

        game.handleInputs();

        BeginDrawing();
            ClearBackground(RAYWHITE);

            game.drawLevel();
            game.drawCrossAir();
        EndDrawing();
    }

    return 0;
}
