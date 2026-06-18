#pragma once

#include "raylib.h"
#include <string>
#include <vector>
#include "engine_ast.hpp"

struct DialogueRect{
    Rectangle rect;
    InteractDirection dir;
};

struct DialogueData{
    int id;
    int next;
    bool once;
    DialogueTrigger trigger;
    std::vector<DialogueRect> rects;
    std::string speaker;
    std::string sprite;
    std::vector<std::string> lines;
};