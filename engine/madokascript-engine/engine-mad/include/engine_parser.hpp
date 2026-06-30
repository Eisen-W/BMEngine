#pragma once

#include "engine_ast.hpp"
#include "engine_lexer.hpp"
#include "lexer.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include <cstddef>
#include <string>
#include <vector>

class EngineParser {
    std::vector<EngineToken> tokens;
    std::vector<Token> core_tokens;
    size_t pos;
    Parser core_parser;

    EngineToken peek() { return tokens[pos]; }
    EngineToken advance() { return tokens[pos++]; }

    bool check_core(TokenType ct);
    bool check_engine(EngineTokenType et);

    void expect_core(TokenType t, const char* err);
    void expect_engine(EngineTokenType t, const char* err);

    static std::vector<Token> build_core_tokens(const std::vector<EngineToken>& toks);

    public:
    EngineParser(std::vector<EngineToken> toks);
    ParseResult parse();

    private:
    //dialogues
    RawDialogueNodes parse_dialogues();
    RawDialogueBlock parse_dialogue_block(bool is_interact);

    //interactables
    RawInteractableNodes parse_interactables();
    RawSwitcherBlock parse_switcher();
    RawMoveableBlock parse_moveable();

    void parse_rect_fields_generic(std::vector<RawRect>& rects);

    ASTNode* parse_rect_expr();

    int parse_int();
    bool parse_bool();
    std::string parse_string();

    InteractDirection parse_dir_string(const std::string& dir);
    void parse_rect_fields(RawDialogueBlock& block);
    RawRect parse_single_rect();

    float parse_number();

    std::vector<std::string> parse_lines();

};