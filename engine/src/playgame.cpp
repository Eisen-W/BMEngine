#include "playgame.hpp"
#include "constants.hpp"
#include "engine.hpp"
#include<raylib.h>

#include "game.hpp"


void Play::playgame()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(BME.DM.getWWidth(), BME.DM.getWHeight(), "BME");
    SetTargetFPS(60);
    InitAudioDevice();

    Game game;

    BME.DM.initCanvas();
    BME.DM.scaleWindow();
    BME.intro.Init();

    game.Init();

    //int debugIdx = EWE.DM.addCanvas("debug", 320, 240);

    while(!WindowShouldClose())
    {
        float dt = GetFrameTime();
        //UPDATE
        if(IsWindowResized()) BME.DM.scaleWindow();

        if(BME.intro.Engineintro) BME.intro.Update();
        else if(!game.gameReady && gamestate == GameState::PLAY) game.Update();
        else if(gamestate == GameState::MESSAGE)
        {
            BME.TB.Update(dt);
            if(!BME.TB.isActive())
            {
                BME.TB.HandleTB();
            }
        }
        if(DEV_MODE) BME.dbg.Update();
        

        //TEXTURE MODE
        BeginTextureMode(BME.DM.getCanvas());
        ClearBackground(BLACK);
        DrawRectangle(0,0,BME.DM.getCanvasWidth(), BME.DM.getCanvasHeight(), RED);
        if(BME.intro.Engineintro) BME.intro.Draw();
        else if(!game.gameReady) 
        {
            game.Draw();
        }
        BME.TB.Draw();
        EndTextureMode();

        // Uncomment the code below to render another canvas
        //=================== "DEBUG" TEXTURE MODE ======================
        /*
        BeginTextureMode(BME.DM.getCanvas(debugIdx));
        ClearBackground(BLACK);
        DrawRectangle(0,0, 320,240, GREEN);
        EndTextureMode();
        */
        
        //DRAWING
        BeginDrawing();
        ClearBackground(BLACK);
        BME.DM.drawCanvasOnScreen(0);
        
        // Uncomment the code below to render another canvas
        /*
        BME.DM.drawCanvasAt(debugIdx,
            {GetScreenWidth() - 160.0f, 0, 160, 120});
        */
        if(DEV_MODE) BME.dbg.Draw();
        EndDrawing();
    }
    printf("before unload\n");
    BME.AM.unloadAssets();
    BME.DM.unloadCanvas();
    printf("after unload\n");
    CloseAudioDevice();
    CloseWindow();
    printf("after close\n");
}
