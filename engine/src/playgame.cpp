#include "playgame.hpp"
#include "constants.hpp"
#include "engine.hpp"
#include<raylib.h>

#include "game.hpp"
#include "globalfont.hpp"


void Play::playgame()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(EWE.DM.getWWidth(), EWE.DM.getWHeight(), "EWE");
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
        float dt = GetFrameTime();
        //UPDATE
        if(IsWindowResized()) EWE.DM.scaleWindow();

        if(EWE.intro.Engineintro) EWE.intro.Update();
        else if(!game.gameReady && gamestate == GameState::PLAY) game.Update();
        else if(gamestate == GameState::MESSAGE)
        {
            EWE.MB.Update(dt);
            if(!EWE.MB.isActive())
            {
                EWE.MB.HandleMB();
            }
        }
        if(DEV_MODE) EWE.dbg.Update();
        
            

        //TEXTURE MODE
        BeginTextureMode(EWE.DM.getCanvas());
        ClearBackground(BLACK);
        DrawRectangle(0,0,EWE.DM.getCanvasWidth(), EWE.DM.getCanvasHeight(), BLACK);
        if(EWE.intro.Engineintro) EWE.intro.Draw();
        else if(!game.gameReady) 
        {
            game.Draw();
        }
        EWE.MB.Draw();
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
    GlobalFont::getAM().unloadAssets();
    EWE.DM.unloadCanvas();
    printf("after unload\n");
    CloseAudioDevice();
    CloseWindow();
    printf("after close\n");
}
