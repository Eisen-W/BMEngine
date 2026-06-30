#pragma once
#include "parser.hpp"
#include <string>
#include <vector>

enum class EngineNodeType{
    DIALOGUES,
    DIALOGUE_AUTO,
    DIALOGUE_INTERACT,
    INTERACTABLES
};

enum struct InteractDirection { UP, DOWN, LEFT, RIGHT, ANY };

enum struct DialogueTrigger { AUTO, INTERACT };

enum struct InteractableType { SWITCHER, MOVEABLE };

struct RawRect { ASTNode* x; ASTNode* y; ASTNode* w; ASTNode* h; InteractDirection dir = InteractDirection::ANY; };
struct MRect { float x, y, w, h; InteractDirection dir = InteractDirection::ANY; };

//parse time only
struct RawDialogueBlock {
    int id = 0;
    int next = 0;
    bool once = false;
    DialogueTrigger trigger = DialogueTrigger::AUTO;
    std::vector<RawRect> rects;
    std::string speaker;
    std::string sprite;
    std::vector<std::string> lines;
};

struct DialogueBlock{
    DialogueTrigger trigger = DialogueTrigger::AUTO;
    int id = 0;
    int next = 0;
    bool once = false;
    std::vector<MRect> rects;
    std::string speaker;
    std::string sprite;
    std::vector<std::string> lines;
};

struct DialogueNodes {
    std::vector<DialogueBlock> blocks;
};

struct RawDialogueNodes {
    std::vector<RawDialogueBlock> blocks;
};



//====================INTERACTABLES=====================

struct RawSwitcherBlock{
    int id = 0;
    std::string name;
    std::vector<RawRect> rects;
};

struct RawMoveableBlock{
    int id = 0;
    std::string name;
    RawRect start;
    std::vector<RawRect> dest;
};

struct SwitcherBlock{
    int id = 0;
    std::string name;
    std::vector<MRect> rects;
};

struct MoveableBlock{
    int id = 0;
    std::string name;
    MRect start;
    std::vector<MRect> dest;
    MRect current; //resolved at load
};

struct RawInteractableNodes{
    std::vector<RawSwitcherBlock> switchers;
    std::vector<RawMoveableBlock> moveables;
};

struct InteractableNodes{
    std::vector<SwitcherBlock> switchers;
    std::vector<MoveableBlock> moveables;
};

struct ParseResult{
    std::vector<ASTNode*> core_statements;
    RawDialogueNodes dialogues;
    RawInteractableNodes interactables;
};