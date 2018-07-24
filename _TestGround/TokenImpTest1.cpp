#include "../Lexer/TokenBase.hpp"
#include "../Lexer/TokenFactory.hpp"

#include <iostream>

int main()
{
    int a = 5, b = 7;

    TokenBase* intToken5 = TokenFactory::MakeToken(a);
    TokenBase* intToken7 = TokenFactory::MakeToken(b);
    TokenBase* token = intToken5->Add(intToken7);
    token = token->Add(intToken5);

    std::cout << token->ToString() << std::endl;
}