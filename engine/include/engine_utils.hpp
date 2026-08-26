#pragma once
#include "engine_ast.hpp"
#include "engine_constants.hpp"
#include "mad_data.hpp"
#include "raylib.h"

class EngineUtils {
    bool directionMatch(InteractDirection interactDir, Direction PDir);

    public:
    void startMessageBox(const DialogueData& data);

    void checkInteractDialogue(Rectangle playerRec, Direction playerDir);    //call on input
    void checkAutoDialogue(Rectangle playerRec);        //call every frame
};