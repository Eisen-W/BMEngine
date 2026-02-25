#pragma once
#include<raylib.h>
#include "anim_manager.hpp"

class Intro{
    public:
    void Init();
    void Update();
    void Draw();
    bool Engineintro;

    Texture2D intro_texture;
    Animation anim_intro;
    Animation::anim_values intro_animValue;
    Animation::anim_Type intro_animType;


    private:
    int count;
    const char* engineTitle;
    int textSize;
    //Music chirp;
};