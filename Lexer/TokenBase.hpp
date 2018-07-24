#ifndef TOKEN_BASE
#define TOKEN_BASE

#include <sstream>
//debugging
#include <iostream>
// don't include header, just declare a Factory class
class TokenFactory;

enum class TokenValueType : unsigned short int
{
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
    };
    TokenValueType GetValueType()
    {
        return valueType;
    }
    
    virtual std::string ToString() = 0;
    virtual TokenBase* Add(TokenBase* token) = 0;
};

class BoolToken;
class FloatToken;
class StringToken;
class IntegerToken;

class IntegerToken final : public TokenBase
{
private:
    IntegerToken(int _value)
    {
        // IMPORTANT : this local tmpVar need to be new-ed, otherwise the same address might
        // be used accross multiple constructor, makeing data corrupted
        int* tmpVar = new int(_value);
        data = (void*)tmpVar;

        valueType = TokenValueType::Integer;

        std::cout << "IntegerToken Constructor, *_value = " << _value << ", dataPtr = " << data << std::endl;
    }

public:
    friend class TokenFactory;

    virtual std::string ToString()
    {
        std::stringstream s;
        // don't use + operator!
        int myInt = *((int*)GetData());

        std::cout << "Tostring dataPtr = " << data << std::endl;

        s << "IntegerToken with data = " << myInt;

        return s.str();
    }

    virtual TokenBase* Add(TokenBase* token) 
    {
        TokenValueType type = token->GetValueType();
        
        switch(type)
        {
            case TokenValueType::Integer:
            {
                int otherInt = *((int*)token->GetData());
                int myInt = *((int*)GetData());
                
                int result = myInt + otherInt;

                TokenBase* newToken = new IntegerToken(result);
                return newToken;
            }
            default:
            {
                return nullptr;
            }
        }
    }
};

#endif