#include "engine_lexer.hpp"
#include "lexer.hpp"
#include <cctype>
#include <vector>

std::vector<EngineToken> EngineLexer::tokenize()
{
    std::vector<EngineToken> tokens;

    while(pos < len)
    {
        skip_whitespace();
        if(pos >= len) break;

        char c = src[pos];

        if(c == '"')                    tokens.push_back(read_string());
        else if(isdigit(c))             tokens.push_back(read_number());
        else if(isalpha(c) || c == '_') tokens.push_back(read_word());
        else                            tokens.push_back(read_symbol());
    }

    // EOF core token
    tokens.push_back({EngineToken::Source::CORE, TokenType::EOF_, {}, ""});
    return tokens;
}

//private functions

void EngineLexer::skip_whitespace()
{
    while(pos < len && (src[pos] == ' ' || src[pos] == '\n' || src[pos] == '\t' || src[pos] == '\r'))
    { pos++; }
}

EngineToken EngineLexer::make_core(TokenType t, std::string val)
{
    return {EngineToken::Source::CORE, t, {}, val};
}

EngineToken EngineLexer::make_engine(EngineTokenType t, std::string val)
{
    return {EngineToken::Source::ENGINE, {}, t, val};
}

EngineToken EngineLexer::read_number()
{
    size_t start = pos;
    bool is_float = false;
    while(pos < len && isdigit(src[pos])) pos++;
    if(pos < len && src[pos] == '.' && isdigit(src[pos + 1]))
    {
        is_float = true;
        pos++;
        while(pos < len && isdigit(src[pos])) pos++;
    }
    std::string val(src + start, pos - start);
    return make_core(is_float ? TokenType::NUMBER_FLOAT : TokenType::NUMBER_INT, val);
}

EngineToken EngineLexer::read_string()
{
    pos++;
    size_t start = pos;
    while(pos < len && src[pos] != '"') pos++;
    std::string val(src + start, pos - start);
    pos++;
    return make_core(TokenType::STRING_LIT, val);
}

EngineToken EngineLexer::read_word()
{
    size_t start = pos;
    while(pos < len && (isalnum(src[pos]) || src[pos] == '_')) pos++;
    std::string word(src + start, pos - start);

    //engine keywords
    if(word == "DIALOGUES") return make_engine(EngineTokenType::DIALOGUES , word);
    if(word == "auto") return make_engine(EngineTokenType::AUTO, word);
    if(word == "interact") return make_engine(EngineTokenType::INTERACT, word);
    if(word == "id") return make_engine(EngineTokenType::ID, word);
    if(word == "next") return make_engine(EngineTokenType::NEXT, word);
    if(word == "once") return make_engine(EngineTokenType::ONCE, word);
    if(word == "rect") return make_engine(EngineTokenType::RECT, word);
    if(word == "speaker") return make_engine(EngineTokenType::SPEAKER, word);
    if(word == "sprite") return make_engine(EngineTokenType::SPRITE, word);
    if(word == "lines") return make_engine(EngineTokenType::LINES, word);

    //core keywords
    if(word == "int") return make_core(TokenType::INT, word);
    if(word == "float") return make_core(TokenType::FLOAT, word);
    if(word == "string") return make_core(TokenType::STRING, word);
    if(word == "bool") return make_core(TokenType::BOOL, word);
    if(word == "true") return make_core(TokenType::BOOL_LIT, word);
    if(word == "false") return make_core(TokenType::BOOL_LIT, word);
    if(word == "SAY")   return make_core(TokenType::SAY, word);

    return make_core(TokenType::IDENT, word);
}

EngineToken EngineLexer::read_symbol()
{
    char c = src[pos++];
    switch(c)
    {
        //engine
        case '{': return make_engine(EngineTokenType::LBRACE, "{");
        case '}': return make_engine(EngineTokenType::RBRACE, "}");
        case '[': return make_engine(EngineTokenType::LBRACKET, "[");
        case ']': return make_engine(EngineTokenType::RBRACKET, "]");

        //core
        case '+': return make_core(TokenType::PLUS, "+");
        case '-': return make_core(TokenType::MINUS, "-");
        case '*': return make_core(TokenType::STAR, "*");
        case '/': return make_core(TokenType::SLASH, "/");
        case '=': return make_core(TokenType::EQUALS, "=");
        case '(': return make_core(TokenType::LPAREN, "(");
        case ')': return make_core(TokenType::RPAREN, ")");
        case ',': return make_core(TokenType::COMMA, ",");
        case ';': return make_core(TokenType::SEMICOLON, ";");
        default:
            printf("unknown char: %c\n", c);
            return read_symbol();
    }
}