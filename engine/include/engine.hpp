#pragma once

#include "asset_manager.hpp"
#include "display_manager.hpp"
#include "debug.hpp"
#include "input_manager.hpp"
#include "intro.hpp"
#include "messagebox.hpp"
#include "moveblock_manager.hpp"
#include "tilemap.hpp"
#include "anim_manager.hpp"
#include "loader.hpp"
#include "engine_utils.hpp"
#include "faceset_manager.hpp"
#include "save_manager.hpp"
#include "raycaster.hpp"

struct Engine{
    AssetManager AM;
    DisplayManager DM;
    Debug dbg;
    Mpoint mousepoint;
    Intro intro;
    Tilemap TM;
    Animation Anim;
    TextBox TB;
    MadLoader madloader;
    EngineUtils EUtils;
    FacesetManager FSM;
    SaveManager SAVE;
    BlockManager moveblock;
    Raycaster raycast;
};
extern Engine BME;