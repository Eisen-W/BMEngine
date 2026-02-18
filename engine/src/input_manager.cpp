#include "input_manager.hpp"
#include "display_manager.hpp"
#include "engine.hpp"

bool Mpoint::MouseRec(Rectangle Rec)
{
    Vector2 mouse = GetMousePosition();
    auto& dm = EWE.DM;
    float ox = dm.getOffsetX();
    float oy = dm.getOffsetY();
    scale = dm.getScale();
    Vector2 fit = dm.getFit();

    if(mouse.x < ox || mouse.x >= ox + fit.x ||
        mouse.y < oy || mouse.y >= oy + fit.y)
        {
            return false;
        }
    
    CMouse = {(mouse.x - ox)/scale, (mouse.y - oy)/scale}; 


    return CheckCollisionPointRec(CMouse, Rec);
    
   //return CheckCollisionPointRec(GetMousePosition(), Rec);
}