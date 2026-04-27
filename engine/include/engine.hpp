#pragma once

#include "asset_manager.hpp"
#include "display_manager.hpp"
#include "debug.hpp"
#include "input_manager.hpp"
#include "intro.hpp"
#include "tilemap.hpp"

struct Engine{
    assetManager AM;
    displayManager DM;
    Debug dbg;
    Mpoint mousepoint;
    Intro intro;
    Tilemap TM;
};
extern Engine EWE;