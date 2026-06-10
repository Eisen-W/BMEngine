#pragma once

#include "engine_ast.hpp"
#include "engine_interpreter.hpp"
#include <vector>
class Loader{
    public:
    // handles loading the necessary default files
    // call the load function in your game level Init function

    void DLoad(const char* dialogue_filepath); // Load Dialogue File

    const std::vector<DialogueBlock>& getDialogueBlocks() const {
    }

    private:
    DialogueInterpreter dialogue_interp;
};