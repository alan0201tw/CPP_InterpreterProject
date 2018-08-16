#include "TokenBase.hpp"

StringToken::StringToken(std::string _value)
{
    // IMPORTANT : this local tmpVar need to be new-ed, otherwise the same address might
    // be used accross multiple constructor, makeing data corrupted
    //std::string* tmpVar = new std::string(_value);
    //data = (void*)tmpVar;

    data.stringData = _value;

    valueType = TokenValueType::String;

    //std::cout << "StringToken Constructor, *_value = " << _value << ", dataPtr = " << data << std::endl;
}

std::string StringToken::ToString()
{
    std::stringstream s;
    // don't use + operator!
    std::string myString = this->GetStringData();
    s << "StringToken with data = " << myString;

    return s.str();
}

TokenBase* StringToken::Add(TokenBase* token) 
{
    TokenValueType type = token->GetValueType();
    
    switch(type)
    {
        case TokenValueType::Integer:
        {
            int otherInt = token->GetIntData();
            std::string otherString = std::to_string(otherInt);
            
            std::string myString = this->GetStringData();

            std::string result = myString + otherString;

            return TokenFactory::MakeToken(result);
        }
        case TokenValueType::String:
        {
            std::string otherString = token->GetStringData();
            std::string myString = this->GetStringData();
            
            std::string result = myString + otherString;

            return TokenFactory::MakeToken(result);
        }
        default:
        {
            std::cout << "StringToken using unexpected + operator" << std::endl;
            return nullptr;
        }
    }
}
// string token do not support subtraction(minus operator)
TokenBase* StringToken::Minus(TokenBase* token) 
{
    std::cout << "StringToken using unexpected - operator" << std::endl;
    return nullptr;
}
// string token do not support subtraction(minus operator)
TokenBase* StringToken::Multiply(TokenBase* token) 
{
    TokenValueType type = token->GetValueType();
    
    switch(type)
    {
        case TokenValueType::Integer:
        {
            std::string result = "";
            std::string myString = this->GetStringData();

            int otherInt = token->GetIntData();
            if(otherInt < 0)
            {
                std::cout << "StringToken using * operator with negative Integer" << std::endl;
            }

            for(int i = 0; i < otherInt ; i++)
            {
                result += myString;
            }

            return TokenFactory::MakeToken(result);
        }
        default:
        {
            std::cout << "StringToken using unexpected * operator" << std::endl;
            return nullptr;
        }
    }
}
// string token do not support subtraction(minus operator)
TokenBase* StringToken::Divide(TokenBase* token) 
{
    std::cout << "StringToken using unexpected / operator" << std::endl;
    return nullptr;
}
