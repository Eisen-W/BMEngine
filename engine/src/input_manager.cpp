#include "input_manager.hpp"
#include "display_manager.hpp"
#include "engine.hpp"

bool Mpoint::MouseRec(Rectangle Rec)
{
    return CheckCollisionPointRec(CMouse, Rec);
}

void Mpoint::UpdateMouse()
{
    Vector2 mouse = GetMousePosition();
    auto& dm = BME.DM;
    float ox = dm.getOffsetX();
    float oy = dm.getOffsetY();
    scale = dm.getScale();
    Vector2 fit = dm.getFit();

    if(mouse.x < ox || mouse.x >= ox + fit.x ||
        mouse.y < oy || mouse.y >= oy + fit.y)
    {
        return;
    }
    
    CMouse = {(mouse.x - ox)/scale, (mouse.y - oy)/scale}; 
}