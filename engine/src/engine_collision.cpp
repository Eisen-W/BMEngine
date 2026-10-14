#include "engine_collision.hpp"
#include "raylib.h"
#include <algorithm>

bool PixelCollision::PixelCollidePoint(Color* imgPixels, int imgW, int imgH, Vector2 imgPos, Vector2 point)
{
    Rectangle imgRec = {imgPos.x, imgPos.y, (float)imgW, (float)imgH};
    if(!CheckCollisionPointRec(point, imgRec)) return false;
    

    int localX = (int)(point.x - imgPos.x);
    int localY = (int)(point.y - imgPos.y);

    if(localX < 0 || localY < 0 || localX >= imgW || localY >= imgH) return false;

    return imgPixels[localY * imgW + localX].a > 0;
}

bool PixelCollision::PixelCollideRec(Color* imgPixels, int imgW, int imgH, Vector2 imgPos, Rectangle rec)
{
    Rectangle imgRec = {imgPos.x, imgPos.y, (float)imgW, (float)imgH};
    if(!CheckCollisionRecs(imgRec, rec)) return false;

    int startX = std::max(0, (int)(rec.x - imgPos.x));
    int startY = std::max(0, (int)(rec.y - imgPos.y));
    int endX   = std::min(imgW, (int)(rec.x + rec.width - imgPos.x));
    int endY   = std::min(imgH, (int)(rec.y + rec.height - imgPos.y)); 

    for(int y = startY; y < endY; y++)
    {
        for(int x = startX; x < endX; x++)
        {
            if(imgPixels[y * imgW + x].a > 0) return true;
        }
    }
    return false;
}
