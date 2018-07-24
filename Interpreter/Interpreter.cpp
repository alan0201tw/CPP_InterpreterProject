#include "Interpreter.hpp"

#include "../Lexer/Lexer.hpp"
#include "../Parser/Parser.hpp"

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