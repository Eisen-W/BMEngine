#pragma once

static constexpr int canvas_W = 640;
static constexpr int canvas_H = 480;

//change as needed
constexpr int TILE_SIZE = 32;
constexpr int SPRITE_SIZE = 16;

enum struct GameState { TITLE, PLAY, MENU, MESSAGE };
extern GameState gamestate;

enum struct Layer : int{
    BACKGROUND = 0,
    VISUAL_BG = 1,
    OBJECT = 2,
    VISUAL_FG = 3,
    FOREGROUND = 4,
    UI = 5,
};