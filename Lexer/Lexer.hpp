#ifndef PASCAL_LEXER
#define PASCAL_LEXER

#include "../BasicInterface/DebugUtility.hpp"
#include <string>

enum class TokenType : unsigned short int
{
    INTEGER,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LPAREN,
    RPAREN,
    EOF_TOKEN
};

class Token : public IToStringInterface
{
public:
    Token(std::string _value, TokenType _tokenType);
    Token(TokenType _tokenType, std::string _value);

    std::string ToString();
    TokenType GetTokenType();
    std::string GetValue();

private:
    TokenType tokenType;
    std::string value;
};

class Lexer final
{
public:
    // construct the Lexer instance with program as text
    Lexer(std::string _text);
    // this needes to return Tokens with different value types
    // this will be called by Parser
    Token* GetNextToken();

private:
    // utility function
    void ThrowException();
    void Advance();
    void SkipWhitespace();
    
    std::string RetrieveIntegerString();

    std::string text;
    int position;
    char currentChar;

    bool isFinished;
};

std::string GetEnumName(TokenType tokenType);
#endif