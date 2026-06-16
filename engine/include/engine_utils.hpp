#pragma once
#include "raylib.h"

class EngineUtils {
    public:
    void checkInteractDialogue(Rectangle playerRec, Vector2 facingPoint);    //call on input
    void checkAutoDialogue(Rectangle playerRec);        //call every frame
};