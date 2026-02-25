#include "intro.hpp"
#include "engine.hpp"

void Intro::Init()
{
    Engineintro = 1;
    count = 0;
    engineTitle = "EWEngine";

    intro_texture = EWE.AM.getTexture("../assets/ShootingRun.png");
    intro_animType = Animation::anim_Type::REPEATING;
    intro_animValue = {0,6,0, 0.1f,0.1f, intro_animType};
    
    //chirp = EWE.AM.getMusic("../assets/chirp - c418.mp3");
    //PlayMusicStream(chirp);
}

void Intro::Update()
{
    //UpdateMusicStream(chirp);
    anim_intro.anim_Update(&intro_animValue);
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
    DrawTexturePro(intro_texture, anim_intro.anime_frame(&intro_animValue, 6, 48), 
                    {10,10,100,100}, {0,0}, 0.0f, WHITE);
    textSize = MeasureText(engineTitle, 80);
    DrawText(engineTitle, textSize/3, textSize/2, 80, WHITE);
}