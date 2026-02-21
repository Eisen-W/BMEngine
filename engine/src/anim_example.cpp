#include "anim_example.hpp"
#include "engine.hpp"
#include<iostream>


void Example::anim_update(anim *self)
{
    float dt = GetFrameTime();
    self->duration_left -= dt;

    if(self->duration_left <= 0.0)
    {
        self->duration_left = self->speed;
        self->curr++;

        if(self->curr > self->last)
        {
            self->curr = self->first;
        }
    }
}

Rectangle Example::anim_frame(anim *self, int frames_per_row, int tileset_px)
{
    int x = (self->curr % frames_per_row) * tileset_px;
    int y = (self->curr / frames_per_row) * tileset_px;

    return Rectangle {(float)x, (float)y, (float)tileset_px, (float)tileset_px};
}

void Example::Init()
{
    ShootRunTexture = EWE.AM.getTexture("../assets/ShootingRun.png"); 
    shootrun = {0, 6, 0, 0.1f, 0.1f};
}

void Example::Update()
{
    anim_update(&shootrun);
}

void Example::Draw()
{
    DrawTexturePro(ShootRunTexture, anim_frame(&shootrun, 6, 48), 
                    {10,10,100,100}, {0,0}, 0.0f, WHITE);
}


