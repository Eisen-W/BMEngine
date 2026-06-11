#pragma once

#include "dialogue.hpp"
#include "engine_interpreter.hpp"
#include <string>
#include <vector>

class Loader{
    public:
    // handles loading the necessary default files
    // call the load function in your game level Init function

    public:
    void DLoad(const char* dialogue_filepath);
    const std::vector<DialogueData>& getDialogueBlocks() const;
    void startDialogue(int id);
    void advanceDialogue();
    const DialogueData* currentDialogue() const;
    bool dialogueRunning() const;
    std::string buildRaw(const DialogueData& data) const;

    private:
    DialogueInterpreter dialogue_interp;
    std::vector<DialogueData> d_data;
};