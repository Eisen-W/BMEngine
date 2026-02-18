#pragma once

#include "asset_manager.hpp"
#include "display_manager.hpp"
#include "debug.hpp"
#include "input_manager.hpp"

struct Engine{
    assetManager AM;
    displayManager DM;
    Debug dbg;
    Mpoint mousepoint;
};
extern Engine EWE;