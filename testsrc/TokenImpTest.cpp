#include <map>
#include <iostream>

int main()
{
    std::map<std::string, void*> variables;

    std::string* str = new std::string("world");
    void* data = (void*)str;
    variables["hello"] = data;

    std::cout << *(std::string*)variables["hello"] << std::endl;
}