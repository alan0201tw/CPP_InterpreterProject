#ifndef TOKEN_BASE
#define TOKEN_BASE

#include <sstream>
#include <string>
//debugging
#include <iostream>

// declare classes
class TokenBase;
// data token
class IntegerToken;
class BoolToken;
class FloatToken;
class StringToken;
// identifier token
//class ID_Token;

class EOF_Token;

// Token Factory to create all Tokens here
class TokenFactory
{
public:
    static TokenBase* MakeToken(int _value);
    static TokenBase* MakeToken(std::string _value);
    static TokenBase* MakeEOF_Token();
};

enum class TokenValueType : unsigned short int
{
    // Data Type
    Integer,
    Float,
    Bool,
    String,
    EOF_Token
};

class TokenBase
{
protected:
    void* data;
    TokenValueType valueType;
    
public:

    void* GetData()
    {
        return data;
    }
    TokenValueType GetValueType()
    {
        return valueType;
    }
    // for safe deleting tokens
    virtual ~TokenBase() {};

    virtual std::string ToString() = 0;
    virtual TokenBase* Add(TokenBase* token) = 0;
    virtual TokenBase* Minus(TokenBase* token) = 0;
    virtual TokenBase* Multiply(TokenBase* token) = 0;
    virtual TokenBase* Divide(TokenBase* token) = 0;
};

class IntegerToken final : public TokenBase
{
private:
    IntegerToken(int _value);

public:

    friend class TokenFactory;

    virtual ~IntegerToken() override {}

    virtual std::string ToString() override;

    virtual TokenBase* Add(TokenBase* token) override;
    virtual TokenBase* Minus(TokenBase* token) override;
    virtual TokenBase* Multiply(TokenBase* token) override;
    virtual TokenBase* Divide(TokenBase* token) override;
};

class StringToken final : public TokenBase
{
private:
    StringToken(std::string _value);
public:
    friend class TokenFactory;

    virtual ~StringToken() override {}

    virtual std::string ToString() override;

    virtual TokenBase* Add(TokenBase* token) override;
    // string token do not support subtraction(minus operator)
    virtual TokenBase* Minus(TokenBase* token) override;
    // string token do not support Multiply
    virtual TokenBase* Multiply(TokenBase* token) override;
    // string token do not support Divide
    virtual TokenBase* Divide(TokenBase* token) override;
};

class EOF_Token final : public TokenBase
{
private:
    EOF_Token();
    
public:
    friend class TokenFactory;

    virtual ~EOF_Token() override {}

    virtual std::string ToString() override;

    virtual TokenBase* Add(TokenBase* token) override;
    virtual TokenBase* Minus(TokenBase* token) override;
    virtual TokenBase* Multiply(TokenBase* token) override;
    virtual TokenBase* Divide(TokenBase* token) override;
};

#endif