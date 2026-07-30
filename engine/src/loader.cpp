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

void MadLoader::FLoad(const char* madfile)
{
    
    std::string filename(madfile);
    if(filename.size() < 4 || filename.substr(filename.size() - 4) != ".mad")
    {
        printf("error: wrong extension or file not found\n");
        exit(1);
    }

    currentLevelPath = madfile;
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

    //overlay master state onto fresh loaded blocks
    for(auto& block : dialogue_interp.getBlocksMutable())
    {
        StateKey key{currentLevelPath, block.id};
        auto it = masterFiredRects.find(key);
        if(it != masterFiredRects.end()) 
        {
            dialogue_interp.setFiredRects(block.id, it->second);
        }
    }

    for(auto& sw : interact_interp.getSwitchersMutable())
    {
        StateKey key{currentLevelPath, sw.id};
        auto it = masterSwitcherState.find(key);
        if(it != masterSwitcherState.end())
        {
            interact_interp.setSwitcherState(sw.id, it->second);
        }
    }

    for(auto& mv : interact_interp.getMoveablesMutable())
    {
        StateKey key{currentLevelPath, mv.id};
        auto it = masterMoveableState.find(key);
        if(it != masterMoveableState.end())
        {
            interact_interp.setMoveableDestIndex(mv.id, it->second);
        }
    }

    convertDialogueData();
    convertInteractableData();
}

void MadLoader::convertDialogueData()
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
    for(auto& data : getDialogueBlocks())
    {
        for(auto& r : data.rects)
            printf("id=%d rect=(%.0f,%.0f,%.0f,%.0f) dir=%d trigger=%d\n",
            data.id, r.rect.x, r.rect.y, r.rect.width, r.rect.height,
            (int)r.dir, (int)data.trigger);
    }
}

void MadLoader::convertInteractableData()
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
    }
    
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

//==================DIALOGUE PASSTHROUGHS=========================
const std::vector<DialogueData>& MadLoader::getDialogueBlocks() const { return d_data; } 
void MadLoader::startDialogue(int id, int rectIndex) { dialogue_interp.startDialogue(id, rectIndex); }
void MadLoader::advanceDialogue() { dialogue_interp.advance(); }
bool MadLoader::dialogueRunning() const { return dialogue_interp.isRunning(); }
bool MadLoader::hasFiredRect(int id, int rectIndex) const
{
    return dialogue_interp.hasFiredRect(id, rectIndex);
}

void MadLoader::saveDialogueState(FILE* f) const 
{ 
    printf("saveDialogue: file pos=%ld\n", ftell(f));
    int count = (int)masterFiredRects.size();
    fwrite(&count, sizeof(int), 1, f);
    for(auto& fr : masterFiredRects)
    {
        int pathLen = (int)fr.first.levelPath.size();
        fwrite(&pathLen, sizeof(int), 1, f);
        fwrite(fr.first.levelPath.c_str(),1,pathLen, f);
        fwrite(&fr.first.id, sizeof(int), 1, f);

        int rectCount = (int)fr.second.size();
        fwrite(&rectCount, sizeof(int), 1, f);
        for(bool b : fr.second)
        {
            int val = b ? 1 : 0;
            fwrite(&val, sizeof(int), 1, f);
        }
    }
    printf("saveDialogue: masterFiredRects count=%d\n", count);
}

void MadLoader::loadDialogueState(FILE* f) 
{ 
    printf("loadDialogue: file pos=%ld\n", ftell(f));
    int count = 0;
    fread(&count, sizeof(int), 1, f);
    printf("loadDialogue: read count=%d\n", count);
    for(int i = 0; i < count; i++)
    {
        int pathLen = 0;
        fread(&pathLen, sizeof(int), 1, f);
        std::string path(pathLen, '\0');
        fread(&path[0], 1, pathLen, f);
        int id = 0;
        fread(&id, sizeof(int), 1, f);
        int rectCount = 0;
        fread(&rectCount, sizeof(int), 1, f);
        std::vector<bool> fired(rectCount, false);
        for(int j = 0; j < rectCount; j++)
        {
            int val = 0;
            fread(&val, sizeof(int), 1, f);
            fired[j] = val != 0;
        }
        masterFiredRects[{path, id}] = fired;
    }
}

const DialogueData* MadLoader::currentDialogue() const
{
    const DialogueBlock* block = dialogue_interp.current();
    if(!block) return nullptr;

    for(auto& data : d_data)
    {
        if(data.id == block->id) return &data;
    }
    return nullptr;
}

std::string MadLoader::buildRaw(const DialogueData& data) const
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
const std::vector<SwitcherData>& MadLoader::getSwitchers() const { return switcher_data; }
bool MadLoader::getSwitcherState(int id) const { return interact_interp.getSwitcherState(id); }
void MadLoader::setSwitcherState(int id, bool value) { interact_interp.setSwitcherState(id, value); }
bool MadLoader::isMoveableSolved(int id) const { return interact_interp.isMoveableSolved(id); }

// MOVEABLES
const std::vector<MoveableData>& MadLoader::getMoveables() const { return moveable_data; }
int MadLoader::getMoveableDestIndex(int id) const { return interact_interp.getMoveableDestIndex(id); }

void MadLoader::setMoveableDestIndex(int id, int destIndex)
{
    interact_interp.setMoveableDestIndex(id, destIndex);
    convertInteractableData();
}

void MadLoader::saveInteractableState(FILE* f) const 
{
    printf("saveInteractable: file pos=%ld\n", ftell(f));
    interact_interp.saveState(f); 
}

void MadLoader::loadInteractableState(FILE* f)
{
    printf("loadInteractable: file pos=%ld\n", ftell(f));
    interact_interp.loadState(f);
    convertInteractableData();
}
