#ifndef PASCAL_LEXER
#define PASCAL_LEXER

#include "DebugUtility.hpp"
#include "TokenBase.hpp"

#include <string>
#include <vector>
#include <set>

enum class ReadingStatus : unsigned short int
{
    Idle,
    ReadyToRead,
    FinishReading
};

class Lexer final
{
public:
    // construct the Lexer instance with program as text
    Lexer(std::string _text);
    // this needes to return Tokens with different value types
    // this will be called by Parser
    TokenBase* GetNextToken();
    // for Parser to use, to determine whether a string is a variable or a keyword
    bool IsStringReservedKeyword(std::string _value);

private:
    // utility function
    void ThrowException();
    void Advance();
    char Peek();
    void SkipWhitespace();
    // for getting constant values
    int RetrieveInteger();
    std::string RetrieveConstString();
    // for recognizing keywords and variable names
    TokenBase* GetTokenById();

    // use this to define keywords
    std::set<std::string> ReservedKeyWords
    {
        "BEGIN", "END"
    };

    std::string text;
    size_t position;
    char currentChar;

    bool isFinished;
    ReadingStatus StringReadingState;
};
#endif