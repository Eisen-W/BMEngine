#include "interactable.hpp"
#include <fstream>
#include <string>

void Interactable::Load(const char* path)
{
    interactionList.clear();
    std::ifstream file(path);
    
    if(!file.is_open())
    {
        printf("failed to load interactables: %s\n", path);
        return;
    }

    std::string line;
    while(std::getline(file, line))
    {
        int comma1 = line.find(',');
        int comma2 = line.find(',', comma1 + 1);

        InteractableData entry;
        entry.tileX = std::stoi(line.substr(0, comma1));
        entry.tileY = std::stoi(line.substr(comma1 + 1, comma2 - comma1 -1));
        entry.message = line.substr(comma2 + 1);
        interactionList.push_back(entry);
    }
}

InteractableData* Interactable::getAt(int tileX, int tileY)
{
    for(auto& i : interactionList)
    {
        if(i.tileX == tileX && i.tileY == tileY) return &i;
    }
    return nullptr;
}