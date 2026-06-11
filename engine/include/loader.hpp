#pragma once

#include "engine_ast.hpp"
#include "engine_interpreter.hpp"
#include <string>
#include <vector>
class Loader{
    public:
    // handles loading the necessary default files
    // call the load function in your game level Init function

    void DLoad(const char* dialogue_filepath); // Load Dialogue File

    const std::vector<DialogueBlock>& getDialogueBlocks() const {
        return dialogue_interp.getBlocks();
    }

    std::string buildRaw(const DialogueBlock& block)
    {
        return dialogue_interp.build_raw(block);
    }

    void advanceDialogue()
    {
        dialogue_interp.advance();
    }

    private:
    DialogueInterpreter dialogue_interp;
};