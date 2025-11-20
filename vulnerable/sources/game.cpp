#include "game.hpp"

Game::Game() : player({ 0.0f, 2.0f, 4.0f }, 5.0f, 5.0f) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow((int)SCREEN_WIDTH, (int)SCREEN_HEIGHT, "OutOfReach");
    SetTargetFPS(60);
    DisableCursor();

    this->camera = {
        .position = this->player.getPosition(),
        .target = { 0.0f, this->player.getPosition().y, 0.0f },
        .up = { 0.0f, 1.0f, 0.0f },
        .fovy = 60.0f,
        .projection = CAMERA_PERSPECTIVE
    };

    this->player.getCrosshair().init({ SCREEN_WIDTH, SCREEN_HEIGHT });
    this->player.getCrosshair().setCircle();
}

void Game::update() {
    UpdateCamera(&this->camera, this->cameraMode);
}

void Game::drawCrossAir() {
    if (this->cameraMode != CAMERA_THIRD_PERSON) {
        this->player.getCrosshair().draw();
    }
}

void Game::handleInputs() {
    if (IsKeyPressed(KEY_ONE)) this->cameraMode = CAMERA_FREE;

    if (IsKeyPressed(KEY_TWO)) this->cameraMode = CAMERA_FIRST_PERSON;

    if (IsKeyPressed(KEY_THREE)) cameraMode = CAMERA_THIRD_PERSON;

    if (IsKeyPressed(KEY_FOUR)) this->cameraMode = CAMERA_ORBITAL;

    if (IsKeyPressed(KEY_C)) {
        this->player.getCrosshair().nextShape();
    }
}

void Game::drawLevel() {
    BeginMode3D(this->camera);
        Position3D start = { 0.0f, 0.0f, 0.0f };
        Size2D size = { 32.0f, 32.0f };
        DrawPlane(start, size, LIGHTGRAY); // Draw ground

        Size3D blockSize = { 2.0f, 10.0f, 2.0f };
        Position3D blockPosition = { start.x, blockSize.y / 2.0f, start.y };
        DrawCubeV(blockPosition, blockSize, DARKBLUE);
        DrawCubeWiresV(blockPosition, blockSize, BLUE);

        // Draw player cube
        if (cameraMode == CAMERA_THIRD_PERSON) {
            DrawCube(camera.target, 0.5f, 0.5f, 0.5f, PURPLE);
            DrawCubeWires(camera.target, 0.5f, 0.5f, 0.5f, DARKPURPLE);
        }
    EndMode3D();
}

Game::~Game() {
    CloseWindow();
}
