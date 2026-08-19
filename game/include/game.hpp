#pragma once

#include "screen_ex.hpp"
class Game{
    public:
    void Init();
    void Update();
    void Draw();

    bool gameNotReady = 1;

    private:
    ScreenEx1 screen1;
    ScreenEx2 screen2;
};