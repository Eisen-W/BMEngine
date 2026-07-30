#include "moveblock_manager.hpp"
#include "constants.hpp"
#include "engine.hpp"
#include "input_manager.hpp"
#include "raylib.h"
#include <cmath>

void BlockManager::InitBlocks()
{
    liveblocks.clear();
    for(auto& mv : BME.madloader.getMoveables())
    {
        liveblocks.push_back({mv.id, mv.current});
    }
}

void BlockManager::UpdateBlocks(Rectangle playerRec, Direction playerDir)
{
    for(auto& block : liveblocks)
    {
        Rectangle pushCheck = playerRec;
        Vector2 pushDir = {0, 0};

        switch(playerDir)
        {
            case Direction::UP:     pushDir = {0, -1};  pushCheck.y -= 2; break;
            case Direction::DOWN:   pushDir = {0, 1};   pushCheck.y += 2; break;
            case Direction::LEFT:   pushDir = {-1, 0};  pushCheck.x -= 2; break;
            case Direction::RIGHT:  pushDir = {1, 0};   pushCheck.x += 2; break;
        }

        if(CheckCollisionRecs(pushCheck, block.rect) && Input::holdA())
        {
            block.rect.x += pushDir.x * TILE_SIZE;
            block.rect.y += pushDir.y * TILE_SIZE;
            checkBlockDest();
        }

        //add collision detection here
    }
}

void BlockManager::DrawBlocks()
{
    for(auto& block : liveblocks)
    {
        DrawRectangleRec(block.rect, BROWN);
        //add block sprite
    }
}

void BlockManager::checkBlockDest()
{
    for(auto& block : liveblocks)
    {
        block.rect.x = round(block.rect.x / TILE_SIZE) * TILE_SIZE;
        block.rect.y = round(block.rect.y / TILE_SIZE) * TILE_SIZE;

        bool matched = false;
        for(auto& mv : BME.madloader.getMoveables())
        {
            if(mv.id != block.id) continue;
            for(int i = 0; i < (int)mv.dest.size(); i++)
            {
                if(CheckCollisionRecs(block.rect, mv.dest[i]))
                {
                    BME.madloader.setMoveableDestIndex(block.id,i);
                    matched = true;
                    break;
                }
            }
        }
        if(!matched)
        {
            BME.madloader.setMoveableDestIndex(block.id, -1);
        }
    }
}