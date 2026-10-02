#pragma once

#include "game.hpp"
class Play{
    public:
    void playgame();

    private:
    void Init();
    void Update(float dt);
    void Canvas();
    void Draw();
    void Unload();

    Game game;
    Renderer renderer;
};
