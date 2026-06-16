#include "engine_interpreter.hpp"
#include "engine_ast.hpp"
#include "interpreter.hpp"
#include <string>
#include <vector>

void DialogueInterpreter::load(const ParseResult& result)
{
    blocks.clear();
    firedRects.clear();
    currentid = 0;
    running = false;

    // run core statements first
    for(auto* node : result.core_statements)
    {
        core_interp.exec_node(node);
    }

    // evaluate raw blocks into final DialogueBlock
    for(auto& raw : result.dialogues.blocks)
    {
        DialogueBlock block;
        block.id = raw.id;
        block.next = raw.next;
        block.once = raw.once;
        block.trigger = raw.trigger;
        block.speaker = raw.speaker;
        block.lines = raw.lines;

        for(auto& r : raw.rects)
        {
            MRect rect;
            rect.x = (float)core_interp.eval_node(r.x).num;
            rect.y = (float)core_interp.eval_node(r.y).num;
            rect.w = (float)core_interp.eval_node(r.w).num;
            rect.h = (float)core_interp.eval_node(r.h).num;
            
            blocks.push_back(block);
        }
        firedRects[block.id] = std::vector<bool>(block.rects.size(), false);
        blocks.push_back(block);
        
    }
}

float DialogueInterpreter::eval_expr(ASTNode* node)
{
    Value v = core_interp.eval_node(node);
    return (float)v.num;
}

void DialogueInterpreter::startDialogue(int id, int rectIndex)
{
    DialogueBlock* block = findByID(id);
    if(!block) return;

    if(rectIndex >= 0 && block->once)
    {
        if(firedRects[id][rectIndex]) return;
        firedRects[id][rectIndex] = true;
    }
    currentid = id;
    running = true;
}

void DialogueInterpreter::advance()
{
    if(!running) return;

    DialogueBlock* block = findByID(currentid);
    if(!block) { running = false; return; }

    if(block->next == 0)
    {
        running = false;
        currentid = 0;
        return;
    }

    currentid = block->next;

    if(!findByID(currentid))
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

bool DialogueInterpreter::hasFiredRect(int id, int rectIndex) const
{
    auto it = firedRects.find(id);
    if(it == firedRects.end()) return false;
    if(rectIndex < 0 || rectIndex >= (int)it->second.size()) return false;
    return it->second[rectIndex];
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