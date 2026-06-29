#pragma once
#include "engine_ast.hpp"
#include "interpreter.hpp"
#include "parser.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class DialogueInterpreter{
    public:
    void load(const ParseResult& result);
    void startDialogue(int id, int rectIndex = -1);
    void advance();
    const DialogueBlock* current() const;
    bool isRunning() const;
    std::string buildRaw(const DialogueBlock& block) const;
    const std::vector<DialogueBlock>& getBlocks() const;
    bool hasFiredRect(int id, int rectIndex) const;

    //save & load
    void saveFiredRects(FILE* f) const;
    void loadFiredRects(FILE* f);

    private:
    std::vector<DialogueBlock> blocks;
    std::unordered_map<int, std::vector<bool>> firedRects;
    int currentid = 0;
    bool running = false;
    Interpreter core_interp;

    DialogueBlock* findByID(int id);
    const DialogueBlock* findByID(int id) const;
    float eval_expr(ASTNode* node);
};