#pragma once

#include "constants.hpp"
#include "raylib.h"
#include <vector>

struct LiveBlock{
    int id;
    Rectangle rect;
};

class BlockManager{
    public:
    void InitBlocks();
    void UpdateBlocks(Rectangle playerRec, Direction playerDir);
    void DrawBlocks();

    void checkBlockDest(); 

    std::vector<LiveBlock> liveblocks;
};