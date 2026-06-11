#pragma once
#include "raylib.h"

class EngineUtils {
    public:
    void checkDialogueTriggers(Rectangle playerRec);    //call on input
    void checkAutoDialogue(Rectangle playerRec);        //call every frame
};