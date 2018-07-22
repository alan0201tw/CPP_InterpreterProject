#include "Parser.hpp"
#include <stdexcept>

#include "../Lexer/Lexer.hpp"

// helping mark AST_Node as abstract class
AST_Node::~AST_Node() {}

int BinaryOperator::Visit()
{
    // define return value base on + - * /
    TokenType tokenType = this->operatorToken->GetTokenType();
    if(tokenType == TokenType::PLUS)
    {
        return left->Visit() + right->Visit();
    }
    else if(tokenType == TokenType::MINUS)
    {
        return left->Visit() - right->Visit();
    }
    else if(tokenType == TokenType::MUL)
    {
        return left->Visit() * right->Visit();
    }
    else if(tokenType == TokenType::DIV)
    {
        return left->Visit() / right->Visit();
    }
    else
    {
         throw std::invalid_argument( "BinaryOperator::Visit : TokenType is not numeric operator , the token causing error is " + operatorToken->ToString() );
    }
}

int ValueNode::Visit()
{
    // convert string to int
    return std::stoi(this->token->GetValue());
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

    if(currentToken->GetTokenType() != TokenType::EOF_TOKEN)
    {
        ThrowException("Not getting EOF_TOKEN after doing parsing! Current Token info is : " + currentToken->ToString() );
    }

    return node;
}

void Parser::ThrowException(std::string message)
{
    throw std::runtime_error(message);
}