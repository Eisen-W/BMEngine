#pragma once

#include "constants.hpp"
#include "raylib.h"
#include "tilemap.hpp"
#include <functional>
#include <vector>

struct DrawCommand{
    Layer layer = Layer::OBJECT;
    float sortY = 0.0f;
    std::function<void()> draw;
};

class Renderer{
    private:
    std::vector<DrawCommand> commands;

    public:
    // generic use
    void Submit(Layer layer, std::function<void()> fn, float sortY = 0.0f);

    // for textures
    void SubmitTexture(Texture2D& texture, Rectangle src, Vector2 pos,
                        Layer layer = Layer::OBJECT, float sortY = 0.0f, Color tint = WHITE);
    
    // for tiles 
    void SubmitTile(const TileInstance& tile, Texture2D& tileset, Layer layer, float sortY = 0.0f);

    // sorts all layers and draws
    void RenderLayers();

    // optional
    void Clear();
};