#pragma once

class Intro{
    public:
    void Init();
    void Update();
    void Draw();
    bool Engineintro;

    private:
    int count;
    const char* engineTitle;
    int textSize;
};