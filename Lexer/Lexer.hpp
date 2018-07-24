#ifndef PASCAL_LEXER
#define PASCAL_LEXER

#include "../BasicInterface/DebugUtility.hpp"
#include "TokenBase.hpp"

#include <string>

class Lexer final
{
public:
    // construct the Lexer instance with program as text
    Lexer(std::string _text);
    // this needes to return Tokens with different value types
    // this will be called by Parser
    TokenBase* GetNextToken();

private:
    // utility function
    void ThrowException();
    void Advance();
    char Peek();
    void SkipWhitespace();
    
    int RetrieveInteger();
    std::string RetrieveConstString();

    std::string text;
    int position;
    char currentChar;

    bool isFinished;
};
#endif