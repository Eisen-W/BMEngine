#pragma once
#include <string>
#include <vector>

enum class EngineNodeType{
    DIALOGUES,
    DIALOGUE_AUTO,
    DIALOGUE_INTERACT
};

struct DialogueBlock{
    int id = 0;
    int next = 0;
    bool once = false;
    float rectX = 0, rectY = 0, rectW = 0, rectH = 0;
    std::string speaker;
    std::vector<std::string> lines;
};

struct DialogueNodes {
    std::vector<DialogueBlock> blocks;
};