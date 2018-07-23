#include "TokenBase.hpp"
#include "TokenFactory.hpp"

#include <iostream>

int main()
{
    TokenFactory fac;

    int a = 5, b = 7;

    TokenBase* intToken5 = fac.MakeToken(a);
    TokenBase* intToken7 = fac.MakeToken(b);

    TokenBase* token = intToken5->Add(intToken7);
    token = token->Add(intToken5);

    std::cout << token->ToString() << std::endl;
}