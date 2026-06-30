#pragma once
#include "lexer.hpp"
#include <cstring>
#include <vector>

enum class EngineTokenType {
    // engine keywords
    DIALOGUES,
    AUTO,
    INTERACT,

    //dialogue fields
    ID, NEXT, ONCE, RECT, SPEAKER, SPRITE, LINES,

    // extra symbols
    LBRACE, RBRACE,     // {}        
    LBRACKET, RBRACKET, // []

    //interactable tokens
    INTERACTABLES, SWITCHER, MOVEABLE,
    NAME,
    START, DEST
};

struct EngineToken {
    enum class Source { CORE, ENGINE } source;
    TokenType core_type;
    EngineTokenType engine_type;
    std::string value;
};

class EngineLexer {
    const char* src;
    size_t pos;
    size_t len;

    public:
    EngineLexer(const char* source) : src(source), pos(0), len(strlen(source)) {}

    std::vector<EngineToken> tokenize();

    private:
    void skip_whitespace();
    EngineToken make_core(TokenType t, std::string val);
    EngineToken make_engine(EngineTokenType t, std::string val);
    EngineToken read_number();
    EngineToken read_string();
    EngineToken read_word();
    EngineToken read_symbol();
};