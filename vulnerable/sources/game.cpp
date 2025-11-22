#include "game.hpp"

Game::Game() : player({ 0.0f, 2.0f, 0.0f }, 5.0f, 0.6f) {
    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_MSAA_4X_HINT);
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), GAME_NAME);
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
}

bool Game::init() {
    // ---- Initiaéliser les textures/fonts ----
    if (!this->manager.init()) {
        cerr << "[FATAL] Manager invalide : ressources manquantes." << endl;
        return false;
    }

    // ---- Sauvegarde la taille de l'écran ---
    this->screenWidth = (float)GetScreenWidth();
    this->screenHeight = (float)GetScreenHeight();

    // ---- Initialise la caméra du joueur ----
    this->player.setRotation({ 180.0f, 0.0f }); 
    this->camera = {
        .position = this->player.getPosition(),
        .target = Vector3Add(this->player.getPosition(), this->player.forwardCamera()),
        .up = { 0.0f, 10.0f, 0.0f },
        .fovy = 90.0f,
        .projection = CAMERA_PERSPECTIVE
    };

    // ---- Initialise le crosshair ----
    this->player.getCrosshair().init({ this->screenWidth, this->screenHeight });
    this->player.getCrosshair().setCircle();
    return true;
}

// ---- Boucle principale ----
void Game::tick() {
    this->handleGlobalInput();

    switch (this->state) {
        case State::StartMenu: break;
        case State::Playing:
            this->handlePlayerInputs();
            this->update();
            break;
        case State::Paused: break;
        default: break;
    }
}

void Game::render() {
    BeginDrawing();
        ClearBackground(RAYWHITE);
        // Rendu du monde si nécessaire
        if (this->state == State::Playing || this->state == State::Paused || this->state == State::SettingsMenu) drawLevel();

        switch (state) {
            case State::StartMenu:    this->drawMenuStart();    break;
            case State::Playing:      this->drawCrossAir();     break;
            case State::SettingsMenu: this->drawMenuSettings(); break;
            case State::Paused:       this->drawMenuPause();    break;
            default: break;
        }
    EndDrawing();
}

// ---- Transitions de jeu ----
void Game::startNewGame() {
    this->pushState(State::Playing);
    DisableCursor();
}

void Game::settings() {
    this->pushState(State::SettingsMenu);
}

void Game::pause() {
    this->pushState(State::Paused);
    EnableCursor();
}

void Game::resume() {
    this->pushState(State::Playing);
    DisableCursor();
}

void Game::pushState(State newState) {
    this->stateStack.push_back(state);
    this->state = newState;
}

Game::State Game::previousState() {
    return stateStack.empty() ? State::StartMenu : stateStack.back();
}

void Game::back() {
    this->state = this->previousState();
    this->stateStack.pop_back();
}

// ---- Logique interne ----
void Game::update() {
    // ---- Camera et déplacements ----
    float dt = GetFrameTime();

    // Déplacement de la caméra avec la souris
    Vector2 mouseDelta = GetMouseDelta();
    this->player.addRotation(mouseDelta.x, mouseDelta.y);

    Position3D moveDirection = { 0.0f };
    // Déplacement du joueur avec le clavier
    if (IsKeyDown(KEY_W)) moveDirection = Vector3Add(moveDirection, this->player.forward());
    if (IsKeyDown(KEY_S)) moveDirection = Vector3Add(moveDirection, this->player.backward());
    if (IsKeyDown(KEY_D)) moveDirection = Vector3Add(moveDirection, this->player.right());
    if (IsKeyDown(KEY_A)) moveDirection = Vector3Add(moveDirection, this->player.left());

    // Mets a jour le déplacement
    if (Vector3Length(moveDirection) > 0.1f) moveDirection = Vector3Normalize(moveDirection);
    this->player.move(moveDirection, dt);

    // Mets a jours la caméra
    this->camera.position = this->player.getPosition();
    this->camera.target = Vector3Add(this->player.getPosition(), this->player.forwardCamera());
}

void Game::handleGlobalInput() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        switch (state) {
            case State::StartMenu:    exit = true; break;
            case State::SettingsMenu: back();      break;
            case State::Playing:      pause();     break;
            case State::Paused:       resume();    break;
            default: break;
        }
    }
}

