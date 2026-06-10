#pragma once
#include "engine_ast.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class DialogueInterpreter{
    std::vector<DialogueBlock> blocks;
    std::unordered_map<int, bool> fired; //tracking 'once' blocks

    int currentid = 0;
    bool running = false;

    public:
    void load(const DialogueNodes& node);
    void trigger(int id);
    
    bool is_running() const { return running; }

    const DialogueBlock* current() const ;

    void advance(); //call this when msgbox finishes a block to advance to the next

    std::string build_raw(const DialogueBlock& block) const;

    const std::vector<DialogueBlock>& getBlocks() const {
        return blocks;
    }
};