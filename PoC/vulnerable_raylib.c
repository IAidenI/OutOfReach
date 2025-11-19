#include <stdio.h>
#include <unistd.h>
#include <raylib.h>

typedef struct {
    float x;
    float y;
} Position;

typedef struct {
    float width;
    float height;
} Size;

typedef struct {
    const char *name;
    Position position;
    Size size;
    float speed;
} Player;

void DisplayPlayerInfos(const Player *player);

void DisplayPlayerInfos(const Player *player) {
    printf(" --- %s ---\n", player->name);
    printf("   Position : X=%.0f;Y=%.0f\n", player->position.x, player->position.y);
    printf("   Taille   : %.0fx%.0f\n", player->size.width, player->size.height);
    printf("   Vitesse  : %.0f\n\n", player->speed);
}

Player player = { "Aiden", { .x = 10.0f, .y = 15.0f }, { .width = 50.0f, .height = 80.0f }, 1.0f };

int main() {
    int SCREEN_WIDTH  = 600;
    int SCREEN_HEIGHT = 300;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PoC - Runtime Process Modification");
    SetTargetFPS(60);


    while(!WindowShouldClose()) {
        if (IsKeyDown(KEY_W) && player.position.y > 0)
            player.position.y -= player.speed;

        if (IsKeyDown(KEY_S) && player.position.y + player.size.height < SCREEN_HEIGHT)
            player.position.y += player.speed;

        if (IsKeyDown(KEY_A) && player.position.x > 0)
            player.position.x -= player.speed;

        if (IsKeyDown(KEY_D) && player.position.x + player.size.width < SCREEN_WIDTH)
            player.position.x += player.speed;

        if (IsKeyPressed(KEY_F)) DisplayPlayerInfos(&player);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawRectangle(player.position.x, player.position.y, player.size.width, player.size.height, RED);
        EndDrawing();
    }

    return 0;
}
