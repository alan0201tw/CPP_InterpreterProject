#include "Lexer.hpp"

// For Debugging
#include <iostream>
#include <sstream>

// helping mark Token as abstract class
Token::~Token() {}

TokenType Token::GetTokenType()
{
    return this->tokenType;
}

std::string Token::ToString()
{
    std::stringstream s;
    // don't use + operator!
    s << "Token with TokenType = " << GetEnumName(tokenType);
    return s.str();
}

IntegerValueToken::IntegerValueToken(int _value, TokenType _tokenType)
{
    value = _value;
    tokenType = _tokenType;
}

std::string IntegerValueToken::ToString()
{
    std::stringstream s;
    // don't use + operator!
    s << "IntegerValueToken with TokenType = " << GetEnumName(tokenType) << ", TokenValue = " << value;
    return s.str();
}

StringValueToken::StringValueToken(std::string _value, TokenType _tokenType)
{
    value = _value;
    tokenType = _tokenType;
}

std::string StringValueToken::ToString()
{
    std::stringstream s;
    // don't use + operator!
    s << "StringValueToken with TokenType = " << GetEnumName(tokenType) << ", TokenValue = " << value;
    return s.str();
}

// a helper function that turns tokenType to string
std::string GetEnumName(TokenType tokenType)
{
    switch(tokenType)
    {
        case TokenType::INTEGER :
            return "INTEGER";
        case TokenType::PLUS :
        case TokenType::MINUS :
        case TokenType::MUL :
        case TokenType::DIV :
            return "MATH_OPERATOR";
        case TokenType::LPAREN :
        case TokenType::RPAREN :
            return "PARENTHESIS";
        default :
            return "EOF_TOKEN";
    }
}

// No need to call this TemporaryFunction() function,
// it's just to avoid link error.
// https://www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp
// for classes with templates, this kind of "work-around" is needed
void TemporaryFunction ()
{
    //Token<int> tmpToken(5, TokenType::INTEGER);
}