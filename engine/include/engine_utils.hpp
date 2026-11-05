#pragma once
#include "engine_ast.hpp"
#include "engine_constants.hpp"
#include "mad_data.hpp"
#include "raylib.h"
#include <string>
#include <unordered_map>

class EngineUtils {
    bool directionMatch(InteractDirection interactDir, Direction PDir);
    std::unordered_map<std::string, std::string> tokens;

    public:
    void startMessageBox(const DialogueData& data);

    void checkInteractDialogue(Rectangle playerRec, Direction playerDir);    //call on input
    void checkAutoDialogue(Rectangle playerRec);        //call every frame

    void madSetString(const std::string& key, const std::string& value);  //substitute key for value
    std::string resolveTokens(const std::string& raw) const;
};