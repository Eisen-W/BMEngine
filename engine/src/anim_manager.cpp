#include "anim_manager.hpp"

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

Rectangle Animation::anim_frame(anim_values *self, int frames_per_row, int tileset_px)
{
    int x = (self->curr % frames_per_row) * tileset_px;
    int y = (self->curr / frames_per_row) * tileset_px;
    return Rectangle {(float)x, (float)y, (float)tileset_px, (float)tileset_px};
}
