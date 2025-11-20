#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include "geometry.hpp"
#include "game_settings.hpp"
#include "player.hpp"

inline constexpr int MAX_COLUMNS = 20;

class Game {
    private:
        Player player;
        Camera3D camera;
        int cameraMode = CAMERA_FIRST_PERSON;
        int crosshairMode = 0;
    public:
        Game();

        void update();
        void drawCrossAir();
        void handleInputs();
        void drawLevel();

        ~Game();
};

#endif // GAME_H
