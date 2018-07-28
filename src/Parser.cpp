#include "../include/Parser.hpp"
#include <stdexcept>

#include "../include/Lexer.hpp"
#include "../include/TokenBase.hpp"

// helping mark AST_Node as abstract class
AST_Node::~AST_Node() {}

CompoundNode::CompoundNode(std::vector<AST_Node*> _childrenNodes)
{
    childrenNodes = _childrenNodes;
}

TokenBase* CompoundNode::Visit()
{
    size_t childrenSize = childrenNodes.size();
    for(size_t childIndex = 0; childIndex < childrenSize ; childIndex++)
    {
        childrenNodes[childIndex]->Visit();
    }

    return nullptr;
}

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

    TokenBase* returningToken = nullptr;
    if(valueType == TokenValueType::String)
    {
        // deal with numeric operators
        if(Parser::IsStringTokenSame(operatorToken, "+"))
        {
            returningToken = left->Visit()->Add(right->Visit());
        }
        else if(Parser::IsStringTokenSame(operatorToken, "-"))
        {
            returningToken = left->Visit()->Minus(right->Visit());
        }
        else if(Parser::IsStringTokenSame(operatorToken, "*"))
        {
            returningToken = left->Visit()->Multiply(right->Visit());
        }
        else if(Parser::IsStringTokenSame(operatorToken, "/"))
        {
            returningToken = left->Visit()->Divide(right->Visit());
        }
        else
        {
            // error
            std::cout << "Error : BinaryOperator::Visit cannot find good operation for token : " << operatorToken->ToString();
        }

        //std::cout << "Returning : " << returningToken->ToString() << std::endl;
        return returningToken;
    }
    else
    {
         throw std::invalid_argument( "BinaryOperator::Visit : TokenType is not numeric operator , the token causing error is " + operatorToken->ToString() );
    }
}

UnaryOperator::UnaryOperator(TokenBase* _operatorToken, AST_Node* _expr)
{
    operatorToken = _operatorToken;
    expr = _expr;
}

TokenBase* UnaryOperator::Visit()
{
    // define return value base on + -
    TokenValueType valueType = this->operatorToken->GetValueType();

    TokenBase* returningToken = nullptr;
    if(valueType == TokenValueType::String)
    {
        // deal with numeric operators
        if(Parser::IsStringTokenSame(operatorToken, "+"))
        {
            returningToken = expr->Visit();
        }
        else if(Parser::IsStringTokenSame(operatorToken, "-"))
        {
            returningToken = expr->Visit()->Multiply(TokenFactory::MakeToken(-1));
        }
    }

    return returningToken;
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

AssignNode::AssignNode(AST_Node* _variable, TokenBase* _operatorToken, AST_Node* _value)
{
    variable = _variable;
    operatorToken = _operatorToken;
    value = _value;
}

TokenBase* AssignNode::Visit()
{
    // variable node should be a ValueNode with StringToken
    std::string varName = *(std::string*)variable->Visit()->GetData();
    if(Parser::variablesMap.find(varName) == Parser::variablesMap.end())
    {
        Parser::ThrowException(std::string("Variable " + varName + " Not found!"));
    }
    else
    {
        // remove the old token in this variable, according to C++ standard, deleting 
        // nullptr is defined behavior
        //delete(Parser::variablesMap[varName]);
        // create new token and assign it
        Parser::variablesMap[varName] = value->Visit();
    }

    return nullptr;
}

Parser::Parser(Lexer* _lexer)
{
    lexer = _lexer;
    currentToken = lexer->GetNextToken();
}
// need this line to actually declare a static variable
std::map <std::string, TokenBase*> Parser::variablesMap;

AST_Node* Parser::Parse()
{
    AST_Node* node = Expr();
    //AST_Node* node = nullptr;

    if(currentToken->GetValueType() != TokenValueType::EOF_Token)
    {
        ThrowException("Parser.cpp : Not getting EOF_TOKEN after doing parsing! Current Token info is : " + currentToken->ToString() );
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
            // the content is the same, or specialChar is empty, 
            // in this case, don't do special character check
            if( tokenStringData.compare(_specialChar) == 0 || _specialChar.empty())
            {
                currentToken = lexer->GetNextToken();
            }
            else
            {
                ThrowException(std::string("Error when trying to eat a string token : expecting " + _specialChar + ", but we have " + tokenStringData));
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

// factor : (PLUS | MINUS) factor | INTEGER | LPAREN expr RPAREN
AST_Node* Parser::Factor()
{
    TokenBase* token = currentToken;
    TokenValueType valueType = token->GetValueType();
    // this factor is an integer
    if(valueType == TokenValueType::Integer)
    {
        Eat(TokenValueType::Integer);
        return new ValueNode(token);
    }
    else if(valueType == TokenValueType::String)
    {
        // this factor is an ( Expr )
        std::string stringData = *(std::string*)currentToken->GetData();
        if(stringData.compare("(") == 0)
        {
            Eat(TokenValueType::String, "(");
            AST_Node* node = Expr();
            Eat(TokenValueType::String, ")");

            return node;
        }
        // this factor is an " string "
        if(stringData.compare("\"") == 0)
        {
            Eat(TokenValueType::String, "\"");
            // after eating the first ", current token will be a string token
            AST_Node* node = new ValueNode(currentToken);
            Eat(TokenValueType::String, "");
            Eat(TokenValueType::String, "\"");

            return node;
        }
        // this factor is an (PLUS | MINUS) factor
        if(stringData.compare("+") == 0)
        {
            Eat(TokenValueType::String, "+");
            AST_Node* node = new UnaryOperator(token, Factor());

            return node;
        }
        if(stringData.compare("-") == 0)
        {
            Eat(TokenValueType::String, "-");
            AST_Node* node = new UnaryOperator(token, Factor());

            return node;
        }
    }
    // error happens, return nullptr
    return nullptr;
}

// term : factor ((MUL | DIV) factor)*
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

// expr   : term ((PLUS | MINUS) term)*
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

std::string Parser::GetStringTokenValue(TokenBase* token)
{
    if(token->GetValueType() != TokenValueType::String)
    {
        ThrowException(std::string(
            "Parser::GetStringTokenValue : TokenValueType is not string"));
    }

    std::string stringData = *(std::string*)token->GetData();

    return stringData;
}