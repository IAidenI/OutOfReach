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
    float pad = 20.0f; // espace entre texte et barre
    float borderThick = 3.0f;

    // --- Calcul des tailles des textes
    TextStyle maxTextRight = textRight;
    maxTextRight.text = to_string(maxValue).size() > to_string(minValue).size();
    Size2D leftSize  = MeasureTextStyled(textLeft);
    Size2D rightSize = MeasureTextStyled(maxTextRight);

    float totalTextWidth = leftSize.x + pad + rightSize.x;
    float sliderWidth    = bounds.width - totalTextWidth - pad;

    if (sliderWidth < 20) sliderWidth = 20;

    float centerY = bounds.y + bounds.height / 2.0f;

    // --- Positionnement des textes ---
    // Texte gauche
    Position2D leftPos = {
        bounds.x,
        centerY - leftSize.y / 2.0f
    };
    DrawTextStyled(textLeft, leftPos);

    // Texte droite
    Position2D rightPos = {
        bounds.x + bounds.width - rightSize.x,
        centerY - rightSize.y / 2.0f
    };
    DrawTextStyled(textRight, rightPos);

    // --- Positionnement de la barre ---
    Rectangle sliderBounds = {
        leftPos.x + leftSize.x + pad,
        bounds.y + 5,
        sliderWidth,
        bounds.height - 10
    };

    // Cadre
    DrawRectangleLinesEx(sliderBounds, borderThick, color);

    // --- Calcul de la position du curseur ---
    float t = (*value - minValue) / (maxValue - minValue);
    if (t < 0) t = 0;
    if (t > 1) t = 1;

    // Curseur
    Rectangle cursorBounds = {
        sliderBounds.x + borderThick,
        sliderBounds.y + borderThick,
        t * sliderBounds.width - 2.0f * borderThick,
        sliderBounds.height - 2.0f * borderThick
    };
    DrawRectangleRec(cursorBounds, Darken(color));

    // --- Interaction souris ---
    if ((IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), sliderBounds))) {
        float mouseRel = GetMouseX() - sliderBounds.x;
        float percent = mouseRel / sliderBounds.width;

        if (percent < 0) percent = 0;
        if (percent > 1) percent = 1;

        *value = minValue + percent * (maxValue - minValue);
    }
}
