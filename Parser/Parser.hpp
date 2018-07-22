#ifndef PASCAL_PARSER
#define PASCAL_PARSER

#include "../Lexer/Lexer.hpp"

class AST_Node
{
public:
    // mark AST_Node as abstract class
    virtual ~AST_Node() = 0;
};

class BinaryOperator final : public AST_Node
{
public:
    BinaryOperator(AST_Node* _left, Token* _operatorToken, AST_Node* _right);

private:
    AST_Node* left;
    AST_Node* right;
    Token* operatorToken;
};

class ValueNode final : public AST_Node
{
public:
    ValueNode(Token* _token);

private:
    Token* token;
};

class Parser final
{
public:
    Parser(Lexer _lexer);
    // Parse the tokens created by lexer to create a abstract syntax tree
    void Parse();

private:
    Lexer* lexer;
    // utility function
    void ThrowException();
    void Eat(TokenType tokenType);

    // Grammar Variables and its definition
    AST_Node* Factor();
    AST_Node* Term();
    AST_Node* Expr();
};

#endif