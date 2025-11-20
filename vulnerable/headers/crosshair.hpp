#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include "geometry.hpp"
#include <stdio.h>

// ---- Valeurs par défaut ----
inline constexpr float DEFAULT_CROSSHAIR_CIRCLE_RADIUS = 3.0f;
inline constexpr float DEFAULT_CROSSHAIR_SQUARE_SIDE   = 6.0f;
inline constexpr float DEFAULT_CROSSHAIR_CROSS_LENGTH  = 8.0f;
inline constexpr float DEFAULT_CROSSHAIR_CROSS_THICK   = 2.0f;
inline constexpr Color DEFAULT_CROSSHAIR_COLOR         = RED;

class Crosshair {
    private:
        // Position / Taille
        Size2D SCREEN_SIZE;
        Position2D position = { 0.0f, 0.0f };

        // Types de crosshair
        struct Circle {
            float radius;
        };

        struct Square {
            float side;
        };

        struct Cross {
            float length;
            float thickness;
        };

        enum CrosshairShape {
            CROSSHAIR_CIRCLE,
            CROSSHAIR_SQUARE,
            CROSSHAIR_CROSS,
        };

        CrosshairShape type;
        union {
            Circle circle;
            Square square;
            Cross cross;
        } shape;
    
        // Couleur
        Color color;
    public:
        void init(Size2D SCREEN_SIZE);

        void setCircle(float radius = DEFAULT_CROSSHAIR_CIRCLE_RADIUS, Color color = DEFAULT_CROSSHAIR_COLOR);
        void setSquare(float side = DEFAULT_CROSSHAIR_SQUARE_SIDE, Color color = DEFAULT_CROSSHAIR_COLOR);
        void setCross(float length = DEFAULT_CROSSHAIR_CROSS_LENGTH, float thickness = DEFAULT_CROSSHAIR_CROSS_THICK, Color color = DEFAULT_CROSSHAIR_COLOR);

        void nextShape();
        void draw();
};

#endif // CROSSHAIR_H
