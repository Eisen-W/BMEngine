#pragma once
#include <string>
#include <vector>

// store interactable tiles data in a plain text file, example below
// interact.txt: 16,16,hello
// syntax: x,y,message
// use the '|' delimiter to split message into pages, example below
// 16,16,Hello there | how ya doing?

// engine automatically wraps the message around box, meaning the new word gets pushed 
// to new line when there isnt enough space on current line based on message box rect
// engine automatically handles that so there's no need for extra work
// change the messagebox according to your liking

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
