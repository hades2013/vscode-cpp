#include <iostream>

class A
{
public:
    A() { std::cout << "Constructor" << std::endl; }
    A(const A&) { std::cout << "Copy Constructor" << std::endl; }
    ~A() {}
};

static A getA()
{
    A a;
    return a;
}

int main()
{
    A a = getA();
    
    return 0;
}