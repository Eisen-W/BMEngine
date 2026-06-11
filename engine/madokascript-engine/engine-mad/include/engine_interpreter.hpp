#pragma once
#include "engine_ast.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class DialogueInterpreter{
    public:
    void load(const DialogueNodes& node);
    void startDialogue(int id);
    void advance();
    const DialogueBlock* current() const;
    bool isRunning() const;
    std::string buildRaw(const DialogueBlock& block) const;
    const std::vector<DialogueBlock>& getBlocks() const;

    private:
    std::vector<DialogueBlock> blocks;
    std::unordered_map<int, bool> fired;
    int currentid = 0;
    bool running = false;

    DialogueBlock* findByID(int id);
    const DialogueBlock* findByID(int id) const;
};