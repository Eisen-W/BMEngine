#pragma once
#include<raylib.h>


class Animation{
    public:
    enum struct anim_Type{
        REPEATING,
        ONESHOT
    };

    struct anim_values{
        int first;
        int last;
        int curr;

        float speed;
        float duration_left;

        anim_Type type;
    };

    void anim_Update(anim_values *self);
    Rectangle anim_frame(anim_values *self, int frames_per_row, int tileset_px);
    
    //Initialize anim_values inside Init Function
    //Call anim_Update inside Update function
    //In DrawTexturePro inside Draw functions, pass anim_frame() Rectangle as 'Rectangle src'
    
};
