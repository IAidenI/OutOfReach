#include <iostream>
#include <unistd.h>
#include <string>

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
        Game() : player("Aiden", { 10.f, 15.f }, 50.f, 80.f, 5.f) {}

        Player& getPlayer() { return this->player; }

        void wait() const {
            std::cout << "[ WAIT ] En attente de la modification du programme...\n";
            while (this->player.position.x == 10.0f && this->player.position.y == 15.0f) {}
        }
};

int main() {
    Game game;

    game.getPlayer().DisplayInfos();

    game.wait();

    game.getPlayer().DisplayInfos();

    return 0;
}
