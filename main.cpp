#include "Lexer/Lexer.hpp"
#include "Parser/Parser.hpp"
#include "Interpreter/Interpreter.hpp"

#include "Lexer/TokenFactory.hpp"

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    TokenBase* token = TokenFactory::MakeToken(5);
    token = token->Add(TokenFactory::MakeToken(88123));

    std::cout << token->ToString() << std::endl;
}