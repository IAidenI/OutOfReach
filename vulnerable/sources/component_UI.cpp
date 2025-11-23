#include "component_UI.hpp"

Size2D GetMenuButtonSize(const TextStyle& message, Padding padIn) {
    Size2D textSize = MeasureTextStyled(message);

    // Taille des biseaux
    float arrow = DEFAULT_ARROW_SIZE;

    float rectWidth  = textSize.x + 2.0f * padIn.x;
    float rectHeight = textSize.y + 2.0f * padIn.y;

    // Largeur totale = rectangles + 2 triangles
    float totalWidth = rectWidth + 2.0f * arrow;

    return { totalWidth, rectHeight };
}

ButtonResult DrawMenuButton(const TextStyle& message, Position2D position, Padding padIn, float borderThick, Color bgColor, Color borderColor) {
    float x = position.x;
    float y = position.y;
    Size2D textSize = MeasureTextStyled(message);

    // Taille des biseaux
    float arrow = DEFAULT_ARROW_SIZE;

    float rectWidth  = textSize.x + 2.0f * padIn.x;
    float rectHeight = textSize.y + 2.0f * padIn.y;

    // --- Rectangle central ---
    Rectangle rectangle = {
        x + arrow,
        y,
        rectWidth,
        rectHeight
    };

    // --- Triangle gauche ---
    Position2D leftTop     = { x + arrow, y };
    Position2D leftBottom  = { x + arrow, y + rectHeight };
    Position2D leftMiddle  = { x,         y + rectHeight / 2.0f };

    // --- Triangle droit ---
    Position2D rightTop    = { x + arrow + rectWidth,        y };
    Position2D rightBottom = { x + arrow + rectWidth,        y + rectHeight };
    Position2D rightMiddle = { x + 2.0f * arrow + rectWidth, y + rectHeight / 2.0f };

    // --- Hover ---
    bool hover = false;
    bool pressed = false;
    Position2D mousePosition = GetMousePosition();
    if (CheckCollisionPointRec(mousePosition, rectangle) ||
        CheckCollisionPointTriangle(mousePosition, leftTop, leftMiddle, leftBottom) ||
        CheckCollisionPointTriangle(mousePosition, rightTop, rightBottom, rightMiddle)) {
        hover = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) pressed = true;
    }

    // --- Affichage ---
    bgColor = hover ? Lighten(bgColor) : bgColor;
    
    // Bouton
    DrawRectangleRec(rectangle, bgColor);
    DrawTriangle(leftTop, leftMiddle, leftBottom, bgColor);
    DrawTriangle(rightTop, rightBottom, rightMiddle, bgColor);
    
    // Bordure
    DrawLineEx(leftMiddle, leftTop, borderThick, borderColor);
    DrawLineEx(leftTop, rightTop, borderThick, borderColor);
    DrawLineEx(rightTop, rightMiddle, borderThick, borderColor);
    DrawLineEx(rightMiddle, rightBottom, borderThick, borderColor);
    DrawLineEx(rightBottom, leftBottom, borderThick, borderColor);
    DrawLineEx(leftBottom, leftMiddle, borderThick, borderColor);
    // Petits disques aux jonctions pour éviter les gaps
    float r = borderThick * 0.5f;
    DrawCircleV({ leftMiddle.x,  leftMiddle.y  }, r, borderColor);
    DrawCircleV({ leftTop.x,     leftTop.y     }, r, borderColor);
    DrawCircleV({ rightTop.x,    rightTop.y    }, r, borderColor);
    DrawCircleV({ rightMiddle.x, rightMiddle.y }, r, borderColor);
    DrawCircleV({ rightBottom.x, rightBottom.y }, r, borderColor);
    DrawCircleV({ leftBottom.x,  leftBottom.y  }, r, borderColor);
    
    // Message
    DrawTextStyled(message, { rectangle.x + padIn.x, rectangle.y + padIn.y });

    return { hover, pressed };
}

