#include "playgame.hpp"
#include "engine.hpp"
#include<raylib.h>

#include "anim_example.hpp"

void Play::playgame()
{
    Example EG;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(EWE.DM.getWWidth(), EWE.DM.getWHeight(), "ツバサ");
    SetTargetFPS(60);
    InitAudioDevice();

    EWE.DM.initCanvas();
    EWE.intro.Init();

    EG.Init();
    
    //Gctx.game.changeGameState(GameState::TITLE);

    while(!WindowShouldClose())
    {
        //UPDATE
        EWE.DM.scaleWindow();

        //if(!Gctx.game.Update()) break;
        if(DEV_MODE) EWE.dbg.Update();
        if(EWE.intro.Engineintro) EWE.intro.Update();
        EG.Update();
            

        //TEXTURE MODE
        BeginTextureMode(EWE.DM.getCanvas());
        ClearBackground(BLACK);
        DrawRectangle(0,0,EWE.DM.getCanvasWidth(), EWE.DM.getCanvasHeight(), SKYBLUE);
        if(EWE.intro.Engineintro) EWE.intro.Draw();
        EG.Draw();
        //Gctx.game.Draw();
        EndTextureMode();

        //DRAWING
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
    CloseAudioDevice();
    CloseWindow();
    printf("after close\n");
}