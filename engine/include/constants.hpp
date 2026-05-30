#pragma once

constexpr int TILE_SIZE = 16;
constexpr int SPRITE_SIZE = 32;

enum struct GameState { PLAY, MENU, MESSAGE };
enum struct Direction { UP, DOWN, LEFT, RIGHT };

extern GameState gamestate;