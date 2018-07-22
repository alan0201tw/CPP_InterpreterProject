#include "Lexer/Lexer.hpp"
#include "Parser/Parser.hpp"
#include "Interpreter/Interpreter.hpp"

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    //cout << (int)TokenType::INTEGER << endl;

    //Token<char>* token = new Token<char>('(' , TokenType::LPAREN);
    Token* token = new Token("1139", TokenType::INTEGER);
    cout << token->ToString() << endl;
}