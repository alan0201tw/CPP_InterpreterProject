#ifndef PASCAL_INTERPRETER
#define PASCAL_INTERPRETER

#include <map>
#include <typeindex>
#include <typeinfo>

#include "../Parser/Parser.hpp"

class Interpreter
{
public:
    Interpreter(Parser* _parser);
};

#endif