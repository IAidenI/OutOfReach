#ifndef COMPONENT_UI
#define COMPONENT_UI

#include <vector>
#include "geometry.hpp"
#include "default_constants.hpp"
#include "style.hpp"
#include "colors.hpp"
#include "manager.hpp"

struct ButtonResult {
    bool hover;
    bool pressed;
};

struct InfoPanel {
    TextStyle subTitle;
    vector<TextStyle> values;
};

inline TextStyle MakeInfoText(Manager& manager, int size, const char* text, Color color) {
    return TextStyle{
        .font        = &manager.getFont(INFO_FONT, size),
        .text        = text,
        .fontSize    = (float)size,
        .spacing     = 2.0f,
        .lineSpacing = 2.0f,
        .color       = color
    };
}

Size2D GetMenuButtonSize(const TextStyle& message, Padding padIn = DEFAULT_PAD_IN);
ButtonResult DrawMenuButton(const TextStyle& message, Position2D position, Padding padIn = DEFAULT_PAD_IN, float borderThick = DEFAULT_BORDER_THICK, Color bgColor = COLOR_MENU_BUTTON_BACKGROUND, Color borderColor = COLOR_MENU_BUTTON_BORDER);
void GuiSliderBar(Rectangle bounds, const TextStyle& textLeft, const TextStyle& textRight, float *value, float minValue, float maxValue, Color color);
void DrawInfoPanel(const TextStyle& title, const vector<InfoPanel>& content, Padding padIn = DEFAULT_PAD_IN, float roundness = DEFAULT_ROUNDNESS, int segments = DEFAULT_SEGMENTS);

#endif // COMPONENT_UI