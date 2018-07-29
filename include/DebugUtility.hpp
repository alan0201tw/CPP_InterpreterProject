#ifndef DEBUG_UTILITY
#define DEBUG_UTILITY

#include <string>

class IToStringInterface
{
    public:
        virtual ~IToStringInterface() {}
        virtual std::string ToString() = 0;
};

#endif