#include "renderer.hpp"
#include "raylib.h"
#include <algorithm>

// generic use
void Renderer::Submit(Layer layer, std::function<void()> fn, float sortY)
{
    commands.push_back({layer, sortY, std::move(fn)});
}

// for textures
void Renderer::SubmitTexture(Texture2D& texture, Rectangle src, Vector2 pos,
                    Layer layer, float sortY, Color tint)
{
    commands.push_back({layer, sortY, 
        [=, &texture]()
        { DrawTextureRec(texture, src, pos, tint); }
    });
}

// for tiles 
void Renderer::SubmitTile(const TileInstance& tile, Texture2D& tileset, Layer layer, float sortY)
{
    SubmitTexture(tileset, tile.src, tile.pos, layer, sortY);
}

// sorts all layers and draws
void Renderer::RenderLayers()
{
    std::sort(commands.begin(), commands.end(), 
    [](const DrawCommand& a, const DrawCommand& b)
        {
            if(a.layer != b.layer)
            {
                return static_cast<int>(a.layer) < static_cast<int>(b.layer);
            }
            return a.sortY < b.sortY;
        });

    for(auto& cmd : commands)
    {
        if(cmd.draw) cmd.draw();
    }
    
    commands.clear();
}

void Renderer::Clear()
{
    commands.clear();
}