void Game::handlePlayerInputs() {
    if (IsKeyPressed(KEY_Q)) this->displayDebug = !this->displayDebug;

    if (IsKeyPressed(KEY_C)) this->player.getCrosshair().nextShape();

    if (IsKeyPressed(KEY_H)) this->displayHUD = !this->displayHUD;
}

// ---- Menus ----
void Game::drawMenuPause() {
    vector<MenuEntry> buttons = {
        { "Reprendre", MenuAction::Resume },
        { "Paramètres", MenuAction::Settings },
        { "Quitter", MenuAction::Exit }
    };

    MenuAction clicked = this->drawMenu("Menu Pause", COLOR_MENU_PAUSE_BACKGROUND, buttons);
    switch (clicked) {
        case MenuAction::Resume: this->resume();     break;
        case MenuAction::Settings: this->settings(); break;
        case MenuAction::Exit:   this->exit = true;  break;
        default: break;
    }
}

void Game::drawMenuStart() {
    vector<MenuEntry> buttons = {
        { "Nouvelle partie", MenuAction::NewGame },
        { "Paramètres", MenuAction::Settings },
        { "Quitter", MenuAction::Exit }
    };

    MenuAction clicked = this->drawMenu(GAME_NAME, COLOR_MENU_START_BACKGROUND, buttons);
    switch (clicked) {
        case MenuAction::NewGame:  this->startNewGame(); break;
        case MenuAction::Settings: this->settings();     break;
        case MenuAction::Exit:     this->exit = true;    break;
        default: break;
    }
}

void Game::drawMenuSettings() {
    vector<MenuEntry> buttons = {
        { "Retour", MenuAction::Resume }
    };

    Color bg = (previousState() == State::StartMenu) ? COLOR_MENU_START_BACKGROUND : COLOR_MENU_PAUSE_BACKGROUND;
    //MenuAction clicked = this->drawMenu("Paramètres", bg, buttons);
    MenuAction clicked = this->settingsTemp(bg);

    if (clicked == MenuAction::Back) this->back();
}

Game::MenuAction Game::settingsTemp(Color background) {
    DrawRectangle(0, 0, (int)this->screenWidth, (int)this->screenHeight, background);
    
    // --- Calcul du titre ---
    TextStyle title = {
        .font = &this->manager.getFont(INFO_FONT, (int)MENU_TITLE_SIZE),
        .text = "Paramètres",
        .fontSize = MENU_TITLE_SIZE,
        .spacing = 2.0f,
        .lineSpacing = 1.0f,
        .color = COLOR_MENU_TITLE
    };
    Size2D titleSize = MeasureTextStyled(title);

    Position2D center = { this->screenWidth  / 2.0f, this->screenHeight / 2.0f };

    // --- Calcul de la taille du bouton ---
    TextStyle btnBackText = {
        .font = &this->manager.getFont(INFO_FONT, (int)MENU_BUTTON_SIZE),
        .text = "Retour",
        .fontSize = MENU_BUTTON_SIZE,
        .spacing = 2.0f,
        .lineSpacing = 1.0f,
        .color = COLOR_MENU_BUTTON_TEXT
    };
    Size2D btnBackSize = GetMenuButtonSize(btnBackText);

    float titlePadY = 40.0f;
    float totalHeight = titleSize.y + titlePadY + btnBackSize.y + 60.0f;

    // --- Calcul de la taille des paramètres ---
    float slidBarPadY = 25.0f;
    Size2D slidBarSize = { 300, 50 };

    // --- Affichage du titre ---
    Position2D titlePosition = {
        center.x - titleSize.x / 2.0f,
        center.y - totalHeight / 2.0f
    };
    DrawTextStyled(title, titlePosition);
    
    // --- Affichage des paramètres
    // Sentibilité
    Rectangle sensibilityBounds = {
        center.x - slidBarSize.x / 2.0f,
        titlePosition.y + titleSize.y + titlePadY,
        slidBarSize.x,
        slidBarSize.y
    };
    Rectangle fovBounds = {
        center.x - slidBarSize.x / 2.0f,
        sensibilityBounds.y + slidBarSize.y + slidBarPadY,
        slidBarSize.x,
        slidBarSize.y
    };

    TextStyle leftText = {
        .font = &this->manager.getFont(INFO_FONT, 40),
        .text = "Sensi",
        .fontSize = 40.0f,
        .spacing = 2.0f,
        .lineSpacing = 1.0f,
        .color = BLACK
    };
    TextStyle rightText = {
        .font = &this->manager.getFont(INFO_FONT, 40),
        .text = TextFormat("%.2f", this->player.getSensitivity()),
        .fontSize = 40.0f,
        .spacing = 2.0f,
        .lineSpacing = 1.0f,
        .color = BLACK
    };
    GuiSliderBar(sensibilityBounds, leftText, rightText, &this->player.getSensitivity(), 0.1f, 2.0f, COLOR_MENU_BUTTON_BORDER);
    leftText.text  = "FOV";
    rightText.text = TextFormat("%.0f°", this->camera.fovy);
    GuiSliderBar(fovBounds, leftText, rightText, &this->camera.fovy, 30.0f, 120.0f, COLOR_MENU_BUTTON_BORDER);

    // --- Affichage du boutton ---
    Position2D btnBackPosition = {
        center.x - btnBackSize.x / 2.0f,
        sensibilityBounds.y + sensibilityBounds.y + 30.0f
    };
    ButtonResult result = DrawMenuButton(btnBackText, btnBackPosition);

    MenuAction clicked = MenuAction::None;
    if (result.pressed) clicked = MenuAction::Back;
    return clicked;
}

