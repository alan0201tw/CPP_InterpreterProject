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
    // 0 for idle, 1 for starting to read, 2 for finish reading
    StringReadingState = ReadingStatus::Idle;
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

TokenBase* Lexer::GetTokenById()
{
    std::string result = "";
    while(isFinished == false && isalnum(currentChar))
    {
        result += currentChar;
        Advance();
    }
    // this result is identifier
    TokenBase* token = TokenFactory::MakeToken(result);
    return token;
}

TokenBase* Lexer::GetNextToken()
{
    while(isFinished == false)
    {
        // when read a newline char, ignore it
        if(currentChar == '\r' || currentChar == '\n')
        {
            Advance();
            continue;
        }

        // if the Lexer is trying to read a string, don't do any preprocessing
        // just return a const string token
        if(StringReadingState == ReadingStatus::ReadyToRead)
        {
            TokenBase* token = TokenFactory::MakeToken(RetrieveConstString());
            StringReadingState = ReadingStatus::FinishReading;
            return token;
        }

        // deal with all kinds of Tokens
        if(currentChar == ' ')
        {
            SkipWhitespace();
        }
        // TODO : floating point value support
        if(isdigit(currentChar))
        {
            return TokenFactory::MakeToken(RetrieveInteger());
            //return new Token(TokenValueType::INTEGER, RetrieveIntegerString());
        }
        // use this shitty way to avoid unwanted character in source code
        // the start of a string can only be letter or underline
        // this StringToken can be either a const string value, or a keyword
        else if(isalpha(currentChar) || currentChar == '_')
        {
            return GetTokenById();
        }
        else if(currentChar == ':' && Peek() == '=')
        {
            Advance();
            Advance();
            return TokenFactory::MakeToken(std::string(":="));
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
        else if(currentChar == '.')
        {
            Advance();
            return TokenFactory::MakeToken(std::string("."));
        }
        else if(currentChar == ';')
        {
            Advance();
            return TokenFactory::MakeToken(std::string(";"));
        }
        else if(currentChar == '\"')
        {
            Advance();
            // change reading string state
            if(StringReadingState == ReadingStatus::Idle)
            {
                StringReadingState = ReadingStatus::ReadyToRead;
            }
            else if(StringReadingState == ReadingStatus::FinishReading)
            {
                StringReadingState = ReadingStatus::Idle;
            }
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