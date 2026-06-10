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
    if(blocks.find(id) == blocks.end()) return;
    auto& block = blocks[id];
    if(block.once && fired.count(id)) return; //already fired
    currentid = id;
    running = true;
}
    
const DialogueBlock* DialogueInterpreter::current() const 
{
    if(!running) return nullptr;
    auto it =  blocks.find(currentid);
    if(it == blocks.end()) return nullptr;
    return &it->second;
}

void DialogueInterpreter::advance()
{
    if(!running) return;
    auto& block = blocks[currentid];

    if(block.once) fired[currentid] = true;

    if(block.next == 0)
    {
        running = false;
        currentid = 0;
        return;
    }
    currentid = block.next;

    //check if next block has already fired
    auto& next_block = blocks[currentid];
    if(next_block.once && fired.count(currentid))
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

std::vector<DialogueBlock> DialogueInterpreter::getblocks() const
{
    std::vector<DialogueBlock> result;
    for(auto& pair : blocks)
    {
        result.push_back(pair.second);
    }
    return result;
}