#include "Lexer.hpp"

#include <iostream>
#include <sstream>
#include <string>

#include <stdexcept>

// helping mark Token as abstract class
//Token::~Token() {}

Token::Token(std::string _value, TokenType _tokenType)
{
    value = _value;
    tokenType = _tokenType;
}

Token::Token(TokenType _tokenType, std::string _value)
{
    value = _value;
    tokenType = _tokenType;
}

TokenType Token::GetTokenType()
{
    return this->tokenType;
}

std::string Token::GetValue()
{
    return this->value;
}

std::string Token::ToString()
{
    std::stringstream s;
    // don't use + operator!
    s << "Token with TokenType = " << GetEnumName(tokenType) << ", TokenValue = " << value;
    return s.str();
}

Lexer::Lexer(std::string _text)
{
    text = _text;

    position = 0;
    currentChar = text[position];
    isFinished = false;
}

void Lexer::Advance()
{
    position++;
    if(position >= (int)text.length())
    {
        isFinished = true;
    }
    else
    {
        currentChar = text[position];
    }
}

void Lexer::SkipWhitespace()
{
    while(isFinished == false && currentChar == ' ')
    {
        Advance();
    }
}

std::string Lexer::RetrieveIntegerString()
{
    std::string result = "";
    while(isFinished == false && isdigit(currentChar))
    {
        result += currentChar;
        Advance();
    }

    return result;
}

Token* Lexer::GetNextToken()
{
    while(isFinished == false)
    {
        // deal with all kinds of Tokens
        if(currentChar == ' ')
        {
            SkipWhitespace();
        }

        if(isdigit(currentChar))
        {
            return new Token(TokenType::INTEGER, RetrieveIntegerString());
        }
        else if(currentChar == '+')
        {
            Advance();
            return new Token(TokenType::PLUS, "+");
        }
        else if(currentChar == '-')
        {
            Advance();
            return new Token(TokenType::MINUS, "-");
        }
        else if(currentChar == '*')
        {
            Advance();
            return new Token(TokenType::MUL, "*");
        }
        else if(currentChar == '/')
        {
            Advance();
            return new Token(TokenType::DIV, "/");
        }
        else if(currentChar == '(')
        {
            Advance();
            return new Token(TokenType::LPAREN, "(");
        }
        else if(currentChar == ')')
        {
            Advance();
            return new Token(TokenType::RPAREN, ")");
        }
        else
        {
            throw std::runtime_error("Get unexpected char : " + currentChar);
        }
    }

    return new Token(TokenType::EOF_TOKEN, '\0');
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