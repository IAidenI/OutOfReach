#ifndef DEFAULT_CONSTANTS_H
#define DEFAULT_CONSTANTS_H

#include "geometry.hpp"

// ---- Fonts ----
inline constexpr float DEFAULT_MENU_TITLE_SIZE  = 120.0f;
inline constexpr float DEFAULT_MENU_BUTTON_SIZE = 64.0f;

// ---- Cubes ----
inline constexpr Position3D DEFAULT_CUBE_SIZE = { 10.0f, 10.0f, 10.0f };
inline constexpr Color DEFAULT_CUBE_COLOR = BLUE;

// ---- Padding
inline constexpr Padding DEFAULT_PAD_IN        = { 10.0f, 10.0f };
inline constexpr Padding DEFAULT_PAD_IN_3D     = { 0.2f, 0.2f };
inline constexpr Margins DEFAULT_PAD_OUT       = { 15.0f, 15.0f };
inline constexpr float   DEFAULT_INTERLINE     = 5.0f;

// ---- Rounded rectangle ----
inline constexpr float   DEFAULT_ROUNDNESS     = 0.12f;
inline constexpr int     DEFAULT_SEGMENTS      = 32;
inline constexpr float   DEFAULT_STROKE        = 2.0f;

// ---- Bouton ----
inline constexpr float   DEFAULT_BORDER_THICK  = 5.0f;
inline constexpr float   DEFAULT_ARROW_SIZE    = 40.0f;

#endif // DEFAULT_CONSTANTS_H
