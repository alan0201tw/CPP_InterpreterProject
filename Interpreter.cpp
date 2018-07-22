#include "Lexer/Lexer.hpp"
#include "Parser/Parser.hpp"

#include <iostream>

using namespace std;

class NodeVisitor
{
public:
    void Visit()
    {

    }
};

int main(int argc, char* argv[])
{
    //cout << (int)TokenType::INTEGER << endl;

    //Token<char>* token = new Token<char>('(' , TokenType::LPAREN);
    Token* token = new IntegerValueToken(1139);
    cout << token->ToString() << endl;

    token = new StringValueToken("(" , TokenType::LPAREN);
    cout << token->ToString() << endl;
}