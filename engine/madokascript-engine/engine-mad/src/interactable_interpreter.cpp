#include "interactable_interpreter.hpp"
#include "engine_ast.hpp"

void InteractableInterpreter::load(const ParseResult& result, Interpreter& core_interp)
{
    switchers.clear();
    moveables.clear();
    switcherState.clear();
    moveableState.clear();

    for(auto& raw : result.interactables.switchers)
    {
        SwitcherBlock block;
        block.id = raw.id;
        block.name = raw.name;
        for(auto& r : raw.rects)
        {
            MRect rect;
            rect.x = (float)core_interp.eval_node(r.x).num;
            rect.y = (float)core_interp.eval_node(r.y).num;
            rect.w = (float)core_interp.eval_node(r.w).num;
            rect.h = (float)core_interp.eval_node(r.h).num;
            rect.dir = r.dir;
            block.rects.push_back(rect);
        }
        switcherState[block.id] = false;
        switchers.push_back(block);
    }

    for(auto& raw : result.interactables.moveables)
    {
        MoveableBlock block;
        block.id = raw.id;
        block.name = raw.name;
        block.start.x = (float)core_interp.eval_node(raw.start.x).num;
        block.start.y = (float)core_interp.eval_node(raw.start.y).num;
        block.start.w = (float)core_interp.eval_node(raw.start.w).num;
        block.start.h = (float)core_interp.eval_node(raw.start.h).num;

        for(auto& r : raw.dest)
        {
            MRect rect;
            rect.x = (float)core_interp.eval_node(r.x).num;
            rect.y = (float)core_interp.eval_node(r.y).num;
            rect.w = (float)core_interp.eval_node(r.w).num;
            rect.h = (float)core_interp.eval_node(r.h).num;
            rect.dir = r.dir;
            block.dest.push_back(rect);
        }
        moveableState[block.id] = -1; //unsolved by default
        ResolveMoveablePos(block);
        moveables.push_back(block);
    }
}


//====================SWITCHER===================
bool InteractableInterpreter::getSwitcherState(int id) const
{
    auto it = switcherState.find(id);
    return it != switcherState.end() ? it->second : false; 
}

void InteractableInterpreter::setSwitcherState(int id, bool value)
{
    switcherState[id] = value;
}

const std::vector<SwitcherBlock>& InteractableInterpreter::getSwitchers() const
{
    return switchers;
}


//===================MOVEABLES========================
void InteractableInterpreter::ResolveMoveablePos(MoveableBlock& mb)
{
    int idx = moveableState[mb.id];
    if(idx >= 0 && idx < (int)mb.dest.size())
    {
        mb.current = mb.dest[idx];
    }
    else {
        mb.current = mb.start;
    }
}

int InteractableInterpreter::getMoveableDestIndex(int id) const
{
    auto it = moveableState.find(id);
    return it != moveableState.end() ? it->second : -1;
}

void InteractableInterpreter::setMoveableDestIndex(int id, int destIndex)
{
    moveableState[id] = destIndex;
    MoveableBlock* mb = findMoveableByID(id);
    if(mb) ResolveMoveablePos(*mb);
}

const std::vector<MoveableBlock>& InteractableInterpreter::getMoveables() const
{
    return moveables;
}

MoveableBlock* InteractableInterpreter::findMoveableByID(int id)
{
    for(auto& mb : moveables)
    {
        if(mb.id == id) return &mb;
    }
    return nullptr;
}

std::vector<SwitcherBlock>& InteractableInterpreter::getSwitchersMutable()
{
    return switchers;
}

std::vector<MoveableBlock>& InteractableInterpreter::getMoveablesMutable()
{
    return moveables;
}

void InteractableInterpreter::saveState(FILE* f) const
{
    int swCount = (int)switcherState.size();
    fwrite(&swCount, sizeof(int), 1, f);
    for(auto& ss : switcherState)
    {
        int id = ss.first, val = ss.second ? 1 : 0;
        fwrite(&id, sizeof(int), 1, f);
        fwrite(&val, sizeof(int), 1, f);
    }

    int mvCount = (int)moveableState.size();
    fwrite(&mvCount, sizeof(int), 1, f);
    for(auto& ms : moveableState)
    {
        int id = ms.first, idx = ms.second;
        fwrite(&id, sizeof(int), 1, f);
        fwrite(&idx, sizeof(int), 1, f);
    }

    printf("saveState: swCount=%d mvCount=%d\n", (int)switcherState.size(), (int)moveableState.size());
    for(auto& p : moveableState)
    {
        printf("saveState: moveable id=%d destIndex=%d\n", p.first, p.second);
    }
}

void InteractableInterpreter::loadState(FILE* f)
{
    int swCount = 0;
    fread(&swCount, sizeof(int), 1, f);
    printf("loadstate: swCount = %d\n", swCount);
    for(int i = 0; i < swCount; i++)
    {
        int id, val;
        fread(&id, sizeof(int), 1, f);
        fread(&val, sizeof(int), 1, f);
        switcherState[id] = val != 0;
        printf("loadState: switcher id=%d val=%d\n", id, val);
    }

    int mvCount;
    fread(&mvCount, sizeof(int), 1, f);
    printf("loadState: mvCount=%d\n", mvCount);
    for(int i = 0; i < mvCount; i++)
    {
        int id, idx;
        fread(&id, sizeof(int), 1, f);
        fread(&idx, sizeof(int), 1, f);
        moveableState[id] = idx;
        printf("loadState: moveable id=%d destIndex=%d\n", id, idx);
    }

    for(auto& m : moveables) 
    { 
        ResolveMoveablePos(m); 
        printf("loadState: resolved id=%d current=(%.0f,%.0f)\n", m.id, m.current.x, m.current.y);
    }
}
