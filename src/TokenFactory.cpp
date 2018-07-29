#include "TokenBase.hpp"

TokenBase* TokenFactory::MakeToken(int _value)
{
    return new IntegerToken(_value);
}

TokenBase* TokenFactory::MakeToken(std::string _value)
{
    return new StringToken(_value);
}

TokenBase* TokenFactory::MakeEOF_Token()
{
    return new EOF_Token();
}