#include "game.hpp"
#include "raylib.h"

void Game::Init() {
  //to load all game objects and set custom values to variables
  gameInit = 0;
}

void Game::Update() {
  //all update code and functions go here
  float dt = GetFrameTime();
}

void Game::Draw() {
  //all draw calls here
  DrawRectangle(0, 0, 640, 480, DARKBLUE);
}