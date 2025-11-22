#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <rlgl.h>
#include <string>
#include <vector>
#include "geometry.hpp"
#include "game_settings.hpp"
#include "player.hpp"
#include "manager.hpp"
#include "style.hpp"

inline constexpr int MAX_COLUMNS = 20;
inline constexpr float LETTER_BOUNDRY_SIZE = 0.25f;
inline constexpr Color LETTER_BOUNDRY_COLOR = VIOLET;

class Game {
    private:
        Manager manager;

        Player player;
        Camera3D camera;
        int crosshairMode = 0;

        bool displayDebug = false;
        bool pause = false;
    public:
        Game();
        bool init();

        bool getPause() const { return this->pause; }
        Player& getPlayer() { return this->player; }

        void update();

        void handleGlobalInput();
        void handlePlayerInputs();

        void drawCrossAir();
        void drawSign(TextStyle& message, Position3D origin, Padding padIn = DEFAULT_PAD_IN_3D, Color color = DARKPURPLE);
        void drawArrowAxies(Position3D plan, float size = 1.0f);
        void drawLevel();

        void drawTextCodepoint3D(Font font, int codepoint, Vector3 position, float fontSize, bool backface, Color tint);
        void drawText3D(const TextStyle& message, Vector3 position, bool backface);

        ~Game();
};

#endif // GAME_H
