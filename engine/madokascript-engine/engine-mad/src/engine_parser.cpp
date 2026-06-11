#include "engine_parser.hpp"
#include "engine_ast.hpp"
#include "engine_lexer.hpp"
#include "lexer.hpp"
#include <cstdio>
#include <string>
#include <vector>

bool EngineParser::check_core(TokenType t)
{
    auto& tok = tokens[pos];
    return tok.source == EngineToken::Source::CORE && tok.core_type == t;
}

bool EngineParser::check_engine(EngineTokenType t)
{
    auto& tok = tokens[pos];
    return tok.source == EngineToken::Source::ENGINE && tok.engine_type == t;
}

void EngineParser::expect_core(TokenType ct, const char* err)
{
    if(!check_core(ct))
    {
        printf("parse error: %s (got %s)\n", err, tokens[pos].value.c_str());
        exit(1);
    }
    advance();
}

void EngineParser::expect_engine(EngineTokenType et, const char* err)
{
    if(!check_engine(et))
    {
        printf("parse error: %s (got %s)\n", err, tokens[pos].value.c_str());
        exit(1);
    }
    advance();
}

//PUBLIC
DialogueNodes EngineParser::parse()
{
    DialogueNodes result;

    while(!check_core(TokenType::EOF_))
    {
        if(check_engine(EngineTokenType::DIALOGUES))
        {
            result = parse_dialogues();
        }
        else {
            printf("unexpected token: %s\n", tokens[pos].value.c_str());
            exit(1);
        }
    }
    return result;
}

//PRIVATE

DialogueNodes EngineParser::parse_dialogues()
{
    advance(); //consume dialogue
    expect_engine(EngineTokenType::LBRACE, "expected '{' after DIALOGUES");

    DialogueNodes node;

    while(!check_engine(EngineTokenType::RBRACE) && !check_core(TokenType::EOF_))
    {
        if(check_engine(EngineTokenType::AUTO)){
            node.blocks.push_back(parse_dialogue_block(false)); 
        }
        else if (check_engine(EngineTokenType::INTERACT)) {
            node.blocks.push_back(parse_dialogue_block(true)); 
        }
        else {
            printf("parse error: expected AUTO or INTERACT, got '%s'\n", tokens[pos].value.c_str());
            exit(1);
        }
    }

    expect_engine(EngineTokenType::RBRACE, "expected '}' after DIALOGUES block");
    return node;
}

DialogueBlock EngineParser::parse_dialogue_block(bool is_interact)
{
    advance(); //consume auto or interact
    expect_engine(EngineTokenType::LBRACE,"expected '{'");

    DialogueBlock block;
    block.trigger = is_interact ? DialogueTrigger::INTERACT : DialogueTrigger::AUTO;

    while(!check_engine(EngineTokenType::RBRACE) && !check_core(TokenType::EOF_))
    {
        if(check_engine(EngineTokenType::ID))
        {
            advance();
            expect_core(TokenType::EQUALS, "expected '='");
            block.id = parse_int();
            expect_core(TokenType::SEMICOLON, "expected ';'");
        }
        else if(check_engine(EngineTokenType::NEXT))
        {
            advance();
            expect_core(TokenType::EQUALS, "expected '='");
            block.next = parse_int();
            expect_core(TokenType::SEMICOLON, "expected ';'");
        }
        else if(check_engine(EngineTokenType::ONCE))
        {
            advance();
            expect_core(TokenType::EQUALS, "expected '='");
            block.once = parse_bool();
            expect_core(TokenType::SEMICOLON, "expected ';'");
        }
        else if(check_engine(EngineTokenType::RECT))
        {
            advance();
            expect_core(TokenType::EQUALS, "expected '='");
            parse_rect(block);
            expect_core(TokenType::SEMICOLON, "expected ';'");
        }
        else if(check_engine(EngineTokenType::SPEAKER))
        {
            advance();
            expect_core(TokenType::EQUALS, "expected '='");
            block.speaker = parse_string();
            expect_core(TokenType::SEMICOLON, "expected ';'");
        }
        else if(check_engine(EngineTokenType::LINES))
        {
            advance();
            expect_core(TokenType::EQUALS, "expected '='");
            block.lines = parse_lines();
            expect_core(TokenType::SEMICOLON, "expected ';'");
        }
        else {
            printf("parse error: unknown field '%s'\n", tokens[pos].value.c_str());
            exit(1);
        }
    }
    expect_engine(EngineTokenType::RBRACE, "expected '}'");
    return block;
}

int EngineParser::parse_int()
{
    if(!check_core(TokenType::NUMBER_INT))
    {
        printf("parse error: expected integer (got '%s')\n", tokens[pos].value.c_str());
        exit(1);
    }
    return std::stoi(advance().value);
}

bool EngineParser::parse_bool()
{
    if(!check_core(TokenType::BOOL_LIT))
    {
        printf("parse error: expected bool (got %s)\n", tokens[pos].value.c_str());
        exit(1);
    }
    return advance().value == "true";
}

std::string EngineParser::parse_string()
{
    if(!check_core(TokenType::STRING_LIT))
    {
        printf("parse error: expected string (got %s)\n", tokens[pos].value.c_str());
        exit(1);
    }
    return advance().value;
}

void EngineParser::parse_rect(DialogueBlock& block)
{
    expect_core(TokenType::LPAREN, "expected '(' for rect\n");
    block.rectX = parse_number();
    expect_core(TokenType::COMMA, "expected ','\n");
    block.rectY = parse_number();
    expect_core(TokenType::COMMA, "expected ','\n");
    block.rectW = parse_number();
    expect_core(TokenType::COMMA, "expected ','\n");
    block.rectH = parse_number();
    expect_core(TokenType::RPAREN, "expected ')' for rect\n");
}

float EngineParser::parse_number()
{
    if(check_core(TokenType::NUMBER_INT) || check_core(TokenType::NUMBER_FLOAT))
    {
        return std::stof(advance().value);
    }
    printf("parse error: expected number (got '%s')\n", tokens[pos].value.c_str());
    exit(1);
}

std::vector<std::string> EngineParser::parse_lines()
{
    expect_engine(EngineTokenType::LBRACKET, "expected '['\n");
    std::vector<std::string> lines;

    while(!check_engine(EngineTokenType::RBRACKET) && !check_core(TokenType::EOF_))
    {
        lines.push_back(parse_string());
        if(check_core(TokenType::COMMA)) advance();
    }

    expect_engine(EngineTokenType::RBRACKET, "expected ']'\n");
    return lines;
}