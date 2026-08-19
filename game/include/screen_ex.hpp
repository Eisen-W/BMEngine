// EXAMPLE SCREEN
// Delete it or repurpose it

#pragma once
#include "screen_manager.hpp"

class ScreenEx1 : public IScreen
{
    public:
    bool closeScreen = false;

    void Init() override;
    void Update() override;
    void Draw() override;
};

class ScreenEx2 : public IScreen
{
    public:
    bool closeScreen = false;

    void Init() override;
    void Update() override;
    void Draw() override;
};