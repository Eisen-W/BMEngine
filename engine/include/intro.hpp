#pragma once
#include<raylib.h>
#include "anim_manager.hpp"

class Intro{
    public:
    void Init();
    void Update();
    void Draw();
    bool Engineintro = 1;

    Texture2D intro_texture;
    Animation anim_intro;
    Animation::anim_values intro_animValue;
    Animation::anim_Type intro_animType;


    private:
    int count = 0;
    const char* engineTitle = "";
    int textSize = 0;
    int revealedPixels = 0;
    float timer = 0;
    float speed = 0;
};