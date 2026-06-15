#include "engine_interpreter.hpp"
#include "engine_ast.hpp"
#include "interpreter.hpp"
#include <string>

void DialogueInterpreter::load(const ParseResult& result)
{
    blocks.clear();
    fired.clear();
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

        block.rectX = (float)core_interp.eval_node(raw.rectX).num;
        block.rectY = (float)core_interp.eval_node(raw.rectY).num;
        block.rectW = (float)core_interp.eval_node(raw.rectW).num;
        block.rectH = (float)core_interp.eval_node(raw.rectH).num;
        
        blocks.push_back(block);
    }
}

float DialogueInterpreter::eval_expr(ASTNode* node)
{
    Value v = core_interp.eval_node(node);
    return (float)v.num;
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