void GuiSliderBar(Rectangle bounds, const TextStyle& textLeft, const TextStyle& textRight, float *value, float minValue, float maxValue, Color color) {    
    float padText = 20.0f; // espace entre texte et barre
    float borderThick = 3.0f;

    // --- Calcul des tailles des textes
    Size2D leftSize  = MeasureTextStyled(textLeft);
    Size2D rightSize = MeasureTextStyled(textRight);

    float centerY = bounds.y + bounds.height / 2.0f;

    // --- Positionnement des textes ---
    // Texte gauche
    Position2D leftPos = {
        bounds.x - leftSize.x - padText,
        centerY - leftSize.y / 2.0f
    };
    DrawTextStyled(textLeft, leftPos);

    // Texte droite
    Position2D rightPos = {
        bounds.x + bounds.width + padText,
        centerY - rightSize.y / 2.0f
    };
    DrawTextStyled(textRight, rightPos);

    // --- Positionnement de la barre ---
    Rectangle sliderBounds = bounds;
    DrawRectangleLinesEx(sliderBounds, borderThick, color);

    // --- Calcul de la position du curseur ---
    float t = (*value - minValue) / (maxValue - minValue);
    if (t < 0) t = 0;
    if (t > 1) t = 1;

    // Curseur
    Rectangle cursorBounds = {
        sliderBounds.x + borderThick,
        sliderBounds.y + borderThick,
        t * (sliderBounds.width - 2.0f * borderThick),
        sliderBounds.height - 2.0f * borderThick
    };
    DrawRectangleRec(cursorBounds, Darken(color));

    // --- Interaction souris ---
    static float *activeSlide = nullptr;
    Position2D mouse = GetMousePosition();

    // On commence à drag que si le clic démarre dans la barre
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse, sliderBounds)) activeSlide = value;

    // On arrête de drag à la fin du clic
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) activeSlide = nullptr;

    if (activeSlide == value) {
        float mouseRel = GetMouseX() - sliderBounds.x;
        float percent = mouseRel / sliderBounds.width;

        if (percent < 0) percent = 0;
        if (percent > 1) percent = 1;

        *value = minValue + percent * (maxValue - minValue);
    }
}

void DrawInfoPanel(const TextStyle& title, const vector<InfoPanel>& content, Padding padIn, float roundness, int segments) {
    // ---- Calcul de la taille ----
    Size2D titleSize = MeasureTextStyled(title);

    float separatorPadY   = 10.0f;
    float separatorHeight = 3.0f;

    float maxContentWidth = 0.0f;
    float totalContentHeight = 0.0f;

    float valuePadX = padIn.x + 10.0f;

    // Mesure du contenu
    for (const auto& c : content) {
        Size2D subtitleSize = MeasureTextStyled(c.subTitle);

        // Mesure des valeurs
        float lineWidth = 0.0f;
        float lineHeight = 0.0f;

        for (const auto& v : c.values) {
            Size2D vSize = MeasureTextStyled(v);
            lineWidth  += vSize.x + valuePadX;
            lineHeight = fmaxf(lineHeight, vSize.y);
        }

        // Largeur du bloc
        float blockWidth = fmaxf(subtitleSize.x, valuePadX + lineWidth);
        maxContentWidth  = fmaxf(maxContentWidth, blockWidth);

        // Hauteur du bloc
        float blockHeight = subtitleSize.y + c.subTitle.lineSpacing + lineHeight + c.subTitle.lineSpacing;
        totalContentHeight += blockHeight;
    }

    // Taille final
    float frameWidth  = fmaxf(titleSize.x, maxContentWidth) + 2.0f * padIn.x;
    float frameHeight = padIn.y + titleSize.y + separatorPadY + separatorHeight + separatorPadY + totalContentHeight + padIn.y;
    Frame frame = {
        10.0f,     // En haut a gauche
        10.0f,     // 
        frameWidth,
        frameHeight
    };

    // Le fond
    DrawRectangleRounded(frame, roundness, segments, COLOR_INFO_PANEL_BACKGROUND);
    
    // Le titre
    Position2D titlePosition = {
        frame.x + frame.width / 2.0f - titleSize.x / 2.0f,
        frame.y + padIn.y
    };
    DrawTextStyled(title, titlePosition);

    // La barre
    Rectangle separatorPosition = {
        frame.x + padIn.x,
        titlePosition.y + titleSize.y + separatorPadY,
        frame.width - 2.0f * padIn.x,
        separatorHeight
    };
    DrawRectangleRounded(separatorPosition, 1.0f, segments, COLOR_INFO_PANEL_SEPARATOR_LINE);

    // Le contenu
    Position2D subtitlePosition = {
        frame.x + padIn.x,
        separatorPosition.y + separatorPosition.height + separatorPadY
    };

    for (const auto& c : content) {
        // Sous-titre
        Size2D subtitleSize = MeasureTextStyled(c.subTitle);
        DrawTextStyled(c.subTitle, subtitlePosition);

        // Position de départ des valeurs
        Position2D valuePos = {
            frame.x + padIn.x + valuePadX,
            subtitlePosition.y + subtitleSize.y + c.subTitle.lineSpacing
        };

        float valuesHeight = 0.0f;
        // Valeurs sur une ligne
        for (const auto& v : c.values) {
            Size2D vSize = MeasureTextStyled(v);
            DrawTextStyled(v, valuePos);
            valuesHeight = fmaxf(valuesHeight, vSize.y);

            // On avance en X pour la prochaine valeur
            valuePos.x += vSize.x + valuePadX;
        }

        // On descend pour le prochain InfoPanel
        subtitlePosition.y = valuePos.y + valuesHeight + c.subTitle.lineSpacing;
    }
}
