#include "../include/Interpreter.hpp"

#include "../include/Lexer.hpp"
#include "../include/Parser.hpp"

#include "../include/Interpreter.hpp"

Interpreter::Interpreter(Parser* _parser)
{
    parser = _parser;
}

TokenBase* Interpreter::Interpret()
{
    AST_Node* root = parser->Parse();

    return root->Visit();
}