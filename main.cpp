#include "engine_ast.hpp"
#include "engine_lexer.hpp"
#include "engine_parser.hpp"

#include <cstdio>
#include <string>

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("usage: mad <file.mad>\n");
        return 1;
    }
    FILE* f = fopen(argv[1], "r");
    std::string filename(argv[1]);
    if(filename.size() < 4 || filename.substr(filename.size() - 4) != ".mad")
    {
        printf("error: wrong extension or file not found\n");
        return 1;
    }
    if(!f)
    {
        printf("could not open file: %s\n", argv[1]);
        return 1;
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

    
    for(auto& t : tokens)
    {
        printf("source: %d, type: %d, value: %s\n", (int)t.source, (int)t.engine_type, t.value.c_str());
    }
    
    
    EngineParser parser(tokens);
    ParseResult result = parser.parse();

    //Interpreter interp;
    //interp.run(ast);

    for(auto& block : result.dialogues.blocks)
    {
        printf("id=%d, next=%d, speaker=%s, lines=%zu\n", block.id, block.next, block.speaker.c_str(), block.lines.size());
    }

    free(src);
    return 0;
}