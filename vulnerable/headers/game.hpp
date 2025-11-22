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
#include "colors.hpp"
#include "component_UI.hpp"

inline constexpr const char *GAME_NAME  = "OutOfReach";
inline constexpr float MENU_TITLE_SIZE  = 120.0f;
inline constexpr float MENU_BUTTON_SIZE = 64.0f;

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
    public:
        Game();
        bool init();

        // ---- Accès à l'état ----
        bool shouldExit() const { return this->exit; }
        State getState() const { return this->state; }

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
        void drawCrossAir();
        
        // ---- Monde ----
        void drawSign(TextStyle& message, Position3D origin, Padding padIn = DEFAULT_PAD_IN_3D, Color color = DARKPURPLE);
        void drawArrowAxies(Position3D plan, float size = 1.0f);
        void drawLevel();

        // Code repris de https://www.raylib.com/examples/text/loader.html?name=text_3d_drawing
        void drawTextCodepoint3D(Font font, int codepoint, Vector3 position, float fontSize, bool backface, Color tint);
        void drawText3D(const TextStyle& message, Vector3 position, bool backface);

        ~Game();
};

#endif // GAME_H
