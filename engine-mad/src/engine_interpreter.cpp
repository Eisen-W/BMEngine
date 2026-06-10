#include "engine_interpreter.hpp"
#include "engine_ast.hpp"
#include <vector>

void DialogueInterpreter::load(const DialogueNodes& node)
{
    for(auto& block : node.blocks)
    {
        blocks[block.id] = block;
    }
}

void DialogueInterpreter::trigger(int id)
{
    for(auto& block : blocks)
    {
        if(block.id == id)
        {
            if(block.once && fired.count(id)) return;
            currentid = id;
            running = true;
            return;
        }
    }
}
    
const DialogueBlock* DialogueInterpreter::current() const 
{
    if(!running) return nullptr;
    for(auto& block : blocks)
    {
        if(block.id == currentid) return &block;
    }
    return nullptr;
}

void DialogueInterpreter::advance()
{
    if(!running) return;
    
    auto find_block = [&](int id) -> DialogueBlock* 
    {
        for(auto& b : blocks)
        {
            if(b.id == id) return &b;
        }
        return nullptr;
    };

    DialogueBlock* block = find_block(currentid);
    if(!block) { running = false; return; }

    if(block->once) fired[currentid] = true;

    if(block->next == 0)
    {
        running = false;
        currentid = 0;
        return;
    }
    currentid = block->next;

    DialogueBlock* next_block = find_block(currentid);
    if(!next_block || (next_block->once && fired.count(currentid)))
    {
        running = false;
        currentid = 0;
    }
}

std::string DialogueInterpreter::build_raw(const DialogueBlock& block) const
{
    std::string raw;
    for(int i = 0; i < (int)block.lines.size(); i++)
    {
        raw += block.lines[i];
        if(i < (int)block.lines.size() - 1) raw += "|";
    }
    return raw;
}
