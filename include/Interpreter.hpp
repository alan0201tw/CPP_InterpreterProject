#ifndef PASCAL_INTERPRETER
#define PASCAL_INTERPRETER

#include <map>
#include <typeindex>
#include <typeinfo>

#include "Parser.hpp"

class Interpreter
{
public:
    Interpreter(Parser* _parser);

    TokenBase* Interpret();

private:
    Parser* parser;
};

#endif