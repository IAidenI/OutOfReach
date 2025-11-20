#ifndef STYLE_H
#define STYLE_H

#include "geometry.hpp"
#include <string>
#include <cstdint>
#include <stdio.h>
#include <sstream>

// ---- Style pour les textes ----
struct TextStyle {
    const Font *font;
    string text;
    float fontSize;
    float spacing;
    float lineSpacing;
    Color color;
};

inline void DrawTextStyled(const TextStyle& data, Position2D position) {
    DrawTextEx(*data.font, data.text.c_str(), position, data.fontSize, data.spacing, data.color);
}

inline Size2D MeasureTextStyled(const TextStyle& data) {
    float maxWidth   = 0.0f;
    float lineHeight = 0.0f;
    int   lineCount  = 0;

    std::stringstream ss(data.text);
    std::string line;

    while (std::getline(ss, line, '\n')) {
        Vector2 s = MeasureTextEx(*data.font, line.c_str(), data.fontSize, data.spacing);

        maxWidth   = std::max(maxWidth, s.x);
        lineHeight = std::max(lineHeight, s.y);
        lineCount++;
    }

    if (lineCount == 0) return {0.0f, 0.0f};

    float totalHeight = lineCount * lineHeight + (lineCount - 1) * data.lineSpacing;

    return { maxWidth, totalHeight };
}

struct InfoSegment {
    TextStyle textStyle;
    size_t offset = SIZE_MAX;
};

#endif // STYLE_H
