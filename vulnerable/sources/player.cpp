#include "player.hpp"

Player::Player(Position3D position, float speed, float sensitivity) {
    this->position = position;
    this->speed = speed;
    this->sensitivity = sensitivity;
}

void Player::addRotation(float dx, float dy) {
    this->rotation.x -= dx * this->sensitivity;
    this->rotation.y -= dy * this->sensitivity;

    // Pour bloquer si Y est trop haut ou bas
    if (this->rotation.y > 89.0f) this->rotation.y = 89.0f;
    if (this->rotation.y < -89.0f) this->rotation.y = -89.0f; 
}

void Player::move(Position3D direction, float dt) {
    this->position.x += direction.x * this->speed * dt;
    this->position.y += direction.y * this->speed * dt;
    this->position.z += direction.z * this->speed * dt;
}

Position3D Player::forward() {
    return {
        cosf(DEG2RAD * rotation.y) * sinf(DEG2RAD * rotation.x),
        sinf(DEG2RAD * rotation.y),
        cosf(DEG2RAD * rotation.y) * cosf(DEG2RAD * rotation.x) 
    };
}

Position3D Player::backward() {
    Vector3 f = this->forward();
    return { -f.x, -f.y, -f.z };
}

Position3D Player::right() {
    return {
        sinf(DEG2RAD * (this->rotation.x - 90.0f)),
        0,
        cosf(DEG2RAD * (this->rotation.x - 90.0f))
    };
}

Position3D Player::left()  {
    Vector3 r = this->right();
    return { -r.x, -r.y, -r.z };
}