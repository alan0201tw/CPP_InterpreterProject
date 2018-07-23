#ifndef TOKEN_FACTORY
#define TOKEN_FACTORY

#include "TokenBase.hpp"

class TokenFactory
{
public:
    TokenBase* MakeToken(int _value)
    {
        return new IntegerToken(_value);
    }
    //TokenBase* MakeToken(float);
};

#endif