Game::MenuAction Game::drawMenu(const char *titleText, Color background, const vector<MenuEntry>& buttons) {
    // Effet de focus
    DrawRectangle(0, 0, (int)this->screenWidth, (int)this->screenHeight, background);
    
    float buttonPadY = 50.0f;
    float titlePadY = 40.0f;

    float centerX = this->screenWidth  / 2.0f;
    float centerY = this->screenHeight / 2.0f;
    
    // --- Calcul du titre ---
    TextStyle title = {
        .font = &this->manager.getFont(INFO_FONT, (int)MENU_TITLE_SIZE),
        .text = titleText,
        .fontSize = MENU_TITLE_SIZE,
        .spacing = 2.0f,
        .lineSpacing = 1.0f,
        .color = COLOR_MENU_TITLE
    };
    Size2D titleSize = MeasureTextStyled(title);

    // --- Calcul de la tailles des boutons ---
    vector<Size2D> buttonsSize;
    buttonsSize.reserve(buttons.size());

    float totalButtonHeight = 0;
    for (auto& button : buttons) {
        TextStyle text = {
            .font = &this->manager.getFont(INFO_FONT, (int)MENU_BUTTON_SIZE),
            .text = button.label,
            .fontSize = MENU_BUTTON_SIZE,
            .spacing = 2.0f,
            .lineSpacing = 1.0f,
            .color = COLOR_MENU_BUTTON_TEXT
        };
        Size2D size = GetMenuButtonSize(text);
        buttonsSize.push_back(size);
        totalButtonHeight += size.y;
    }

    // --- Calcul de la hauteur total ---
    float totalHeight = titleSize.y + titlePadY + totalButtonHeight;

    // --- Affichage du titre ---
    Position2D titlePosition = {
        centerX - titleSize.x / 2.0f,
        centerY - totalHeight / 2.0f
    };
    DrawTextStyled(title, titlePosition);

    // --- Affichage des bouttons ---
    MenuAction clicked = MenuAction::None;
    float currentY = titlePosition.y + titleSize.y + titlePadY;
    for (size_t i = 0; i < buttons.size(); i++) {
        TextStyle buttonText = {
            .font = &this->manager.getFont(INFO_FONT, (int)MENU_BUTTON_SIZE),
            .text = buttons[i].label,
            .fontSize = MENU_BUTTON_SIZE,
            .spacing = 2.0f,
            .lineSpacing = 1.0f,
            .color = COLOR_MENU_BUTTON_TEXT
        };
        Position2D buttonPosition = {
            centerX - buttonsSize[i].x / 2.0f,
            currentY
        };

        ButtonResult result = DrawMenuButton(buttonText, buttonPosition);
        if (result.pressed) clicked = buttons[i].action;

        currentY += buttonsSize[i].y + buttonPadY;
    }

    return clicked;
}

