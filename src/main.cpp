#include "Lexer.hpp"
#include "Parser.hpp"
#include "Interpreter.hpp"

#include "TokenBase.hpp"

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
    //std::string result = interpreter->Interpret()->ToString();
    interpreter->Interpret();
    //std::cout << "Result = " << result << std::endl;
    map<std::string, TokenBase*>::iterator it;

    for ( it = Parser::variablesMap.begin(); it != Parser::variablesMap.end(); it++ )
    {
        std::cout << it->first << " : " << it->second->ToString() << std::endl;
    }
    /*
    cout << "sizeof(GeneralData) = " << sizeof(GeneralData) << endl;
    cout << "sizeof(string) = " << sizeof(std::string) << endl;
    std::string sss = "ewl;khgvo;rngvouasnrvoberougvnoegbv;soebvoe";
    cout << "sizeof(sss) = " << sizeof(sss) << endl;
    */
}