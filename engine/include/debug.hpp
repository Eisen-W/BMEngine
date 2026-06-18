#pragma once
#include<raylib.h>
#include<sys/resource.h>


inline constexpr bool DEV_MODE = true; //set to false for release builds

class Debug
{
private:
    bool enabled = false;
    int memory = 0;
    int colorsUsed = 0;

    int printMemUsage();
    int countColors(const RenderTexture2D& canvas);

    Vector2 cm;

public:
    void Update();
    void Draw();
};