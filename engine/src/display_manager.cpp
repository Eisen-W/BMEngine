#include "display_manager.hpp"
#include "raylib.h"
#include <cmath>
#include <stdexcept>

displayManager::displayManager() {}
displayManager::~displayManager() {}

void displayManager::initCanvas()
{
    canvases.emplace_back();
    CanvasEntry& main = canvases.back();
    main.id = "game";
    main.width = canvasWidth;
    main.height = canvasHeight;

    main.texture = LoadRenderTexture(canvasWidth, canvasHeight);
    SetTextureFilter(main.texture.texture, TEXTURE_FILTER_POINT);
}

int displayManager::addCanvas(const std::string& id, int w, int h)
{
    canvases.emplace_back();
    CanvasEntry& entry = canvases.back();
    entry.id = id;
    entry.width = w;
    entry.height = h;
    entry.texture = LoadRenderTexture(w,h);
    SetTextureFilter(entry.texture.texture, TEXTURE_FILTER_POINT);

    return (int)canvases.size() - 1;
}

void displayManager::removeCanvas(int index)
{
    if(index == 0) return;
    if(index < 0 || index >= (int)canvases.size()) return;
    UnloadRenderTexture(canvases[index].texture);
    canvases.erase(canvases.begin() + index);
}

void displayManager::unloadCanvas()
{
    for(auto& c : canvases) {UnloadRenderTexture(c.texture);}
    canvases.clear();
}

const RenderTexture2D& displayManager::getCanvas(int index) const
{
    return canvases.at(index).texture;
}

const RenderTexture2D& displayManager::getCanvas(const std::string& id) const
{
    for(auto& c : canvases)
    {
        if(c.id == id) return c.texture;
    }
    throw std::runtime_error("Canvas not found: " + id);
}

int displayManager::getCanvasIndex(const std::string& id) const
{
    for(int i = 0; i < (int)canvases.size(); i++)
    {
        if(canvases[i].id == id) return i;
    }
    return -1;
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

void displayManager::drawCanvasOnScreen(int index) const 
{
    const auto& c = canvases.at(index);
    Rectangle srcRec = {0,0,(float)c.width, -(float)c.height};
    Rectangle desRec = {(float)getOffsetX(), (float)getOffsetY(), fit.x, fit.y};
    DrawRectangle(offsetX, offsetY, fit.x, fit.y, {26,26,26,255});

    DrawTexturePro(c.texture.texture, srcRec, desRec, {0,0}, 0, WHITE);

}

void displayManager::drawCanvasAt(int index, Rectangle dest) const
{
    const auto& c = canvases.at(index);
    Rectangle srcRec = {0,0, (float)c.width, -(float)c.height};
    DrawTexturePro(c.texture.texture, srcRec, dest, {0, 0}, 0, WHITE);
}
