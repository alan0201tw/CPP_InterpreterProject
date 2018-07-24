#include "Lexer/Lexer.hpp"
#include "Parser/Parser.hpp"
#include "Interpreter/Interpreter.hpp"

#include "Lexer/TokenFactory.hpp"

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    /*
    TokenBase* token = TokenFactory::MakeToken(5);
    token = token->Add(TokenFactory::MakeToken(88123));

    std::cout << token->ToString() << std::endl;
    */
    
    std::string program = "7 + 5 + 67";
    Lexer* lexer = new Lexer(program);
    Parser* parser = new Parser(lexer);
    Interpreter* interpreter = new Interpreter(parser);
    // call the final token's ToString method to turn result to string
    std::string result = interpreter->Interpret()->ToString();

    std::cout << result << std::endl;
}