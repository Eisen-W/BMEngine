#pragma once
#include<raylib.h>

enum class anim_Type{
    REPEATING,
    ONESHOT
};

struct anim{
    int first;
    int last;
    int curr;

    float speed;
    float duration_left;
    anim_Type type;
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