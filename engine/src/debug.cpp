#include "debug.hpp"
#include "engine.hpp"
#include <iostream>
#include<fstream>
#include<string>


int Debug::printMemUsage()
{
    std::ifstream file("/proc/self/status");
    std::string line;

    while (std::getline(file, line)) {
        if (line.rfind("VmRSS:", 0) == 0) {
            std::string value = line.substr(6);
            return std::stoul(value);
        }
    }

    return 0;
}

int Debug::countColors(const RenderTexture2D& canvas)
{
    Image img = LoadImageFromTexture(canvas.texture);

    std::unordered_set<unsigned int> uniqueColors;

    for(int y = 0; y < img.height; y+=4)
    for(int x = 0; x < img.width; x+=4)
    {
        Color c = GetImageColor(img, x, y);

        unsigned int key = (c.r << 24) | (c.g << 16) | (c.b << 8) | c.a;
        uniqueColors.insert(key);
    }
    UnloadImage(img);

    return (int)uniqueColors.size();
}

void Debug::Update()
{
    if(!DEV_MODE) return;

    memory = printMemUsage();
    /*
    static int frameCount = 0;
    frameCount++;
    if(frameCount % 120 == 0)
    {
        colorsUsed = countColors(DM.getCanvas());
    }
    */
    cm = EWE.mousepoint.CMouse;

    if(IsKeyPressed(KEY_TAB)) enabled = !enabled;
}

void Debug::Draw()
{
    if(!DEV_MODE || !enabled) return;

    int FS = 20;
    int xpos = 10;


    DrawText(TextFormat("FPS: %d", GetFPS()), xpos,10, FS, WHITE);
    DrawText(TextFormat("Gamepad: %s", GetGamepadName(0)), xpos,30, FS, WHITE);
    DrawText(TextFormat("memory: %d mb", memory/1024), xpos, 50, FS, WHITE);
    DrawText(TextFormat("frame time: %.2f ms", GetFrameTime() * 1000.0f), xpos,70, FS, WHITE);
    DrawText(TextFormat("%d", (int)GetTime()), xpos, 90, FS, WHITE);
    DrawText(TextFormat("Colors = %d", colorsUsed), xpos, 110, FS, WHITE);
    
    DrawText(TextFormat("CMouse: x:%.2f y:%.2f", cm.x, cm.y), xpos, 150, FS, WHITE);

}