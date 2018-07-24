#include "Lexer.hpp"
#include "TokenBase.hpp"
#include "TokenFactory.hpp"

#include <iostream>
#include <sstream>
#include <string>

#include <stdexcept>

// helping mark Token as abstract class
//Token::~Token() {}

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

int Lexer::RetrieveInteger()
{
    std::string result = "";
    while(isFinished == false && isdigit(currentChar))
    {
        result += currentChar;
        Advance();
    }

    return std::stoi(result);
}

TokenBase* Lexer::GetNextToken()
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
            return TokenFactory::MakeToken(RetrieveInteger());
            //return new Token(TokenValueType::INTEGER, RetrieveIntegerString());
        }
        else if(currentChar == '+')
        {
            Advance();
            return TokenFactory::MakeToken(std::string("+"));
        }
        else if(currentChar == '-')
        {
            Advance();
            return TokenFactory::MakeToken(std::string("-"));
        }
        else if(currentChar == '*')
        {
            Advance();
            return TokenFactory::MakeToken(std::string("*"));
        }
        else if(currentChar == '/')
        {
            Advance();
            return TokenFactory::MakeToken(std::string("/"));
        }
        else if(currentChar == '(')
        {
            Advance();
            return TokenFactory::MakeToken(std::string("("));
        }
        else if(currentChar == ')')
        {
            Advance();
            return TokenFactory::MakeToken(std::string(")"));
        }
        else
        {
            throw std::runtime_error(std::string("Get unexpected char : ") + currentChar);
        }
    }

    return TokenFactory::MakeEOF_Token();
}

// No need to call this TemporaryFunction() function,
// it's just to avoid link error.
// https://www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp
// for classes with templates, this kind of "work-around" is needed
void TemporaryFunction ()
{
    //Token<int> tmpToken(5, TokenType::INTEGER);
}