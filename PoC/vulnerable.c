#include <stdio.h>
#include <unistd.h>

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

Player player = { "Aiden", { .x = 10.0f, .y = 15.0f }, { .width = 50.0f, .height = 80.0f }, 5.0f };

int main() {
    DisplayPlayerInfos(&player);

    printf("[ WAIT ] En attente de la modification du programme...\n");
    while (player.speed == 5.0f) {}

    DisplayPlayerInfos(&player);
    return 0;
}
