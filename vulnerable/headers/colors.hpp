#ifndef COLOR_H
#define COLOR_H

#include "geometry.hpp"

inline constexpr Color COLOR_INVENTORY_BACKGROUND    = CLITERAL(Color){  84,  61,  89, 255 };
inline constexpr Color COLOR_VALUE_HOOVER            = CLITERAL(Color){  24,  76,  66, 255 };

// ---- Commandes ----
inline constexpr Color COLOR_COMMANDS_BACKGROUND = CLITERAL(Color){  12,  17,  20, 178 };
inline constexpr Color COLOR_COMMANDS_BORDER     = BLACK;
inline constexpr Color COLOR_COMMANDS_LABEL      = CLITERAL(Color){  92, 197, 184, 255 };
inline constexpr Color COLOR_COMMANDS_ACTION     = CLITERAL(Color){ 255, 255, 255, 178 };

// ---- Menu ----
inline constexpr Color COLOR_MENU_START_BACKGROUND  = CLITERAL(Color){  27,  26,  23, 255 };
inline constexpr Color COLOR_MENU_PAUSE_BACKGROUND  = CLITERAL(Color){ 255, 255, 255,  64 };
inline constexpr Color COLOR_MENU_TITLE             = CLITERAL(Color){ 232, 159,  84, 255 };
inline constexpr Color COLOR_MENU_TEXT              = CLITERAL(Color){ 232, 159,  84, 255 };

inline constexpr Color COLOR_MENU_BUTTON_BACKGROUND = CLITERAL(Color){  74,  66,  56, 255 };
inline constexpr Color COLOR_MENU_BUTTON_BORDER     = CLITERAL(Color){ 202, 126,  60, 255 };
inline constexpr Color COLOR_MENU_BUTTON_TEXT       = CLITERAL(Color){ 255, 233, 199, 255 };

// ---- Info panel ----
inline constexpr Color COLOR_INFO_PANEL_BACKGROUND     = CLITERAL(Color){  46,  43,  38, 255 };
inline constexpr Color COLOR_INFO_PANEL_TITLE          = CLITERAL(Color){ 232, 159,  84, 255 };
inline constexpr Color COLOR_INFO_PANEL_SUB_TITLE      = CLITERAL(Color){ 202, 126,  60, 255 };
inline constexpr Color COLOR_INFO_PANEL_SEPARATOR_LINE = CLITERAL(Color){ 241, 144,  72, 255 };
inline constexpr Color COLOR_INFO_PANEL_VALUE          = CLITERAL(Color){ 255, 233, 199, 255 };


// ---- Hover ----
inline constexpr float DEFAULT_HOVER_AMOUNT = 0.20f;
inline Color Lighten(Color c, float amount = DEFAULT_HOVER_AMOUNT) {
    Color out;
    out.r = c.r + (255 - c.r) * amount;
    out.g = c.g + (255 - c.g) * amount;
    out.b = c.b + (255 - c.b) * amount;
    out.a = c.a;
    return out;
}

inline Color Darken(Color c, float amount = DEFAULT_HOVER_AMOUNT) {
    Color out;
    out.r = c.r * (1.0f - amount);
    out.g = c.g * (1.0f - amount);
    out.b = c.b * (1.0f - amount);
    out.a = c.a;
    return out;
}

#endif // COLOR_H
