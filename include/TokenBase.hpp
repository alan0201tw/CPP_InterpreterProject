#ifndef TOKEN_BASE
#define TOKEN_BASE

#include <sstream>
#include <string>
#include <cstring>
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

union GeneralData
{
    int intData;
    double doubleData;
    std::string stringData;
    // this is super important
    GeneralData()
    {
        std::memset(this, 0, sizeof(GeneralData));
    }
    ~GeneralData() {}
};

class TokenBase
{
protected:
    GeneralData data;
    TokenValueType valueType;
    
public:
    // for safe deleting tokens
    virtual ~TokenBase() {};

    // expose data as readonly property
    int GetIntData() { return data.intData; }
    double GetDoubleData() { return data.doubleData; }
    std::string GetStringData() { return data.stringData; }

    // provide a method for external reading of each token's value type
    // but no need to save it as a member since each class maps to a specific value type,
    // we can just provide an interface to make each actual token implements it.
    virtual TokenValueType GetValueType() = 0;

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

    virtual TokenValueType GetValueType() override
    { 
        return TokenValueType::Integer;
    }

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

    virtual TokenValueType GetValueType() override
    { 
        return TokenValueType::String;
    }

    virtual std::string ToString() override;

    virtual TokenBase* Add(TokenBase* token) override;
    virtual TokenBase* Minus(TokenBase* token) override;
    virtual TokenBase* Multiply(TokenBase* token) override;
    virtual TokenBase* Divide(TokenBase* token) override;
};

class EOF_Token final : public TokenBase
{
private:
    EOF_Token();
    
public:
    friend class TokenFactory;

    virtual ~EOF_Token() override {}

    virtual TokenValueType GetValueType() override
    { 
        return TokenValueType::EOF_Token;
    }

    virtual std::string ToString() override;

    virtual TokenBase* Add(TokenBase* token) override;
    virtual TokenBase* Minus(TokenBase* token) override;
    virtual TokenBase* Multiply(TokenBase* token) override;
    virtual TokenBase* Divide(TokenBase* token) override;
};

#endif