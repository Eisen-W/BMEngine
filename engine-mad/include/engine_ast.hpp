#pragma once
#include "parser.hpp"
#include <string>
#include <vector>

enum class EngineNodeType{
    DIALOGUES,
    DIALOGUE_AUTO,
    DIALOGUE_INTERACT
};

enum struct DialogueTrigger { AUTO, INTERACT };

struct RawRect { ASTNode* x; ASTNode* y; ASTNode* w; ASTNode* h; };
struct MRect { float x, y, w, h; };

//parse time only
struct RawDialogueBlock {
    int id = 0;
    int next = 0;
    bool once = false;
    DialogueTrigger trigger = DialogueTrigger::AUTO;
    std::vector<RawRect> rects;
    std::string speaker;
    std::vector<std::string> lines;
};

struct DialogueBlock{
    DialogueTrigger trigger = DialogueTrigger::AUTO;
    int id = 0;
    int next = 0;
    bool once = false;
    std::vector<MRect> rects;
    std::string speaker;
    std::vector<std::string> lines;
};

struct DialogueNodes {
    std::vector<DialogueBlock> blocks;
};

struct RawDialogueNodes {
    std::vector<RawDialogueBlock> blocks;
};

struct ParseResult{
    std::vector<ASTNode*> core_statements;
    RawDialogueNodes dialogues;
};