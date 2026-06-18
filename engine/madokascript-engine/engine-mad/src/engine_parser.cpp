#include "engine_parser.hpp"
#include "engine_ast.hpp"
#include "engine_lexer.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include <cstdio>
#include <string>
#include <vector>

std::vector<Token> EngineParser::build_core_tokens(const std::vector<EngineToken>& toks)
{
    std::vector<Token> result;
    for(auto& et : toks)
    {
        if(et.source == EngineToken::Source::CORE)
        {
            result.push_back({et.core_type, et.value});
        }
        else {
            result.push_back({TokenType::EOF_, ""});
        }
    }
    return result;

}

EngineParser::EngineParser(std::vector<EngineToken> toks) : tokens(std::move(toks)), pos(0), 
                                                            core_tokens(build_core_tokens(tokens)),
                                                            core_parser(core_tokens, pos)
{}

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
ParseResult EngineParser::parse()
{
    ParseResult result;

    while(!check_core(TokenType::EOF_))
    {
        if(check_engine(EngineTokenType::DIALOGUES))
        {
            result.dialogues = parse_dialogues();
        }
        else if(check_core(TokenType::INT) ||
                check_core(TokenType::FLOAT) ||
                check_core(TokenType::STRING) ||
                check_core(TokenType::BOOL))
        {
            ASTNode* node = core_parser.parse_statement();
            result.core_statements.push_back(node);
        }
        else {
            printf("unexpected token: %s\n", tokens[pos].value.c_str());
            exit(1);
        }
    }
    return result;
}

//PRIVATE

RawDialogueNodes EngineParser::parse_dialogues()
{
    advance(); //consume dialogue
    expect_engine(EngineTokenType::LBRACE, "expected '{' after DIALOGUES");

    RawDialogueNodes node;

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

RawDialogueBlock EngineParser::parse_dialogue_block(bool is_interact)
{
    advance(); //consume auto or interact
    expect_engine(EngineTokenType::LBRACE,"expected '{'");

    RawDialogueBlock block;
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
            parse_rect_fields(block);
            expect_core(TokenType::SEMICOLON, "expected ';'");
        }
        else if(check_engine(EngineTokenType::SPEAKER))
        {
            advance();
            expect_core(TokenType::EQUALS, "expected '='");
            block.speaker = parse_string();
            expect_core(TokenType::SEMICOLON, "expected ';'");
        }
        else if(check_engine(EngineTokenType::SPRITE))
        {
            advance();
            expect_core(TokenType::EQUALS, "expected '='");
            block.sprite = parse_string();
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

InteractDirection EngineParser::parse_dir_string(const std::string& dir)
{
    if(dir == "up")     return InteractDirection::UP;
    if(dir == "down")   return InteractDirection::DOWN;
    if(dir == "left")   return InteractDirection::LEFT;
    if(dir == "right")  return InteractDirection::RIGHT;
    return InteractDirection::ANY;
}

void EngineParser::parse_rect_fields(RawDialogueBlock& block)
{
    if(check_engine(EngineTokenType::LBRACKET))
    {
        advance();  //consume '['
        while(!check_engine(EngineTokenType::RBRACKET) && !check_core(TokenType::EOF_))
        {
            block.rects.push_back(parse_single_rect());
            if(check_core(TokenType::COMMA)) advance();
        }
        expect_engine(EngineTokenType::RBRACKET, "expected ']'");
    }
    else {
        block.rects.push_back(parse_single_rect());
    }
}

RawRect EngineParser::parse_single_rect()
{
    expect_core(TokenType::LPAREN, "expected '(' for rect\n");
    RawRect r;
    r.x = core_parser.parse_expr();
    expect_core(TokenType::COMMA, "expected ','\n");
    r.y = core_parser.parse_expr();
    expect_core(TokenType::COMMA, "expected ','\n");
    r.w = core_parser.parse_expr();
    expect_core(TokenType::COMMA, "expected ','\n");
    r.h = core_parser.parse_expr();

    if(check_core(TokenType::COMMA))
    {
        advance();
        if(!check_core(TokenType::STRING_LIT))
        {
            printf("parse error: expected direction string\n");
            exit(1);
        }
        r.dir = parse_dir_string(advance().value);
    }
    expect_core(TokenType::RPAREN, "expected ')' for rect");
    return r;
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

ASTNode* EngineParser::parse_rect_expr()
{
    return core_parser.parse_expr();
}