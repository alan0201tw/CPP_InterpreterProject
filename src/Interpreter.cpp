#include "Interpreter.hpp"

#include "Lexer.hpp"
#include "Parser.hpp"

#include "Interpreter.hpp"

Interpreter::Interpreter(Parser* _parser)
{
    parser = _parser;
}

TokenBase* Interpreter::Interpret()
{
    AST_Node* root = parser->Parse();

    return root->Visit();
}