// ---- HUD ----
void Game::drawCrossAir() {
    this->player.getCrosshair().draw();
}

// ---- Monde ----
void Game::drawSign(TextStyle& message, Position3D origin, Padding padIn, Color color) {
    // Socle
    float poleHeight = 1.5f;
    Size3D cylSize = { 0.1f, 0.1f, poleHeight };
    DrawCylinder(origin, cylSize.x, cylSize.y, cylSize.z, 16, color);

    // Panneau
    Size2D textSize = MeasureTextStyled(message);
    Size3D panelSize = {
        textSize.x + padIn.x * 2.0f,
        textSize.y + padIn.y * 2.0f,
        0.2f
    };
    Position3D panelPosition = origin;
    panelPosition.y += poleHeight + panelSize.y / 2.0f;
    DrawCubeV(panelPosition, panelSize, color);
    this->drawArrowAxies(panelPosition);
    
    // Texte
    Position3D textPos = {
        panelPosition.x - textSize.x / 2.0f,
        panelPosition.y + textSize.y / 2.0f,
        panelPosition.z + panelSize.z / 2.0f + 0.001f
    };
    this->drawText3D(message, textPos, false);
    this->drawArrowAxies(textPos);
}

// AXE X (rouge)
// AXE Y (vert)
// AXE Z (bleu)
void Game::drawArrowAxies(Position3D plan, float size) {
    if (!this->displayDebug) return;
    
    // ---- AXE X (rouge) ----
    DrawLine3D(plan, { plan.x + size, plan.y, plan.z }, RED);
    DrawCube({ plan.x + size, plan.y, plan.z }, 0.2f, 0.2f, 0.2f, RED);

    // ---- AXE Y (vert) ----
    DrawLine3D(plan, { plan.x, plan.y + size, plan.z }, GREEN);
    DrawCube({ plan.x, plan.y + size, plan.z }, 0.2f, 0.2f, 0.2f, GREEN);

    // ---- AXE Z (bleu) ----
    DrawLine3D(plan, { plan.x, plan.y, plan.z + size }, BLUE);
    DrawCube({ plan.x, plan.y, plan.z + size }, 0.2f, 0.2f, 0.2f, BLUE);
}

void Game::drawLevel() {
    BeginMode3D(this->camera);
        // Dessine le sol
        Position3D start = { 0.0f, 0.0f, 0.0f };
        Size2D size = { 32.0f, 32.0f };
        DrawPlane(start, size, LIGHTGRAY);
        this->drawArrowAxies(start);

        // Dessine un bloc d'exemple
        Size3D blockSize = { 4.0f, 50.0f, 4.0f };
        Position3D blockPosition = { start.x, blockSize.y / 2.0f, start.y - (blockSize.z + 3.0f) };
        DrawCubeV(blockPosition, blockSize, DARKBLUE);
        DrawCubeWiresV(blockPosition, blockSize, BLUE);
        this->drawArrowAxies(blockPosition, 6.0f);

        // Dessine un panneau
        Position3D signPosition = { blockPosition.x, blockPosition.y + blockSize.y / 2.0f, blockPosition.z };
        TextStyle message = {
            .font = &this->manager.getFont(INFO_FONT, 0.16),
            .text = "Bravo\nTu as trouvé le texte caché\nFlag : FLAG{}",
            .fontSize = 0.16f,
            .spacing = 0.02f,
            .lineSpacing = 0.05f,
            .color = BLACK
        };
        this->drawSign(message, signPosition);
        this->drawArrowAxies(signPosition);
    EndMode3D();
}

