#ifndef PLAYER_H
#define PLAYER_H

#include "geometry.hpp"
#include "crosshair.hpp"

class Player {
    private:
        Position3D position;
        float speed;
        float height;
        Crosshair crosshair;
    public:
        Player(Position3D position, float speed, float height);

        Position3D getPosition() const { return this->position; }
        float getSpeed() const { return this->speed; }
        float getHeight() const { return this->height; }
        Crosshair& getCrosshair() { return this->crosshair; }
};

#endif // PLAYER_H