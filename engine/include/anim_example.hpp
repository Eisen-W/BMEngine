#pragma once
#include<raylib.h>

struct anim{
    int first;
    int last;
    int curr;

    float speed;
    float duration_left;
};

class Example{
    public:
    void Init();
    void Update();
    void Draw();
    void anim_update(anim *self);
    Rectangle anim_frame(anim *self, int frames_per_row, int tileset_px);

    Texture2D ShootRunTexture;
    anim shootrun;

    private:
};