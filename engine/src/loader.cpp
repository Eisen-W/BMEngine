#include "loader.hpp"
#include "mad_data.hpp"
#include "engine_ast.hpp"
#include "engine_interpreter.hpp"
#include "engine_lexer.hpp"
#include "engine_parser.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

//=======================DIALOGUE FILE=================================
void Loader::FLoad(const char* madfile)
{
    
    std::string filename(madfile);
    if(filename.size() < 4 || filename.substr(filename.size() - 4) != ".mad")
    {
        printf("error: wrong extension or file not found\n");
        exit(1);
    }

    FILE* f = fopen(madfile, "r");
    if(!f)
    {
        printf("could not open file: %s\n", madfile);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char* src = (char*)malloc(size + 1);
    fread(src, 1, size, f);
    src[size] = '\0';
    fclose(f);

    EngineLexer lexer(src);
    auto tokens = lexer.tokenize();

    EngineParser parser(tokens);
    ParseResult result = parser.parse();

    free(src);

    for(auto* node : result.core_statements) core_interp.exec_node(node);
    dialogue_interp.load(result, core_interp);
    interact_interp.load(result, core_interp);

    convertDialogueData();
    convertInteractableData();
}

void Loader::convertDialogueData()
{
    //convert DialogueBlock to DialogueData
    d_data.clear();
    for(auto& block : dialogue_interp.getBlocks())
    {
        DialogueData data;
        data.id = block.id;
        data.next = block.next;
        data.once = block.once;
        data.trigger = block.trigger;
        data.speaker = block.speaker;
        data.sprite = block.sprite;
        data.lines = block.lines;

        for(auto& r : block.rects)
        {
            DialogueRect dr;
            dr.rect = {r.x, r.y, r.w, r.h};
            dr.dir = r.dir;
            data.rects.push_back(dr);
        }
        d_data.push_back(data);
    }
}

void Loader::convertInteractableData()
{
    switcher_data.clear();
    for(auto& block : interact_interp.getSwitchers())
    {
        SwitcherData data;
        data.id = block.id;
        data.name = block.name;
        for(auto& r : block.rects)
        {
            data.rects.push_back({{r.x, r.y, r.w, r.h}, r.dir});   
        }
        switcher_data.push_back(data);

        moveable_data.clear();
        for(auto& block : interact_interp.getMoveables())
        {
            MoveableData data;
            data.id = block.id;
            data.name = block.name;
            data.start = {block.start.x, block.start.y, block.start.w, block.start.h};

            for(auto& d : block.dest)
            {
                data.dest.push_back({d.x, d.y, d.w, d.h});
            }
            data.current = {block.current.x, block.current.y, block.current.w, block.current.h};
            moveable_data.push_back(data);
        }
    }
}

//==================DIALOGUE PASSTHROUGHS=========================
const std::vector<DialogueData>& Loader::getDialogueBlocks() const { return d_data; } 
void Loader::startDialogue(int id, int rectIndex) { dialogue_interp.startDialogue(id, rectIndex); }
void Loader::advanceDialogue() { dialogue_interp.advance(); }
bool Loader::dialogueRunning() const { return dialogue_interp.isRunning(); }
bool Loader::hasFiredRect(int id, int rectIndex) const
{
    return dialogue_interp.hasFiredRect(id, rectIndex);
}

void Loader::saveDialogueState(FILE* f) const { dialogue_interp.saveFiredRects(f); }
void Loader::loadDialogueState(FILE* f) { dialogue_interp.loadFiredRects(f); }

const DialogueData* Loader::currentDialogue() const
{
    const DialogueBlock* block = dialogue_interp.current();
    if(!block) return nullptr;

    for(auto& data : d_data)
    {
        if(data.id == block->id) return &data;
    }
    return nullptr;
}

std::string Loader::buildRaw(const DialogueData& data) const
{
    std::string raw;
    for(int i = 0; i < (int)data.lines.size(); i++)
    {
        raw += data.lines[i];
        if(i < (int)data.lines.size() - 1) raw += '|';
    }
    return raw;
}

//=================INTERACTABLE PASSTHROUGHS==================
// SWITCHERS
const std::vector<SwitcherData>& Loader::getSwitchers() const { return switcher_data; }
bool Loader::getSwitcherState(int id) const { return interact_interp.getSwitcherState(id); }
void Loader::setSwitcherState(int id, bool value) { interact_interp.setSwitcherState(id, value); }

// MOVEABLES
const std::vector<MoveableData>& Loader::getMoveables() const { return moveable_data; }
int Loader::getMoveableDestIndex(int id) const { return interact_interp.getMoveableDestIndex(id); }

void Loader::setMoveableDestIndex(int id, int destIndex)
{
    interact_interp.setMoveableDestIndex(id, destIndex);
    convertInteractableData();
}

void Loader::saveInteractableState(FILE* f) const { interact_interp.saveState(f); }
void Loader::loadInteractableState(FILE* f)
{
    interact_interp.loadState(f);
    convertInteractableData();
}