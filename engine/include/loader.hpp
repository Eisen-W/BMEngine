#pragma once

#include "interactable_interpreter.hpp"
#include "interpreter.hpp"
#include "mad_data.hpp"
#include "engine_interpreter.hpp"
#include <string>
#include <vector>

class Loader{
    public:
    // handles loading the necessary default files
    // call the load function in your game level Init function

    public:
    void FLoad(const char* madfile); // File Load

    // dialogue passthrough
    const std::vector<DialogueData>& getDialogueBlocks() const;
    void startDialogue(int id, int rectIndex = -1);
    void advanceDialogue();
    const DialogueData* currentDialogue() const;
    bool dialogueRunning() const;
    std::string buildRaw(const DialogueData& data) const;
    bool hasFiredRect(int id, int rectIndex) const;

    void saveDialogueState(FILE* f) const;
    void loadDialogueState(FILE* f);

    // interactable passthroughs
    const std::vector<SwitcherData>& getSwitchers() const;
    bool getSwitcherState(int id) const;
    void setSwitcherState(int id, bool value);

    const std::vector<MoveableData>& getMoveables() const;
    int getMoveableDestIndex(int id) const;
    void setMoveableDestIndex(int id, int destIndex);

    void saveInteractableState(FILE* f) const;
    void loadInteractableState(FILE* f);


    private:
    Interpreter core_interp;
    DialogueInterpreter dialogue_interp;
    InteractableInterpreter interact_interp;

    std::vector<DialogueData> d_data;
    std::vector<SwitcherData> switcher_data;
    std::vector<MoveableData> moveable_data;

    void convertDialogueData();
    void convertInteractableData();
};