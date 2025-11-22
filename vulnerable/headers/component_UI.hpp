#ifndef COMPONENT_UI
#define COMPONENT_UI

#include "geometry.hpp"
#include "style.hpp"
#include "colors.hpp"

struct ButtonResult {
    bool hover;
    bool pressed;
};

Size2D GetMenuButtonSize(const TextStyle& message, Padding padIn = DEFAULT_PAD_IN);
ButtonResult DrawMenuButton(const TextStyle& message, Position2D position, Padding padIn = DEFAULT_PAD_IN, float borderThick = DEFAULT_BORDER_THICK, Color bgColor = COLOR_MENU_BUTTON_BACKGROUND, Color borderColor = COLOR_MENU_BUTTON_BORDER);
void GuiSliderBar(Rectangle bounds, const TextStyle& textLeft, const TextStyle& textRight, float *value, float minValue, float maxValue, Color color);

#endif // COMPONENT_UI