#ifndef TOKEN_FACTORY
#define TOKEN_FACTORY

#include "TokenBase.hpp"

class TokenFactory
{
public:
    static TokenBase* MakeToken(int _value)
    {
        return new IntegerToken(_value);
    }
    static TokenBase* MakeToken(std::string _value)
    {
        //return new StringToken();
        return nullptr;
    }
    static TokenBase* MakeEOF_Token()
    {
        //return new EOF_Token();
        return nullptr;
    }
    //TokenBase* MakeToken(float);
};

#endif
