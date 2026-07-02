#include "game.hpp"
#include "engine.hpp"
#include "raylib.h"

void Game::Init() {
  //to load all game objects and set custom values to variables

  EWE.loader.FLoad("../assets/msg.mad");
  EWE.FSM.texture = EWE.AM.getTexture("../assets/face.png");
  EWE.FSM.registerFace("EisenW", {0,0,16,16});



  gameReady = 0; //keep at the end of the function
}

void Game::Update() {
  //all update code and functions go here
  float dt = GetFrameTime();

  //Replace the rec values below with player rec 
  if(!EWE.MB.isActive())
  {
    EWE.EUtils.checkAutoDialogue({0,0,640,480});
  }
  
}

void Game::Draw() {
  //all draw calls here
  DrawRectangle(0, 0, 640, 480, DARKBLUE);
}