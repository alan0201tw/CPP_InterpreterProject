#ifndef PASCAL_PARSER
#define PASCAL_PARSER

#include "Lexer.hpp"
#include "TokenBase.hpp"

#include <vector>
#include <map>

class AST_Node
{
public:
    // mark AST_Node as abstract class
    virtual ~AST_Node() = 0;
    virtual TokenBase* Visit() = 0;
};

class CompoundNode final : public AST_Node
{
public:
    CompoundNode(std::vector<AST_Node*> _childrenNodes);

    virtual TokenBase* Visit();

private:
    std::vector<AST_Node*> childrenNodes;
};

class BinaryOperator final : public AST_Node
{
public:
    BinaryOperator(AST_Node* _left, TokenBase* _operatorToken, AST_Node* _right);

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

    virtual TokenBase* Visit();

private:
    AST_Node* expr;
    TokenBase* operatorToken;
};

class ValueNode final : public AST_Node
{
public:
    ValueNode(TokenBase* _token);

    virtual TokenBase* Visit();

private:
    TokenBase* token;
};

// The VariableNode is constructed out of ID token.
class VariableNode final : public AST_Node
{
public:
    VariableNode(TokenBase* _token);

    virtual TokenBase* Visit();
    std::string GetVarName();

private:
    TokenBase* token;
};

class AssignNode final : public AST_Node
{
public:
    AssignNode(VariableNode* _variable, TokenBase* _operatorToken, AST_Node* _value);

    virtual TokenBase* Visit();

private:
    VariableNode* variable;
    AST_Node* value;
    TokenBase* operatorToken;
};

class NoOperationNode final : public AST_Node
{
public:
    NoOperationNode();

    virtual TokenBase* Visit();
};

class Parser final
{
public:
    Parser(Lexer* _lexer);
    // Parse the tokens created by lexer to create a abstract syntax tree
    AST_Node* Parse();
    
    // Utility Function
    static void ThrowException(std::string message);
    static bool IsStringTokenSame(TokenBase* token, std::string _value);
    static std::string GetStringTokenValue(TokenBase* token);
    // variables in program
    // use ID ( identifier, variable names ) to get Token
    // each time an value assignment happens, free old token and make a new one
    static std::map <std::string, TokenBase*> variablesMap;

private:
    Lexer* lexer;
    void Eat(TokenValueType tokenType, std::string _specialChar = "");

    TokenBase* currentToken;

    // Grammar Variables and its definition
    // Actual Program Structure
    AST_Node* Program();
    AST_Node* CompoundStatement();
    std::vector<AST_Node*> StatementList();
    AST_Node* Statement();
    AST_Node* AssignmentStatement();
    VariableNode* Variable();
    AST_Node* Empty();

    // Basics
    AST_Node* Expr();
    AST_Node* Term();
    AST_Node* Factor();
};

#endif