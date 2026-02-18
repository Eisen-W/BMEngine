#include "playgame.hpp"
#include "engine.hpp"
#include<raylib.h>

void Play::playgame()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(EWE.DM.getWWidth(), EWE.DM.getWHeight(), "ツバサ");
    SetTargetFPS(60);

    EWE.DM.initCanvas();
    EWE.intro.Init();

    
    //Gctx.game.changeGameState(GameState::TITLE);

    while(!WindowShouldClose())
    {
        EWE.DM.scaleWindow();

        //if(!Gctx.game.Update()) break;
        if(DEV_MODE) EWE.dbg.Update();
        if(EWE.intro.Engineintro) EWE.intro.Update();

        BeginTextureMode(EWE.DM.getCanvas());
        ClearBackground(BLACK);
        DrawRectangle(0,0,EWE.DM.getCanvasWidth(), EWE.DM.getCanvasHeight(), SKYBLUE);
        if(EWE.intro.Engineintro) EWE.intro.Draw();
        //Gctx.game.Draw();
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK);
        EWE.DM.drawCanvasOnScreen();
        if(DEV_MODE) EWE.dbg.Draw();
        EndDrawing();
    }
    printf("before unload\n");
    EWE.AM.unloadAssets();
    EWE.DM.unloadCanvas();
    printf("after unload\n");
    CloseWindow();
    printf("after close\n");
}