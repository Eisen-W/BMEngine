#include "loader.hpp"
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
}