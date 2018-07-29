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
    std::cout << "EOF_Token using unexpected + operator" << std::endl;
    return nullptr;
}

TokenBase* EOF_Token::Minus(TokenBase* token) 
{
    std::cout << "EOF_Token using unexpected - operator" << std::endl;
    return nullptr;
}

TokenBase* EOF_Token::Multiply(TokenBase* token) 
{
    std::cout << "EOF_Token using unexpected * operator" << std::endl;
    return nullptr;
}

TokenBase* EOF_Token::Divide(TokenBase* token) 
{
    std::cout << "EOF_Token using unexpected / operator" << std::endl;
    return nullptr;
}