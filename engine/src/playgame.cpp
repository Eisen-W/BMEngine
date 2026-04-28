#include "playgame.hpp"
#include "engine.hpp"
#include<raylib.h>

#include "game.hpp"


void Play::playgame()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(EWE.DM.getWWidth(), EWE.DM.getWHeight(), "EWEngine-2D");
    SetTargetFPS(60);
    InitAudioDevice();

    Game game;

    EWE.DM.initCanvas();
    EWE.DM.scaleWindow();
    EWE.intro.Init();

    game.Init();
    //Gctx.game.changeGameState(GameState::TITLE);

    while(!WindowShouldClose())
    {
        //UPDATE
        if(IsWindowResized()) EWE.DM.scaleWindow();

        if(EWE.intro.Engineintro) EWE.intro.Update();
        else if(!game.gameInit) game.Update();
        if(DEV_MODE) EWE.dbg.Update();
        
            

        //TEXTURE MODE
        BeginTextureMode(EWE.DM.getCanvas());
        ClearBackground(BLACK);
        DrawRectangle(0,0,EWE.DM.getCanvasWidth(), EWE.DM.getCanvasHeight(), BLACK);
        if(EWE.intro.Engineintro) EWE.intro.Draw();
        else if(!game.gameInit) game.Draw();
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
