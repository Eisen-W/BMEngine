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
    InitWindow(BME.DM.getWWidth(), BME.DM.getWHeight(), game.WindowName.c_str());
    SetTargetFPS(60);
    
    if(game.devCfg.USE_AUDIO) InitAudioDevice();

    BME.DM.addCanvas(game.gamecanvasCfg.gameCanvasName, 
        game.gamecanvasCfg.cWidth, game.gamecanvasCfg.cHeight);

    //BME.DM.initCanvas();  // default canvas

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

    if(DEV_MODE && game.devCfg.DEBUG_VIEW) BME.dbg.Update();
}

void Play::Canvas()
{
    //TEXTURE MODE
    BeginTextureMode(BME.DM.getCanvas(game.gamecanvasCfg.gameCanvasName));
    ClearBackground(BLACK);

    DrawRectangle(0,0,
        BME.DM.getCanvasWidth(BME.DM.getCanvasIndex(game.gamecanvasCfg.gameCanvasName)),
        BME.DM.getCanvasHeight(BME.DM.getCanvasIndex(game.gamecanvasCfg.gameCanvasName)),
        RED
    );

    if(BME.intro.Engineintro) BME.intro.Draw();
    else if(!game.gameNotReady) 
    {
        game.Draw(renderer);
        renderer.RenderLayers();
    }
    BME.TB.Draw(renderer);
    EndTextureMode();
}

void Play::Draw()
{
    //DRAWING
    BeginDrawing();
    ClearBackground(BLACK);
    BME.DM.drawCanvasOnScreen(BME.DM.getCanvasIndex(game.gamecanvasCfg.gameCanvasName));

    if(DEV_MODE && game.devCfg.DEBUG_VIEW) BME.dbg.Draw();
    EndDrawing();
}

void Play::Unload()
{
    printf("before unload\n");
    BME.AM.unloadAssets();
    BME.DM.unloadCanvas();
    printf("after unload\n");

    if(game.devCfg.USE_AUDIO) CloseAudioDevice();
    CloseWindow();

    printf("after close\n");
}
