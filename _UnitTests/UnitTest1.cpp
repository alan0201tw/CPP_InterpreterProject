#include <iostream>
#include <assert.h>

#include "../Interpreter/Interpreter.hpp"
#include "../Lexer/Lexer.hpp"
#include "../Parser/Parser.hpp"

std::string GetInterpretOutput(std::string src)
{
    Lexer* lexer = new Lexer(src);
    Parser* parser = new Parser(lexer);
    Interpreter* interpreter = new Interpreter(parser);
    // call the final token's ToString method to turn result to string
    std::string result = interpreter->Interpret()->ToString();

    return result;
}

int main()
{
    std::string content = "(\"ok\" + 3)*9";
    // the result string is the token's description string
    std::string result = GetInterpretOutput(content);
    std::string expectResult = 
    TokenFactory::MakeToken("ok3ok3ok3ok3ok3ok3ok3ok3ok3")->ToString();
    
    assert(result.compare(expectResult) == 0);

    std::cout << "All unit test passed!" << std::endl;
}