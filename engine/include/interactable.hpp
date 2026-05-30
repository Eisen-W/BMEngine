#pragma once
#include <string>
#include <vector>

struct InteractableData {
    int tileX, tileY;
    std::string message;
};

class Interactable{
    public:
    void Load(const char* path);
    InteractableData* getAt(int tileX, int tileY);
    const std::vector<InteractableData>& getInteractVector() const { return interactionList; }

    private:
    std::vector<InteractableData> interactionList;
};
