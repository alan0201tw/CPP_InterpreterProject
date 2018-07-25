#ifndef PASCAL_PARSER
#define PASCAL_PARSER

#include "../Lexer/Lexer.hpp"
#include "../Lexer/TokenBase.hpp"

class AST_Node
{
public:
    // mark AST_Node as abstract class
    virtual ~AST_Node() = 0;
    virtual TokenBase* Visit() = 0;
};

class BinaryOperator final : public AST_Node
{
public:
    BinaryOperator(AST_Node* _left, TokenBase* _operatorToken, AST_Node* _right);
    AST_Node* LeftNode();
    AST_Node* RightNode();
    TokenBase* OperatorToken();

    virtual TokenBase* Visit();

private:
    AST_Node* left;
    AST_Node* right;
    TokenBase* operatorToken;
};

class UnaryOperator final : public AST_Node
{
public:
    UnaryOperator(TokenBase* _operatorToken, AST_Node* _expr);
    AST_Node* Expr();
    TokenBase* OperatrToken();

    virtual TokenBase* Visit();

private:
    AST_Node* expr;
    TokenBase* operatorToken;
};

class ValueNode final : public AST_Node
{
public:
    ValueNode(TokenBase* _token);
    TokenBase* ValueToken();

    virtual TokenBase* Visit();

private:
    TokenBase* token;
};

class Parser final
{
public:
    Parser(Lexer* _lexer);
    // Parse the tokens created by lexer to create a abstract syntax tree
    AST_Node* Parse();
    
    // Utility Function
    static bool IsStringTokenSame(TokenBase* token, std::string _value);

private:
    Lexer* lexer;
    // utility function
    void ThrowException(std::string message);
    void Eat(TokenValueType tokenType, std::string _specialChar = "");

    TokenBase* currentToken;

    // Grammar Variables and its definition
    AST_Node* Factor();
    AST_Node* Term();
    AST_Node* Expr();
};

#endif