#include "intro.hpp"
#include <cstdio>
//#include "engine.hpp"

void Intro::Init()
{
    Engineintro = 0;
    count = 0;
    engineTitle = "BMEngine";
    timer = 0.0f;
    speed = 150.0f;
    revealedPixels = 0;
    textSize = MeasureText(engineTitle, 80);
    printf("intro init\n");
    
}

void Intro::Update()
{
    timer += GetFrameTime();
    revealedPixels = (int)(timer * speed);
    if(revealedPixels > textSize) revealedPixels = textSize;

    count++;
    if(count == 3*60)
    {
        Engineintro = 0;
        count = 0;
    }
}

void Intro::Draw()
{
    //DrawText(engineTitle, textSize/3, textSize/2, 80, WHITE);
    
    int offsetX = 0;
    for(int j = 0; engineTitle[j] != '\0'; j++)
    {
        char single[2] = { engineTitle[j], '\0'};
        int charWidth = MeasureText(single, 80);

        if(offsetX >= revealedPixels) break;
        DrawText(single, textSize/5 + offsetX, textSize/2, 80, WHITE);
        offsetX += charWidth + 5;
    }
} 
