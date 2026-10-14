#pragma once

// Header for more collision types

#include "raylib.h"
class PixelCollision
{
    public:
    bool PixelCollidePoint(Color* imgPixels, int imgW, int imgH, Vector2 imgPos, Vector2 point);
    bool PixelCollideRec(Color* imgPixels, int imgW, int imgH, Vector2 imgPos, Rectangle rec);
};