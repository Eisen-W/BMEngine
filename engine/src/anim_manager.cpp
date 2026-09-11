#include "anim_manager.hpp"
#include "raylib.h"

void Animation::anim_Update(anim_values *self)
{
    float dt = GetFrameTime();
    self->duration_left -= dt; 

    if(self->duration_left <= 0.0)
    {
        self->duration_left = self->speed;
        self->curr++;

        if(self->curr > self->last)
        {
            switch(self->type)
            {
                case anim_Type::REPEATING:
                    self->curr = self->first;
                    break;
                
                case anim_Type::ONESHOT:
                    self->curr = self->last;
                    break;
            }
        }
    }
}

Rectangle Animation::anim_frame(anim_values *self, int frames_per_row, int tileWidth, int tileHeight, const std::vector<Rectangle>& customFrames)
{
    if(!customFrames.empty() && self->curr >= 0 && self->curr < (int)customFrames.size())
    {
        const Rectangle& r = customFrames[self->curr];

        if(r.width > 0.0f && r.height > 0.0f) return r;
    }
    
    int x = (self->curr % frames_per_row) * tileHeight;
    int y = (self->curr / frames_per_row) * tileWidth;
    return Rectangle{(float)x, (float)y, (float)tileWidth, (float)tileHeight};
}
