#pragma once

#include "asset_manager.hpp"
#include "display_manager.hpp"
#include "debug.hpp"
#include "input_manager.hpp"
#include "interactable.hpp"
#include "intro.hpp"
#include "messagebox.hpp"
#include "moveblock_manager.hpp"
#include "tilemap.hpp"
#include "anim_manager.hpp"
#include "loader.hpp"
#include "engine_utils.hpp"
#include "faceset_manager.hpp"
#include "save_manager.hpp"

struct Engine{
    assetManager AM;
    displayManager DM;
    Debug dbg;
    Mpoint mousepoint;
    Intro intro;
    Tilemap TM;
    Animation Anim;
    MessageBox MB;
    Interactable interact;
    Loader loader;
    EngineUtils EUtils;
    FacesetManager FSM;
    SaveManager SAVE;
    BlockManager moveblock;
};
extern Engine EWE;