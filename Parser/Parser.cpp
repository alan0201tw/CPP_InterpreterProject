#include "Parser.hpp"
#include <stdexcept>

#include "../Lexer/Lexer.hpp"
#include "../Lexer/TokenFactory.hpp"

// helping mark AST_Node as abstract class
AST_Node::~AST_Node() {}

BinaryOperator::BinaryOperator(AST_Node* _left, TokenBase* _operatorToken, AST_Node* _right)
{
    left = _left;
    right = _right;
    operatorToken = _operatorToken;
}

TokenBase* BinaryOperator::Visit()
{
    // define return value base on + - * /
    TokenValueType valueType = this->operatorToken->GetValueType();
    if(valueType == TokenValueType::String)
    {
        // deal with numeric operators
        if(Parser::IsStringTokenSame(operatorToken, "+"))
        {
            return left->Visit()->Add(right->Visit());
        }
        else if(Parser::IsStringTokenSame(operatorToken, "-"))
        {
            return left->Visit()->Minus(right->Visit());
        }
        else if(Parser::IsStringTokenSame(operatorToken, "*"))
        {
            return left->Visit()->Multiply(right->Visit());
        }
        else if(Parser::IsStringTokenSame(operatorToken, "/"))
        {
            return left->Visit()->Divide(right->Visit());
        }
        else
        {
            // error
            std::cout << "Error : BinaryOperator::Visit cannot find good operation for token : " << operatorToken->ToString();
            return nullptr;
        }
    }
    else
    {
         throw std::invalid_argument( "BinaryOperator::Visit : TokenType is not numeric operator , the token causing error is " + operatorToken->ToString() );
    }
}

ValueNode::ValueNode(TokenBase* _token)
{
    token = _token;
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
    AST_Node* node = Expr();
    //AST_Node* node = nullptr;

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

void Parser::Eat(TokenValueType tokenType, std::string _specialChar)
{
    TokenValueType valueType = currentToken->GetValueType();

    if(valueType == tokenType)
    {
        // if the current token is a string token, need to further compare actual data
        if(valueType == TokenValueType::String)
        {
            std::string tokenStringData = *(std::string*)currentToken->GetData();
            // the content is the same
            if( tokenStringData.compare(_specialChar) == 0 )
            {
                currentToken = lexer->GetNextToken();
            }
        }
        else
        {
            currentToken = lexer->GetNextToken();
        }
    }
    else
    {
        ThrowException(std::string("Error when trying to eat a token."));
    }
}

AST_Node* Parser::Factor()
{
    TokenBase* token = currentToken;
    TokenValueType valueType = token->GetValueType();
    if(valueType == TokenValueType::Integer)
    {
        Eat(TokenValueType::Integer);
        return new ValueNode(token);
    }
    else if(valueType == TokenValueType::String)
    {
        std::string stringData = *(std::string*)currentToken->GetData();
        if(stringData.compare("(") == 0)
        {
            Eat(TokenValueType::String, "(");
            AST_Node* node = Expr();
            Eat(TokenValueType::String, ")");

            return node;
        }
    }
    // error happens, return nullptr
    return nullptr;
}

AST_Node* Parser::Term()
{
    AST_Node* node = Factor();
    // if current token is "*" or "/"
    while( IsStringTokenSame(currentToken, "*") || IsStringTokenSame(currentToken, "/") )
    {
        TokenBase* token = currentToken;
        if(IsStringTokenSame(currentToken, "*"))
        {
            Eat(TokenValueType::String, "*");
        }
        else if(IsStringTokenSame(currentToken, "/"))
        {
            Eat(TokenValueType::String, "/");
        }

        node = new BinaryOperator(node, token, Factor());
    }

    return node;
}

AST_Node* Parser::Expr()
{
    AST_Node* node = Term();
    // if current token is "*" or "/"
    while( IsStringTokenSame(currentToken, "+") || IsStringTokenSame(currentToken, "-") )
    {
        TokenBase* token = currentToken;
        if(IsStringTokenSame(currentToken, "+"))
        {
            Eat(TokenValueType::String, "+");
        }
        else if(IsStringTokenSame(currentToken, "-"))
        {
            Eat(TokenValueType::String, "-");
        }

        node = new BinaryOperator(node, token, Term());
    }

    return node;
}

/// temporary solution for comparing two string tokens

bool Parser::IsStringTokenSame(TokenBase* token, std::string _value)
{
    if(token->GetValueType() != TokenValueType::String)
        return false;

    std::string stringData = *(std::string*)token->GetData();
    if(stringData.compare(_value) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}