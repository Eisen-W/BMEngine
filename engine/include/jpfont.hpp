#pragma once 
#include <vector>

inline constexpr bool lang_JP = true;
inline constexpr bool JP_Kanji = false;

namespace JPFont {
    inline std::vector<int> GetCodePoints()
    {
        std::vector<int> codepoints;
        for(int i = 32; i < 127; i++) codepoints.push_back(i);          //ascii
        for(int i = 0x3040; i <= 0x309F; i++) codepoints.push_back(i);  //hiragana
        for(int i = 0x30A0; i <= 0x30FF; i++) codepoints.push_back(i);  //katakana
        if(JP_Kanji) { for(int i = 0x4E00; i <= 0x9FA0; i++) codepoints.push_back(i); }  //kanji
        return codepoints;
    }
}