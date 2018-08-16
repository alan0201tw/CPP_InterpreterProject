#include "TokenBase.hpp"

IntegerToken::IntegerToken(int _value)
{
    // IMPORTANT : this local tmpVar need to be new-ed, otherwise the same address might
    // be used accross multiple constructor, makeing data corrupted
    //int* tmpVar = new int(_value);
    //data = (void*)tmpVar;

    data.intData = _value;

    valueType = TokenValueType::Integer;

    //std::cout << "IntegerToken Constructor, *_value = " << _value << ", dataPtr = " << data << std::endl;
}

std::string IntegerToken::ToString()
{
    std::stringstream s;
    // don't use + operator!
    //int myInt = *((int*)GetData());

    s << "IntegerToken with data = " << data.intData;

    return s.str();
}

TokenBase* IntegerToken::Add(TokenBase* token)
{
    TokenValueType type = token->GetValueType();
    
    switch(type)
    {
        case TokenValueType::Integer:
        {
            int otherInt = token->GetIntData();
            int myInt = this->GetIntData();
            
            int result = myInt + otherInt;

            return TokenFactory::MakeToken(result);
        }
        case TokenValueType::String:
        {
            std::string otherString = token->GetStringData();

            int myInt = this->GetIntData();
            std::string myString = std::to_string(myInt);
            
            std::string result = myString + otherString;

            //std::cout << "myString = " << myString << ", otherString = " << otherString << std::endl;

            return TokenFactory::MakeToken(result);
        }
        default:
        {
            std::cout << "IntegerToken using unexpected + operator" << std::endl;
            return nullptr;
        }
    }
}

TokenBase* IntegerToken::Minus(TokenBase* token)
{
    TokenValueType type = token->GetValueType();
    
    switch(type)
    {
        case TokenValueType::Integer:
        {
            int otherInt = token->GetIntData();
            int myInt = this->GetIntData();
            
            int result = myInt - otherInt;

            return TokenFactory::MakeToken(result);
        }
        default:
        {
            std::cout << "IntegerToken using unexpected - operator" << std::endl;
            return nullptr;
        }
    }
}

TokenBase* IntegerToken::Multiply(TokenBase* token)
{
    TokenValueType type = token->GetValueType();
    
    switch(type)
    {
        case TokenValueType::Integer:
        {
            int otherInt = token->GetIntData();
            int myInt = this->GetIntData();
            
            int result = myInt * otherInt;

            return TokenFactory::MakeToken(result);
        }
        case TokenValueType::String:
        {
            std::string result = token->Multiply(this)->GetStringData();
            return TokenFactory::MakeToken(result);
        }
        default:
        {
            std::cout << "IntegerToken using unexpected * operator" << std::endl;
            return nullptr;
        }
    }
}

TokenBase* IntegerToken::Divide(TokenBase* token)
{
    TokenValueType type = token->GetValueType();
    
    switch(type)
    {
        case TokenValueType::Integer:
        {
            int otherInt = token->GetIntData();
            int myInt = this->GetIntData();
            
            int result = myInt / otherInt;

            return TokenFactory::MakeToken(result);
        }
        default:
        {
            std::cout << "IntegerToken using unexpected / operator" << std::endl;
            return nullptr;
        }
    }
}
