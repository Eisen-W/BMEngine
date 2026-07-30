#pragma once
#include<raylib.h>
#include<sys/resource.h>

#ifdef __linux__
#include<sys/resource.h>
#endif


inline constexpr bool DEV_MODE = true; //set to false for release builds

class Debug
{
private:
    bool enabled = false;
    int memory = 0;
    int colorsUsed = 0;

    int printMemUsage();

    int FS = 20;
    int xpos = 10;

public:
    void Update();
    void Draw();
};