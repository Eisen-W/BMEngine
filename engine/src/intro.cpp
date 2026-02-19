#include "intro.hpp"
#include "engine.hpp"

void Intro::Init()
{
    Engineintro = 1;
    count = 0;
    engineTitle = "EWEngine";

    //chirp = EWE.AM.getMusic("../assets/chirp - c418.mp3");
    //PlayMusicStream(chirp);
}

void Intro::Update()
{
    //UpdateMusicStream(chirp);
    count++;
    if(count == 20*60)
    {
        Engineintro = 0;
        count = 0;
        //StopMusicStream(chirp);
    }
}

void Intro::Draw()
{
    textSize = MeasureText(engineTitle, 80);
    DrawText(engineTitle, textSize/3, textSize/2, 80, WHITE);
}