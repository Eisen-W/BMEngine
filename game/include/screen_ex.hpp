// EXAMPLE SCREEN
// Delete it or repurpose it

#pragma once
#include "engine_constants.hpp"

#include "screen_manager.hpp"
#include "tilemap.hpp"


class ScreenEx1 : public IScreen
{
    public:
    bool closeScreen = false;

    void Init() override;
    void Update() override;
    void Draw() override;

    private:
    Tilemap levelmap;
    Direction dir = Direction::DOWN;
};

class ScreenEx2 : public IScreen
{
    public:
    bool closeScreen = false;

    void Init() override;
    void Update() override;
    void Draw() override;
};