#pragma once

#include "engine_ast.hpp"
#include "interpreter.hpp"
#include <unordered_map>
#include <vector>

class InteractableInterpreter{
    public:
    void load(const ParseResult& result, Interpreter& core_interp);

    //switchers
    bool getSwitcherState(int id) const;
    void setSwitcherState(int id, bool value);
    const std::vector<SwitcherBlock>& getSwitchers() const;

    //moveables
    int getMoveableDestIndex(int id) const; // -1 if unsolved
    void setMoveableDestIndex(int id, int destIndex); // -1 to reset
    const std::vector<MoveableBlock>& getMoveables() const;
    MoveableBlock* findMoveableByID(int id);

    void saveState(FILE* f) const;
    void loadState(FILE* f);

    private:
    std::vector<SwitcherBlock> switchers;
    std::vector<MoveableBlock> moveables;
    std::unordered_map<int, bool> switcherState;
    std::unordered_map<int, int> moveableState;

    void ResolveMoveablePos(MoveableBlock& mb);
};