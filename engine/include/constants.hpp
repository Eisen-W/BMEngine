#pragma once

static constexpr int canvas_W = 640;
static constexpr int canvas_H = 480;

//change as needed
constexpr int TILE_SIZE = 16;
constexpr int SPRITE_SIZE = 16;

enum struct GameState { TITLE, PLAY, MENU, MESSAGE };
extern GameState gamestate;