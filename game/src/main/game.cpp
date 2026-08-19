#include "game.hpp"
#include "engine.hpp"
#include "raylib.h"

void Game::Init() {
  //to load/initialize all game objects
  BME.screens.add("ex1", &screen1);
  BME.screens.add("ex2", &screen2);

  screen2.LazyInit = true;  // heavy screen, defer until first visit

  BME.screens.InitAll();    // inits all except screens with 'LazyInit = true'
  BME.screens.switchTo("ex1");

  gameNotReady = 0; //keep at the end of the function
}

void Game::Update() {
  //all update code goes here
  float dt = GetFrameTime();
  BME.screens.Update();
}

void Game::Draw() {
  //all draw calls here
  DrawRectangle(0, 0, 640, 480, {0,4,51,255});
  BME.screens.Draw();
}