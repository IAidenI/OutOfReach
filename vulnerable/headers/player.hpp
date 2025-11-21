#ifndef PLAYER_H
#define PLAYER_H

#include "geometry.hpp"
#include "crosshair.hpp"

class Player {
    private:
        Position3D position;
        float speed;
        float sensitivity;
        Vector2 rotation = { 0.0f, 0.0f };
        Crosshair crosshair;
    public:
        Player(Position3D position, float speed, float sensitivity);

        void setPosition(Position3D position) { this->position = position; }

        Position3D& getPosition() { return this->position; }
        float getSpeed() const { return this->speed; }
        float getSensitivity() const { return this->sensitivity; }
        Vector2 getRotation() const { return this->rotation; }
        Crosshair& getCrosshair() { return this->crosshair; }

        void setSpeed(float speed) { this->speed = speed; }
        void setSensitivity(float sensitivity) { this->sensitivity = sensitivity; }
        
        void addRotation(float dx, float dy);
        void move(Position3D direction, float dt);

        Position3D forward();
        Position3D backward();
        Position3D right();
        Position3D left();
};

#endif // PLAYER_H
