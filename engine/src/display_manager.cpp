#include "display_manager.hpp"
#include "raylib.h"
#include <cmath>


void displayManager::initCanvas()
{
    canvas = LoadRenderTexture(canvasWidth, canvasHeight);
    SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT);
}

void displayManager::scaleWindow()
{
    if(!PIXEL_PERFECT) 
    {
        scale = fminf((float)GetScreenWidth()/canvasWidth, (float)GetScreenHeight()/canvasHeight);
    }
    else{
        int scaleX = GetScreenWidth() / canvasWidth;
        int scaleY = GetScreenHeight() / canvasHeight;
        scale = (int)(scaleX < scaleY) ? scaleX : scaleY;
        if(scale < 1) scale = 1;
    }
    

    fit = {(float)(canvasWidth * scale), (float)(canvasHeight * scale)};
    offsetX = (GetScreenWidth() - (int)fit.x)/2;
    offsetY = (GetScreenHeight() - (int)fit.y)/2;
};

void displayManager::drawCanvasOnScreen() const {
    Rectangle srcRec = {0,0,(float)getCanvasWidth(), -(float)getCanvasHeight()};
    Rectangle desRec = {(float)getOffsetX(), (float)getOffsetY(), (float)getFit().x, (float)getFit().y};
    DrawRectangle(offsetX, offsetY, fit.x, fit.y, {26,26,26,255});

    DrawTexturePro(canvas.texture, srcRec, desRec, {0,0}, 0, WHITE);

}

void displayManager::unloadCanvas()
{
    UnloadRenderTexture(canvas);
}

displayManager::displayManager()
{
}

displayManager::~displayManager()
{
}