// EXAMPLE SCREEN
// Delete it or repurpose it

#include "screen_ex.hpp"
#include "constants.hpp"
#include "engine.hpp"
#include "engine_constants.hpp"
#include "raylib.h"

// ============= SCREEN 1 ====================
void ScreenEx1::Init()
{
    // Init Values
    /*
    BME.madloader.FLoad("../assets/msg.mad");
    BME.FaceSM.texture = BME.AM.getTexture("../assets/face.png");
    BME.FaceSM.registerFace("EisenW", {0,0,16,16});
    */
    levelmap.LoadFiles({
                    {"../assets/TOWN_visualBG.csv",MapType::VISUAL, Layer::VISUAL_BG},
                    {"../assets/TOWN_visualFG.csv",MapType::VISUAL, Layer::VISUAL_FG},
                    }, 
                    "../assets/sprite-temp.png", 30, 20);
}

void ScreenEx1::Update()
{
    // Screen switching logic
    if(closeScreen) { closeScreen = false;}
    if(IsKeyPressed(KEY_SPACE))
    {
        nextScreen = "ex2";
        closeScreen = true;
    }

    // actual update logic
    if(IsKeyPressed(KEY_D)) 
    { 
        printf("pressed D\n");
        levelmap.destroyTile(4,6, Layer::VISUAL_BG, MapType::VISUAL);
        levelmap.setTile(4, 7, 2, Layer::VISUAL_BG, MapType::VISUAL);
    }
    if(!BME.TB.isActive())
    {
      BME.EUtils.checkAutoDialogue({0,0,640,480});
    }

}

void ScreenEx1::Draw()
{
    DrawRectangle(0,0, 640, 480, PINK);
    levelmap.Draw();
}

// ============ SCREEN 2 ====================
void ScreenEx2::Init() {}

void ScreenEx2::Update()
{
    if(closeScreen) {closeScreen = false;}
    if(IsKeyPressed(KEY_SPACE))
    {
        nextScreen = "ex1";
        closeScreen = true;
    }
}

void ScreenEx2::Draw()
{
    DrawRectangle(0,0, 640, 480, SKYBLUE);
}