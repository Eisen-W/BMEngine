// EXAMPLE SCREEN
// Delete it or repurpose it

#include "screen_ex.hpp"
#include "engine.hpp"
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
    if(!BME.TB.isActive())
    {
      BME.EUtils.checkAutoDialogue({0,0,640,480});
    }

}

void ScreenEx1::Draw()
{
    DrawRectangle(0,0, 640, 480, PINK);
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