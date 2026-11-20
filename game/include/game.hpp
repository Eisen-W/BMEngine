#pragma once

#include "screen_ex.hpp"

// to be used in playgame ==============================
struct DevConfigs
{
    static constexpr bool DEBUG_VIEW = true;
    static constexpr bool USE_AUDIO = false;
};

struct GameCanvasConfigs
{
    int cWidth = 320;
    int cHeight = 320;
    std::string gameCanvasName = "gamecanvas"; 
};
// ======================================================

class Game{
    public:
    DevConfigs devCfg;
    GameCanvasConfigs gamecanvasCfg;

    std::string WindowName = "BME";

    void Init();
    void Update();
    void Draw(Renderer& r);

    bool gameNotReady = 1;

    private:
    ScreenEx1 screen1;
    ScreenEx2 screen2;
};