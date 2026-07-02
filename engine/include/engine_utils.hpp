#pragma once
#include "constants.hpp"
#include "engine_ast.hpp"
#include "mad_data.hpp"
#include "raylib.h"

class EngineUtils {
    bool directionMatch(InteractDirection interactDir, Direction playerDir);

    public:
    void startMessageBox(const DialogueData& data);

    void checkInteractDialogue(Rectangle playerRec, Direction playerDir);    //call on input
    void checkAutoDialogue(Rectangle playerRec);        //call every frame
};