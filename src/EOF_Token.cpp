#include "TokenBase.hpp"

EOF_Token::EOF_Token()
{
    data = nullptr;
    valueType = TokenValueType::EOF_Token;

    //std::cout << "EOF_Token Constructor" << std::endl;
}

std::string EOF_Token::ToString()
{
    return std::string("EOF_Token String");
}

TokenBase* EOF_Token::Add(TokenBase* token) 
{
    throw new std::runtime_error(std::string("EOF_Token using unexpected + operator"));
    return nullptr;
}

TokenBase* EOF_Token::Minus(TokenBase* token) 
{
    throw new std::runtime_error(std::string("EOF_Token using unexpected - operator"));
    return nullptr;
}

TokenBase* EOF_Token::Multiply(TokenBase* token) 
{
    throw new std::runtime_error(std::string("EOF_Token using unexpected * operator"));
    return nullptr;
}

TokenBase* EOF_Token::Divide(TokenBase* token) 
{
    throw new std::runtime_error(std::string("EOF_Token using unexpected / operator"));
    return nullptr;
}