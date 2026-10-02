#include "playgame.hpp"
#include "constants.hpp"
#include "engine.hpp"
#include<raylib.h>

#include "game.hpp"


void Play::playgame()
{
    // Init
    Init();

    // Main window loop
    while(!WindowShouldClose())
    {
        float dt = GetFrameTime();
        // Update
        Update(dt);
        
        // Drawing
        Canvas();
        Draw();
    }
    Unload();
}


void Play::Init()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(BME.DM.getWWidth(), BME.DM.getWHeight(), "BME");
    SetTargetFPS(60);
    InitAudioDevice();

    BME.DM.initCanvas();
    BME.DM.scaleWindow();
    BME.intro.Init();

    game.Init();
}

void Play::Update(float dt)
{
    if(IsWindowResized()) BME.DM.scaleWindow();

    if(BME.intro.Engineintro) BME.intro.Update();
    else if(!game.gameNotReady && gamestate == GameState::PLAY) game.Update();
    else if(gamestate == GameState::MESSAGE)
    {
        BME.TB.Update(dt);
        if(!BME.TB.isActive())
        {
            BME.TB.HandleTB();
        }
    }

    if(DEV_MODE) BME.dbg.Update();
}

void Play::Canvas()
{
    //TEXTURE MODE
    BeginTextureMode(BME.DM.getCanvas());
    ClearBackground(BLACK);
    DrawRectangle(0,0,BME.DM.getCanvasWidth(), BME.DM.getCanvasHeight(), RED);
    if(BME.intro.Engineintro) BME.intro.Draw();
    else if(!game.gameNotReady) 
    {
        game.Draw();
    }
    BME.TB.Draw();
    EndTextureMode();
}

void Play::Draw()
{
    //DRAWING
    BeginDrawing();
    ClearBackground(BLACK);
    BME.DM.drawCanvasOnScreen(0);

    if(DEV_MODE) BME.dbg.Draw();
    EndDrawing();
}

void Play::Unload()
{
    printf("before unload\n");
    BME.AM.unloadAssets();
    BME.DM.unloadCanvas();
    printf("after unload\n");
    CloseAudioDevice();
    CloseWindow();
    printf("after close\n");
}
