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
    int getMoveableDestIndex(int id) const; // -1 if unsolved, only answers "which dest is block 'n' at"
    void setMoveableDestIndex(int id, int destIndex); // -1 to reset
    bool isMoveableSolved(int id) const; // for boolean only checks, only answers "is block 'n' solved or not"
    const std::vector<MoveableBlock>& getMoveables() const;
    MoveableBlock* findMoveableByID(int id);

    std::vector<SwitcherBlock>& getSwitchersMutable();
    std::vector<MoveableBlock>& getMoveablesMutable();
    
    void saveState(FILE* f) const;
    void loadState(FILE* f);

    private:
    std::vector<SwitcherBlock> switchers;
    std::vector<MoveableBlock> moveables;
    std::unordered_map<int, bool> switcherState;
    std::unordered_map<int, int> moveableState;

    void ResolveMoveablePos(MoveableBlock& mb);
};