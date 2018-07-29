#include "Parser.hpp"
#include <stdexcept>

#include "Lexer.hpp"
#include "TokenBase.hpp"

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

    // remove the old token in this variable, according to C++ standard, deleting 
    // nullptr is defined behavior
    //delete(Parser::variablesMap[varName]);
    // create new token and assign it
    Parser::variablesMap[varName] = value->Visit();
    
    return nullptr;
}

VariableNode::VariableNode(TokenBase* _token)
{
    token = _token;
}

TokenBase* VariableNode::Visit()
{
    std::string varName = *(std::string*)token->GetData();
    // not found
    if(Parser::variablesMap.find(varName) == Parser::variablesMap.end())
    {
        Parser::ThrowException(std::string("Variable " + varName + " not found."));
    }
    else
    {
        return Parser::variablesMap[varName];
    }

    return nullptr;
}

// empty constructor for NoOperationNode
NoOperationNode::NoOperationNode() {}

TokenBase* NoOperationNode::Visit()
{
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
    AST_Node* node = Program();
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

// program : compound_statement DOT
AST_Node* Parser::Program()
{
    std::cout << "Making CompoundStatement" << std::endl;
    AST_Node* node = CompoundStatement();
    Eat(TokenValueType::String, ".");
    return node;
}

// compound_statement: BEGIN statement_list END
AST_Node* Parser::CompoundStatement()
{
    Eat(TokenValueType::String, "BEGIN");
    std::cout << "Making StatementList" << std::endl;
    std::vector<AST_Node*> nodes = StatementList();
    Eat(TokenValueType::String, "END");

    AST_Node* root = new CompoundNode(nodes);
    return root;
}

//statement_list : statement | statement SEMI statement_list
std::vector<AST_Node*> Parser::StatementList()
{
    std::cout << "Making Statement" << std::endl;
    AST_Node* node = Statement();
    std::vector<AST_Node*> results;
    results.push_back(node);

    while( IsStringTokenSame(currentToken, ";") )
    {
        Eat(TokenValueType::String, ";");
        std::cout << "Making Statement" << std::endl;
        results.push_back(Statement());
    }

    if(variablesMap.find(GetStringTokenValue(currentToken)) != variablesMap.end())
    {
        ThrowException(std::string("Parser::StatementList : Expecting complete statement."));
    }

    return results;
}

// statement : compound_statement | assignment_statement | empty
AST_Node* Parser::Statement()
{
    AST_Node* node = nullptr;
    if(IsStringTokenSame(currentToken, "BEGIN"))
    {
        std::cout << "Making CompoundStatement" << std::endl;
        node = CompoundStatement();
    }
    // statement starts with a variable name
    else if(currentToken->GetValueType() == TokenValueType::String)
    {
        node = AssignmentStatement();
    }
    else
    {
        node = Empty();
    }

    if(node == nullptr)
    {
        ThrowException(std::string("Parser::Statement : returning nullptr"));
    }

    return node;
}

// assignment_statement : variable ASSIGN expr
AST_Node* Parser::AssignmentStatement()
{
    AST_Node* var = Variable();
    TokenBase* token = currentToken;
    Eat(TokenValueType::String, ":=");
    AST_Node* value = Expr();

    AST_Node* node = new AssignNode(var, token, value);
    return node;
}

// variable : ID
AST_Node* Parser::Variable()
{
    AST_Node* node = new VariableNode(currentToken);
    // eat the variable name, the name is not a const string, so just eat a random string
    Eat(TokenValueType::String);

    return node;
}

// An empty production
AST_Node* Parser::Empty()
{
    return new NoOperationNode();
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
        else if(stringData.compare("\"") == 0)
        {
            Eat(TokenValueType::String, "\"");
            // after eating the first ", current token will be a string token
            AST_Node* node = new ValueNode(currentToken);
            Eat(TokenValueType::String, "");
            Eat(TokenValueType::String, "\"");

            return node;
        }
        // this factor is an (PLUS | MINUS) factor
        else if(stringData.compare("+") == 0)
        {
            Eat(TokenValueType::String, "+");
            AST_Node* node = new UnaryOperator(token, Factor());

            return node;
        }
        else if(stringData.compare("-") == 0)
        {
            Eat(TokenValueType::String, "-");
            AST_Node* node = new UnaryOperator(token, Factor());

            return node;
        }
        // this factor is a variable
        else
        {
            AST_Node* node = Variable();
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