#include "game.hpp"
#include "engine.hpp"
#include "raylib.h"

void Game::Init() {
  //to load all game objects and set custom values to variables
  gameReady = 0;
  EWE.loader.DLoad("../assets/msg.mad");
}

void Game::Update() {
  //all update code and functions go here
  float dt = GetFrameTime();

  EWE.EUtils.checkAutoDialogue({0,0,640,480});
}

void Game::Draw() {
  //all draw calls here
  DrawRectangle(0, 0, 640, 480, DARKBLUE);
}