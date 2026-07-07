#pragma once
#include "asset_manager.hpp"
#include "jpfont.hpp"
#include "raylib.h"

namespace GlobalFont{
    inline assetManager& getAM()
    {
        static assetManager am;
        return am;
    }

    inline Font EngineFont()
        {
            if(!lang_JP) return GetFontDefault();
            auto codepoints = JPFont::GetCodePoints();
            return getAM().getFontEx("../assets/JF-Dot-Shinonome16.ttf", 16, codepoints);
        }
}