// Code repris de https://www.raylib.com/examples/text/loader.html?name=text_3d_drawing
void Game::drawTextCodepoint3D(Font font, int codepoint, Vector3 position, float fontSize, bool backface, Color tint) {
    // Character index position in sprite font
    // NOTE: In case a codepoint is not available in the font, index returned points to '?'
    int index = GetGlyphIndex(font, codepoint);
    float scale = fontSize/(float)font.baseSize;

    // Character destination rectangle on screen
    // NOTE: We consider charsPadding on drawing
    position.x += (float)(font.glyphs[index].offsetX - font.glyphPadding)*scale;
    position.y -= (float)(font.glyphs[index].offsetY - font.glyphPadding)*scale;

    // Character source rectangle from font texture atlas
    // NOTE: We consider chars padding when drawing, it could be required for outline/glow shader effects
    Rectangle srcRec = { font.recs[index].x - (float)font.glyphPadding, font.recs[index].y - (float)font.glyphPadding,
                         font.recs[index].width + 2.0f*font.glyphPadding, font.recs[index].height + 2.0f*font.glyphPadding };

    float width = (float)(font.recs[index].width + 2.0f*font.glyphPadding)*scale;
    float height = (float)(font.recs[index].height + 2.0f*font.glyphPadding)*scale;

    if (font.texture.id > 0) {
        const float x = 0.0f;
        const float y = 0.0f;
        const float z = 0.0f;

        // normalized texture coordinates of the glyph inside the font texture (0.0f -> 1.0f)
        const float tx = srcRec.x/font.texture.width;
        const float ty = srcRec.y/font.texture.height;
        const float tw = (srcRec.x+srcRec.width)/font.texture.width;
        const float th = (srcRec.y+srcRec.height)/font.texture.height;

        if (this->displayDebug) DrawCubeWiresV((Vector3){ position.x + width/2, position.y - height/2, position.z }, (Vector3){ width, height, 0.25f }, VIOLET);

        rlCheckRenderBatchLimit(4 + 4*backface);
        rlSetTexture(font.texture.id);

        rlPushMatrix();
            rlTranslatef(position.x, position.y, position.z);

            rlBegin(RL_QUADS);
                rlColor4ub(tint.r, tint.g, tint.b, tint.a);

                // Front Face
                rlNormal3f(0.0f, 0.0f, 1.0f);                                   // Normal Pointing Up
                rlTexCoord2f(tx, ty); rlVertex3f(x,         y         , z);     // Top Left Of The Texture and Quad
                rlTexCoord2f(tx, th); rlVertex3f(x,         y - height, z);     // Bottom Left Of The Texture and Quad
                rlTexCoord2f(tw, th); rlVertex3f(x + width, y - height, z);     // Bottom Right Of The Texture and Quad
                rlTexCoord2f(tw, ty); rlVertex3f(x + width, y         , z);     // Top Right Of The Texture and Quad

                if (backface) {
                    // Back Face
                    rlNormal3f(0.0f, 0.0f, -1.0f);                              // Normal Pointing Down
                    rlTexCoord2f(tx, ty); rlVertex3f(x,         y         , z); // Top Right Of The Texture and Quad
                    rlTexCoord2f(tw, ty); rlVertex3f(x + width, y         , z); // Top Left Of The Texture and Quad
                    rlTexCoord2f(tw, th); rlVertex3f(x + width, y - height, z); // Bottom Left Of The Texture and Quad
                    rlTexCoord2f(tx, th); rlVertex3f(x,         y - height, z); // Bottom Right Of The Texture and Quad
                }
            rlEnd();
        rlPopMatrix();

        rlSetTexture(0);
    }
}

void Game::drawText3D(const TextStyle& message, Vector3 position, bool backface) {
    int length = TextLength(message.text.c_str());          // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0.0f;               // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f;               // Offset X to next character to draw

    float scale = message.fontSize/(float)message.font->baseSize;

    for (int i = 0; i < length;) {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = GetCodepoint(&message.text[i], &codepointByteCount);
        int index = GetGlyphIndex(*message.font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) codepointByteCount = 1;

        if (codepoint == '\n') {
            // NOTE: Fixed line spacing of 1.5 line-height
            // TODO: Support custom line spacing defined by user
            textOffsetY -= message.fontSize + message.lineSpacing;
            textOffsetX = 0.0f;
        }
        else {
            if ((codepoint != ' ') && (codepoint != '\t')) {
                this->drawTextCodepoint3D(*message.font, codepoint, (Vector3){ position.x + textOffsetX, position.y + textOffsetY, position.z }, message.fontSize, backface, message.color);
            }

            if (message.font->glyphs[index].advanceX == 0) textOffsetX += (float)message.font->recs[index].width*scale + message.spacing;
            else textOffsetX += (float)message.font->glyphs[index].advanceX*scale + message.spacing;
        }

        i += codepointByteCount;   // Move text bytes counter to next codepoint
    }
}

Game::~Game() {
    CloseWindow();
}
