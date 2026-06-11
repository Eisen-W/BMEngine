#include "engine_interpreter.hpp"
#include "engine_ast.hpp"
#include <string>

void DialogueInterpreter::load(const DialogueNodes& node)
{
    blocks.clear();
    fired.clear();
    currentid = 0;
    running = false;

    for(auto& block : node.blocks)
    {
        blocks.push_back(block);
    }
}

void DialogueInterpreter::startDialogue(int id)
{
    DialogueBlock* block = findByID(id);
    if(!block) return;
    if(block->once && fired.count(id)) return;
    currentid = id;
    running = true;
}

void DialogueInterpreter::advance()
{
    if(!running) return;

    DialogueBlock* block = findByID(currentid);
    if(!block) { running = false; return; }

    if(block->once) fired[currentid] = true;

    if(block->next == 0)
    {
        running = false;
        currentid = 0;
        return;
    }

    currentid = block->next;

    DialogueBlock* next = findByID(currentid);
    if(!next || (next->once && fired.count(currentid)))
    {
        running = false;
        currentid = 0;
    }
}

const DialogueBlock* DialogueInterpreter::current() const
{
    if(!running) return nullptr;
    return findByID(currentid);
}

bool DialogueInterpreter::isRunning() const
{
    return running;
}

std::string DialogueInterpreter::buildRaw(const DialogueBlock& block) const
{
    std::string raw;
    for(int i = 0; i < (int)block.lines.size(); i++)
    {
        raw += block.lines[i];
        if(i < (int)block.lines.size() - 1) raw += '|';
    }
    return raw;
}

const std::vector<DialogueBlock>& DialogueInterpreter::getBlocks() const
{
    return blocks;
}

bool DialogueInterpreter::hasFired(int id) const
{
    return fired.count(id) > 0;
}

DialogueBlock* DialogueInterpreter::findByID(int id)
{
    for(auto& b : blocks)
    {
        if(b.id == id) return &b;
    }
    return nullptr;
}

const DialogueBlock* DialogueInterpreter::findByID(int id) const
{
    for(auto& b : blocks)
    {
        if(b.id == id) return &b;
    }
    return nullptr;
}