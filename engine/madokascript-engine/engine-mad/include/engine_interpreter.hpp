#pragma once
#include "engine_ast.hpp"
#include "interpreter.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class DialogueInterpreter{
    public:
    void load(const ParseResult& result, Interpreter& core_interp);
    void startDialogue(int id, int rectIndex = -1);
    void advance();
    const DialogueBlock* current() const;
    bool isRunning() const;
    std::string buildRaw(const DialogueBlock& block) const;
    const std::vector<DialogueBlock>& getBlocks() const;
    bool hasFiredRect(int id, int rectIndex) const;

    std::vector<DialogueBlock>& getBlocksMutable();
    void setFiredRects(int id, const std::vector<bool>& fired);

    //save & load
    void saveFiredRects(FILE* f) const;
    void loadFiredRects(FILE* f);

    private:
    std::vector<DialogueBlock> blocks;
    std::unordered_map<int, std::vector<bool>> firedRects;
    int currentid = 0;
    bool running = false;

    DialogueBlock* findByID(int id);
    const DialogueBlock* findByID(int id) const;
};