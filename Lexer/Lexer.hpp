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
    // this destructor will help mark this Token class as abstract
    virtual ~Token() = 0;

    virtual std::string ToString();
    virtual TokenType GetTokenType();

protected:
    TokenType tokenType;
};

class IntegerValueToken : public Token
{
public:
    IntegerValueToken(int _value, TokenType _tokenType = TokenType::INTEGER);
    // overriding IToStringInterface
    virtual std::string ToString();
    int GetValue();

private:
    int value;
};

class StringValueToken : public Token
{
public:
    StringValueToken(std::string _value, TokenType _tokenType);
    // overriding IToStringInterface
    virtual std::string ToString();
    std::string GetValue();

private:
    std::string value;
};

class Lexer final
{
public:
    // construct the Lexer instance with program as text
    Lexer(std::string text);
    // this needes to return Tokens with different value types
    // this will be called by Parser
    Token* GetNextToken();

private:
    // utility function
    void ThrowException();
    void Advance();
    void SkipWhitespace();
    
    int RetrieveInteger();
};

std::string GetEnumName(TokenType tokenType);
#endif