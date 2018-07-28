#include "./include/Lexer.hpp"
#include "./include/Parser.hpp"
#include "./include/Interpreter.hpp"

#include "./include/TokenBase.hpp"

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    /*
    TokenBase* token = TokenFactory::MakeToken(5);
    token = token->Add(TokenFactory::MakeToken(88123));

    std::cout << token->ToString() << std::endl;
    */
    std::string content;

    // ./main.exe <fileName>
    if(argc == 2)
    {
        std::ifstream ifs(argv[1]);
        content.assign((std::istreambuf_iterator<char>(ifs)),std::istreambuf_iterator<char>());
    }
    else
    {
        std::cout << "Usage error, or usage not supported yet. " <<
        "Try : ./main.exe <source code file name>" << std::endl;

        exit(0);
    }
    
    //std::string program = "7 *(2+881) /(10-100) * 10";

    Lexer* lexer = new Lexer(content);
    Parser* parser = new Parser(lexer);
    Interpreter* interpreter = new Interpreter(parser);
    // call the final token's ToString method to turn result to string
    std::string result = interpreter->Interpret()->ToString();

    std::cout << "Result = " << result << std::endl;
}