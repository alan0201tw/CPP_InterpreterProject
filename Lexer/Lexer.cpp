#include "Lexer.hpp"
#include "TokenBase.hpp"

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

char Lexer::Peek()
{
    int peekPosition = position + 1;
    if(peekPosition >= (int)text.length())
    {
        return '\0';
    }
    else
    {
        return text[peekPosition];
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

std::string Lexer::RetrieveConstString()
{
    std::string result = "";
    while(isFinished == false && currentChar != '\"')
    {
        //std::cout << Peek() << std::endl;
        result += currentChar;
        Advance();
    }
    //std::cout << result << std::endl;
    return result;
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
        // use this shitty way to avoid unwanted character in source code
        // the start of a string can only be letter or underline
        else if(isalpha(currentChar) || currentChar == '_')
        {
            return TokenFactory::MakeToken(RetrieveConstString());
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
        else if(currentChar == '\"')
        {
            Advance();
            return TokenFactory::MakeToken(std::string("\""));
        }
        else
        {
            throw std::runtime_error(std::string("Lexer.cpp : Get unexpected char : ") + currentChar);
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