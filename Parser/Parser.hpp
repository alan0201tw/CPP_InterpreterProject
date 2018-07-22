#ifndef PASCAL_PARSER
#define PASCAL_PARSER

#include "../Lexer/Lexer.hpp"

class AST_Node
{
public:
    // mark AST_Node as abstract class
    virtual ~AST_Node() = 0;
    virtual int Visit() = 0;
};

class BinaryOperator final : public AST_Node
{
public:
    BinaryOperator(AST_Node* _left, Token* _operatorToken, AST_Node* _right);
    AST_Node* LeftNode();
    AST_Node* RightNode();
    Token* OperatorToken();

    virtual int Visit();

private:
    AST_Node* left;
    AST_Node* right;
    Token* operatorToken;
};

class ValueNode final : public AST_Node
{
public:
    ValueNode(Token* _token);
    Token* ValueToken();

    virtual int Visit();

private:
    Token* token;
};

class Parser final
{
public:
    Parser(Lexer* _lexer);
    // Parse the tokens created by lexer to create a abstract syntax tree
    AST_Node* Parse();

private:
    Lexer* lexer;
    // utility function
    void ThrowException(std::string message);
    void Eat(TokenType tokenType);

    Token* currentToken;

    // Grammar Variables and its definition
    //AST_Node* Factor();
    //AST_Node* Term();
    //AST_Node* Expr();
};

#endif