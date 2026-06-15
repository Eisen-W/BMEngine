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
    void startDialogue(int id);
    void advance();
    const DialogueBlock* current() const;
    bool isRunning() const;
    std::string buildRaw(const DialogueBlock& block) const;
    const std::vector<DialogueBlock>& getBlocks() const;
    bool hasFired(int id) const;

    private:
    std::vector<DialogueBlock> blocks;
    std::unordered_map<int, bool> fired;
    int currentid = 0;
    bool running = false;
    Interpreter core_interp;

    DialogueBlock* findByID(int id);
    const DialogueBlock* findByID(int id) const;
    float eval_expr(ASTNode* node);
};