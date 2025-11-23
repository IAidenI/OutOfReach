#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <rlgl.h>
#include <string>
#include <vector>
#include "geometry.hpp"
#include "default_constants.hpp"
#include "player.hpp"
#include "manager.hpp"
#include "style.hpp"
#include "colors.hpp"
#include "component_UI.hpp"

// ---- Settings ----
inline constexpr const char *GAME_NAME    = "OutOfReach";
inline constexpr Size2D      WORLD_SIZE   = { 500.0f, 500.0f };
inline constexpr Position3D  WORLD_CENTER = { 0.0f, 0.0f, 0.0f };


class Game {
    public:
        // Etat du jeu
        enum class State {
            None,
            StartMenu,
            SettingsMenu,
            Playing,
            Paused
        };

    private:
        // --- Core ---
        Manager manager;
        float targetFps = 60.0f;

        // Le joueur
        Player player;
        Camera3D camera;
        int crosshairMode = 0;

        // Paramètres
        float screenWidth;
        float screenHeight;

        // Autre flags d'affichage
        bool displayDebug = false;
        bool displayHUD = true;

        // Etat du jeu
        State state = State::StartMenu;
        vector<State> stateStack;
        bool exit = false;
        bool handCursor = false;

        // --- Menu ---
        enum class MenuAction {
            None,
            Resume,
            NewGame,
            Settings,
            Back,
            Exit
        };

        struct MenuEntry  {
            const char *label;
            MenuAction action;
        };

        // ---- Transitions de jeu ----
        void startNewGame();
        void settings();
        void pause();
        void resume();
        void pushState(State newState);
        void back();
        State previousState();

        // ---- Test ----
        Model groundModel;
        Texture2D groundAlbedo;

    public:
        Game();
        bool init();

        // ---- Accès à l'état ----
        bool shouldExit() const { return this->exit; }
        State getState() const { return this->state; }
        bool getHandCursor() const { return this->handCursor; }

        // ---- Boucle principale ----
        void tick();   // input + logique selon state
        void render(); // dessin selon state

        // ---- Logique interne ----
        void update();
        void handleGlobalInput();
        void handlePlayerInputs();

        // ---- Menus ----
        void drawMenuPause();
        void drawMenuStart();
        void drawMenuSettings();
        MenuAction settingsTemp(Color background);
        MenuAction drawMenu(const char *titleText, Color background, const vector<MenuEntry>& buttons);

        // ---- HUD ----
        void drawHUD();
        
        // ---- Monde ----
        void drawSign(TextStyle& message, Position3D origin, Padding padIn = DEFAULT_PAD_IN_3D, Color color = DARKPURPLE);
        void drawArrowAxies(Position3D plan, float size = 10.0f);
        void drawLevel();

        // Code repris de https://www.raylib.com/examples/text/loader.html?name=text_3d_drawing
        void drawTextCodepoint3D(Font font, int codepoint, Vector3 position, float fontSize, bool backface, Color tint);
        void drawText3D(const TextStyle& message, Vector3 position, bool backface);

        ~Game();
};

#endif // GAME_H
