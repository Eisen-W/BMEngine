#pragma once

#include "engine_ast.hpp"
#include "engine_lexer.hpp"
#include "lexer.hpp"
#include <cstddef>
#include <string>
#include <vector>

class EngineParser {
    std::vector<EngineToken> tokens;
    size_t pos;

    EngineToken peek() { return tokens[pos]; }
    EngineToken advance() { return tokens[pos++]; }

    bool check_core(TokenType ct);
    bool check_engine(EngineTokenType et);

    void expect_core(TokenType t, const char* err);
    void expect_engine(EngineTokenType t, const char* err);

    public:
    EngineParser(std::vector<EngineToken> toks) : tokens(std::move(toks)), pos(0) {}

    DialogueNodes parse();

    private:
    DialogueNodes parse_dialogues();
    DialogueBlock parse_dialogue_block(bool is_interact);

    int parse_int();
    bool parse_bool();
    std::string parse_string();

    void parse_rect(DialogueBlock& block);

    float parse_number();

    std::vector<std::string> parse_lines();

};