#include "intro.hpp"
#include<raylib.h>

void Intro::Init()
{
    Engineintro = 1;
    count = 0;
    engineTitle = "EWEngine";
}

void Intro::Update()
{
    count++;
    if(count == 10*60)
    {
        Engineintro = 0;
        count = 0;
    }
}

void Intro::Draw()
{
    textSize = MeasureText(engineTitle, 80);
    DrawText(engineTitle, textSize/3, textSize/2, 80, WHITE);
}