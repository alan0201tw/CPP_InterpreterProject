#include "Parser.hpp"
#include <stdexcept>

#include "../Lexer/Lexer.hpp"

// helping mark AST_Node as abstract class
AST_Node::~AST_Node() {}

TokenBase* BinaryOperator::Visit()
{
    // define return value base on + - * /
    TokenValueType valueType = this->operatorToken->GetValueType();
    if(valueType == TokenValueType::String)
    {
        // deal with numeric operators
        return left->Visit()->Add(right->Visit());
    }
    else
    {
         throw std::invalid_argument( "BinaryOperator::Visit : TokenType is not numeric operator , the token causing error is " + operatorToken->ToString() );
    }
}

TokenBase* ValueNode::Visit()
{
    // return the token in the AST_Node
    return this->token;
}

Parser::Parser(Lexer* _lexer)
{
    lexer = _lexer;
    currentToken = lexer->GetNextToken();
}

AST_Node* Parser::Parse()
{
    //AST_Node* node = Expr();
    AST_Node* node = nullptr;

    if(currentToken->GetValueType() != TokenValueType::EOF_Token)
    {
        ThrowException("Not getting EOF_TOKEN after doing parsing! Current Token info is : " + currentToken->ToString() );
    }

    return node;
}

void Parser::ThrowException(std::string message)
{
    throw std::runtime_error(message);
}