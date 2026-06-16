#pragma once

#include "raylib.h"
#include <string>
#include <vector>
#include "engine_ast.hpp"

struct DialogueData{
    int id;
    int next;
    bool once;
    DialogueTrigger trigger;
    std::vector<Rectangle> rects;
    std::string speaker;
    std::vector<std::string> lines;
};