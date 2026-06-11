#include "loader.hpp"
#include "dialogue.hpp"
#include "engine_ast.hpp"
#include "engine_interpreter.hpp"
#include "engine_lexer.hpp"
#include "engine_parser.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>

//=======================DIALOGUE FILE=================================
void Loader::DLoad(const char* dialogue_filepath)
{
    FILE* f = fopen(dialogue_filepath, "r");
    std::string filename(dialogue_filepath);
    if(filename.size() < 4 || filename.substr(filename.size() - 4) != ".mad")
    {
        printf("error: wrong extension or file not found\n");
        exit(1);
    }
    if(!f)
    {
        printf("could not open file: %s\n", dialogue_filepath);
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
    DialogueNodes dialogues = parser.parse();

    free(src);

    dialogue_interp.load(dialogues);

    //convert DialogueBlock to DialogueData
    d_data.clear();
    for(auto& block : dialogue_interp.getBlocks())
    {
        DialogueData data;
        data.id = block.id;
        data.next = block.next;
        data.once = block.once;
        data.trigger =  (block.trigger == DialogueTrigger::INTERACT)
                        ? DialogueTrigger::INTERACT 
                        : DialogueTrigger::AUTO;
        data.rect = {block.rectX, block.rectY, block.rectW, block.rectH};
        data.speaker = block.speaker;
        data.lines = block.lines;
        d_data.push_back(data);

    }
}

const std::vector<DialogueData>& Loader::getDialogueBlocks() const
{
    return d_data;
}

void Loader::startDialogue(int id)
{
    dialogue_interp.startDialogue(id);
}

void Loader::advanceDialogue()
{
    dialogue_interp.advance();
}

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

bool Loader::dialogueRunning() const
{
    return dialogue_interp.isRunning();
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

bool Loader::hasFired(int id) const
{
    return dialogue_interp.hasFired(id);
}