#pragma once
#include "engine_ast.hpp"
#include "engine_constants.hpp"
#include "mad_data.hpp"
#include "messagebox.hpp"
#include "raylib.h"
#include <string>
#include <unordered_map>
#include <vector>

static const std::unordered_map<std::string, Color> colorMap = {
    {"DARKGRAY", DARKGRAY}, 
    {"MAROON", MAROON}, 
    {"ORANGE",ORANGE},
    {"DARKGREEN", DARKGREEN},
    {"DARKBLUE", DARKBLUE},
    {"DARKPURPLE", DARKPURPLE},
    {"DARKBROWN", DARKBROWN},
    {"GRAY", GRAY},
    {"RED", RED},
    {"GOLD", GOLD},
    {"LIME", LIME},
    {"BLUE", BLUE}, 
    {"VIOLET", VIOLET}, 
    {"BROWN", BROWN},
    {"LIGHTGRAY", LIGHTGRAY},
    {"PINK", PINK}, 
    {"YELLOW", YELLOW},
    {"GREEN", GREEN}, 
    {"SKYBLUE", SKYBLUE}, 
    {"PURPLE", PURPLE}, 
    {"BEIGE", BEIGE},
};

class EngineUtils {
    bool directionMatch(InteractDirection interactDir, Direction PDir);
    std::unordered_map<std::string, std::string> tokens;

    Color resolveColor(const std::string& name) const;

    public:
    void startMessageBox(const DialogueData& data);

    void checkInteractDialogue(Rectangle playerRec, Direction playerDir);    //call on input
    void checkAutoDialogue(Rectangle playerRec);        //call every frame

    void madSetString(const std::string& key, const std::string& value);  //substitute key for value
    std::string resolveTokens(const std::string& raw) const;

    std::vector<ColoredWord> parseColoredString(const std::string& raw) const;
};