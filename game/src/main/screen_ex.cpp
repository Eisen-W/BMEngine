// EXAMPLE SCREEN
// Delete it or repurpose it

#include "screen_ex.hpp"
#include "constants.hpp"
#include "engine.hpp"
#include "engine_constants.hpp"
#include "messagebox.hpp"
#include "raylib.h"
#include "renderer.hpp"

// ============= SCREEN 1 ====================
void ScreenEx1::Init()
{
    // Init Values
    loadmadfiles = false;
    if(loadmadfiles)
    {
        BME.madloader.FLoad("../assets/msg.mad");
        BME.FaceSM.texture = BME.AM.getTexture("../assets/face.png");
        BME.FaceSM.registerFace("EisenW", {0,0,16,16});
    }
    

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

    if(IsKeyPressed(KEY_ENTER))
    {
        TextBoxConfig cfg;
        //cfg.box = {50,50,300, 100};
        cfg.slice.texture = BME.AM.getTexture("../assets/textboxnslice.png");
        cfg.slice.active = true;
        cfg.slice.npatch.source = {0,0,32,32};

        int npx = 8;
        cfg.slice.npatch.left = cfg.slice.npatch.bottom = cfg.slice.npatch.right = cfg.slice.npatch.top = npx;
        cfg.slice.npatch.layout = NPATCH_NINE_PATCH;

        BME.TB.Start(BME.EUtils.processString("custom box"), "",
        false, {}, {}, cfg
        );

    }
    float dt = GetFrameTime();
    BME.TB.Update(dt);
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

void ScreenEx1::Draw(Renderer& r)
{
    r.Submit(Layer::BACKGROUND, 
        [&]()
        {
            DrawRectangle(0,0, 640, 480, LIME);
        }
    );

    levelmap.Draw(r);
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

void ScreenEx2::Draw(Renderer& r)
{
    r.Submit(Layer::VISUAL_BG, 
        [&]()
        {
            DrawRectangle(0,0, 640, 480, SKYBLUE);
        }
    );
}