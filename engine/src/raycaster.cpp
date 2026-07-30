#include "raycaster.hpp"

#include "constants.hpp"
#include "raylib.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

bool Raycaster::inFOV(Vector2 toTile, float dist, Vector2 dir) const
{
    if(dist == 0) return false;
    float dot = ((toTile.x * dir.x) + (toTile.y * dir.y)) / dist;
    if(dot < 0) return false;

    float angle = acosf(fminf(dot, 1.0f));
    return angle < FOV_RAD / 2;
}

TileFace Raycaster::getFace(const Vector2& pos, const Rectangle& tile) const
{
    int relX = (int)(pos.x / TILE_SIZE) - (int)(tile.x / TILE_SIZE);
    int relY = (int)(pos.y / TILE_SIZE) - (int)(tile.y / TILE_SIZE);

    if(abs(relX) > abs(relY))
    {
        return (relX > 0) ? TileFace::FACE_LF : TileFace::FACE_RF;
    }
    else {
        return (relY > 0) ? TileFace::FACE_F : TileFace::FACE_BK;
    }
}

// ================== BASE FUNCTIONS =====================
void Raycaster::Init(Texture2D& sheet)
{
    facesheet = sheet;
}

// ======================= RAYCASTING ===================
void Raycaster::Update(const Vector2& playerCenter, const std::vector<std::vector<int>>& visMap, int mapW, int mapH)
{
    slices.clear();

    Vector2 pos = playerCenter;
    Vector2 dir = {0,-1};
    Vector2 plane = {tanf(FOV_RAD / 2.0f), 0}; 

    for(int col = 0; col < canvas_W; col++)
    {
        float camX = 2.0f * col / (float)canvas_W - 1.0f;
        Vector2 rayDir = {dir.x + plane.x * camX, dir.y + plane.y * camX};

        float nearestDist = 1e30f;

        int mapX = (int)(pos.x / TILE_SIZE);
        int mapY = (int)(pos.y / TILE_SIZE);

        float deltaDistX = (rayDir.x == 0) ? nearestDist : fabsf(1.0f / rayDir.x);
        float deltaDistY = (rayDir.y == 0) ? nearestDist : fabsf(1.0f / rayDir.y);

        float sideDistX, sideDistY;
        int stepX, stepY;

        // X
        if(rayDir.x < 0) 
        { 
            stepX = -1;
            sideDistX = (pos.x / TILE_SIZE - mapX) * deltaDistX;
        }
        else {
            stepX = 1;
            sideDistX = (mapX + 1.0f - pos.x / TILE_SIZE) * deltaDistX;
        }

        // Y
        if(rayDir.y < 0)
        {
            stepY = -1;
            sideDistY = (pos.y / TILE_SIZE - mapY) * deltaDistY;
        }
        else {
            stepY = 1;
            sideDistY = (mapY + 1.0f - pos.y / TILE_SIZE) * deltaDistY;
        }

        bool hit = false;
        int side = 0;
        int safety = 0;

        while(!hit && safety++ < 200)
        {
            if(sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else {
                sideDistY += deltaDistY;
                mapY += stepY; 
                side = 1;
            }

            if(mapX < 0 || mapX >= mapW || mapY < 0 || mapY >= mapH) break;
            if(visMap[mapY][mapX] != -1) hit = true;
        }

        if(!hit) continue;

        float perpDist = (side == 0)
            ? (sideDistX - deltaDistX)
            : (sideDistY - deltaDistY);

        
        if(perpDist < 1.0f) perpDist = 1.0f;

        float sliceH = fminf((float)canvas_H,(float)canvas_H / perpDist);
        float screenX = (float)col;

        if(col == canvas_W / 2 && hit)
        {
            crossHairPoint = {
                pos.x + rayDir.x * (side == 0 ? (sideDistX - deltaDistX) : (sideDistY - deltaDistY)) * TILE_SIZE,
                pos.y + rayDir.y * (side == 0 ? (sideDistX - deltaDistX) : (sideDistY - deltaDistY)) * TILE_SIZE
            };
        }

        TileFace face;
        if(side == 0)
        {
            face = (rayDir.x > 0) ? TileFace::FACE_LF : TileFace::FACE_RF;
        }
        else {
            face = (rayDir.y > 0) ? TileFace::FACE_F : TileFace::FACE_BK;
        }

        slices.push_back({screenX, sliceH, perpDist, face});

    }
}

void Raycaster::Draw() const
{
    for(const RaySlice& s : slices)
    {
        Rectangle srcRect = {
            (float)((int)s.face * TILE_SIZE), 0,
            (float)TILE_SIZE, (float)TILE_SIZE
        };
        Rectangle destRect = {
            s.screenX, canvas_H / 2.0f - s.screenH / 2.0f,
            1.0f, s.screenH
        };

        DrawTexturePro(facesheet, srcRect, destRect, {0,0}, 0, WHITE);
    }
}