#include "crosshair.hpp"

void Crosshair::init(Size2D SCREEN_SIZE) {
    this->SCREEN_SIZE = SCREEN_SIZE;
}

void Crosshair::setCircle(float radius, Color color) {
    this->position = {
        .x = this->SCREEN_SIZE.x / 2.0f,
        .y = this->SCREEN_SIZE.y / 2.0f
    };
    this->type = CROSSHAIR_CIRCLE;
    this->shape.circle.radius = radius;
    this->color = color;
}

void Crosshair::setSquare(float side, Color color) {
    this->position = {
        .x = this->SCREEN_SIZE.x / 2.0f - side / 2.0f,
        .y = this->SCREEN_SIZE.y / 2.0f - side / 2.0f
    };
    this->type = CROSSHAIR_SQUARE;
    this->shape.square.side = side;
    this->color = color;
}

void Crosshair::setCross(float length, float thickness, Color color) {
    this->position = {
        .x = this->SCREEN_SIZE.x / 2.0f - length / 2.0f,
        .y = this->SCREEN_SIZE.y / 2.0f - thickness / 2.0f
    };
    this->type = CROSSHAIR_CROSS;
    this->shape.cross.length = length;
    this->shape.cross.thickness = thickness;
    this->color = color;
}

void Crosshair::nextShape() {
    switch (this->type) {
        case CROSSHAIR_CIRCLE: this->setSquare(); break;
        case CROSSHAIR_SQUARE: this->setCross();  break;
        case CROSSHAIR_CROSS:  this->setCircle(); break;
    }
}

void Crosshair::draw() {
    switch (this->type) {
        case CROSSHAIR_CIRCLE: {
            DrawCircleV(this->position, this->shape.circle.radius, this->color);
            break;
        }
        case CROSSHAIR_SQUARE: {
            DrawRectangleV(this->position, { .x = this->shape.square.side, .y = this->shape.square.side }, this->color);
            break;
        }
        case CROSSHAIR_CROSS: {
            DrawRectangleV(this->position, { .x = this->shape.cross.length, .y = this->shape.cross.thickness }, this->color); // Horizontal
            Position2D localPosition = {
                .x = this->SCREEN_SIZE.x / 2.0f - this->shape.cross.thickness / 2.0f,
                .y = this->SCREEN_SIZE.y / 2.0f - this->shape.cross.length / 2.0f
            };
            DrawRectangleV(localPosition, { .x = this->shape.cross.thickness, .y = this->shape.cross.length }, this->color); // Horizontal
            break;
        }
        default:
            break;
    }
}
