#include <iostream>
#include <unistd.h>
#include <raylib.h>

typedef struct {
    float x;
    float y;
} Position2D;

typedef struct {
    float width;
    float height;
} Size;

class Player {
    public:
        const char* name;
        Position2D position;
        Size size;
        float speed;

    public:
        Player(const char* name, Position2D position, float width, float height, float speed) : name(name) {
            this->position = position;
            this->size.width = width;
            this->size.height = height;
            this->speed = speed;
        }

        void DisplayInfos() const {
            std::cout << " --- " << this->name << " ---\n";
            std::cout << "   Position : X=" << this->position.x << ";Y=" << this->position.y << "\n";
            std::cout << "   Taille   : " << this->size.width << "x" << this->size.height << "\n";
            std::cout << "   Vitesse  : " << this->speed << "\n\n";
        }
};

class Game {
    private:
        Player player;
    public:
        Game(int SCREEN_WIDTH, int SCREEN_HEIGHT) : player("Aiden", { 10.f, 15.f }, 50.f, 80.f, 5.f) {
            InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PoC - Runtime Process Modification");
            SetTargetFPS(60);
        }

        Player& getPlayer() { return this->player; }
};

int main() {
    int SCREEN_WIDTH  = 600;
    int SCREEN_HEIGHT = 300;
    Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

    void* rbp_in_main = __builtin_frame_address(0);
    printf("[ DEBUG ] RBP dans main : %p\n", rbp_in_main);
    printf("[ DEBUG ] Adresse de Game game    : %p\n", &game);
    printf("[ DEBUG ] Adresse de player.speed : %p\n", &game.getPlayer().speed);

    while(!WindowShouldClose()) {
        if (IsKeyDown(KEY_W) && game.getPlayer().position.y > 0)
            game.getPlayer().position.y -= game.getPlayer().speed;

        if (IsKeyDown(KEY_S) && game.getPlayer().position.y + game.getPlayer().size.height < SCREEN_HEIGHT)
            game.getPlayer().position.y += game.getPlayer().speed;

        if (IsKeyDown(KEY_A) && game.getPlayer().position.x > 0)
            game.getPlayer().position.x -= game.getPlayer().speed;

        if (IsKeyDown(KEY_D) && game.getPlayer().position.x + game.getPlayer().size.width < SCREEN_WIDTH)
            game.getPlayer().position.x += game.getPlayer().speed;

        if (IsKeyPressed(KEY_F)) game.getPlayer().DisplayInfos();

        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawRectangle(game.getPlayer().position.x, game.getPlayer().position.y, game.getPlayer().size.width, game.getPlayer().size.height, RED);
        EndDrawing();
    }

    return 0;
}
