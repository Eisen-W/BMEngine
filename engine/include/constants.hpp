#pragma once

constexpr int TILE_SIZE = 16;
constexpr int SPRITE_SIZE = 32;

constexpr int ENEMY_TILE_W = SPRITE_SIZE / TILE_SIZE;
constexpr int ENEMY_TILE_H = (SPRITE_SIZE + SPRITE_SIZE / 2) / TILE_SIZE;

enum struct GameState { PLAY, MENU, MESSAGE };
enum struct Direction { UP, DOWN, LEFT, RIGHT };

extern GameState gamestate;