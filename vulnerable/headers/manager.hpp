#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <vector>
#include "geometry.hpp"
using namespace std;

// ---- Structure texture/font ----
inline constexpr const char *INFO_FONT_PATH              = "assets/fonts/Inconsolata-Regular.ttf";
inline constexpr const int   FONT_SIZE_COUNT             = 4;
inline constexpr const int   FONT_SIZES[FONT_SIZE_COUNT] = { 20, 30, 50, 120 };

// ASCII + accents FR courants
static const char32_t FR_CHARS[] = U" !\"#$%&'()*+,-./0123456789:;<=>?@°"
                                   U"ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"
                                   U"abcdefghijklmnopqrstuvwxyz{|}~"
                                   U"àâäçéèêëîïôöùûüÿÀÂÄÇÉÈÊËÎÏÔÖÙÛÜŸ’«»œŒ";

enum TextureID {
    // Sentinelle pour savoir la taille
    TEX_MAX
};

enum FontID {
    INFO_FONT,
    // Sentinelle pour savoir la taille
    FONT_MAX
};

// ---- Assets ----

bool CheckFileExiste(const char *path);

class Manager {
    private:
        bool valid = true;

        Texture2D tmgr[TEX_MAX];
        Font fmgr[FONT_MAX][FONT_SIZE_COUNT];

        // ---- Textures/Fonts ----
        const char *textures[TEX_MAX] = {};

        const char *fonts[FONT_MAX] = {
            INFO_FONT_PATH
        };
    public:
        bool init();

        Texture2D getTexture(TextureID id) const { return this->tmgr[id]; }
        const Font& getFont(FontID id, int size);

        ~Manager();
};

#endif // MANAGER_H
