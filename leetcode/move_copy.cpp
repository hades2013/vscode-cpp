#include <iostream>
#include <utility>
#include <string>
#include <vector>


class B
{
public:
    B() {}
    B(const B&) { std::cout << "B Constructor" << std::endl; }
};

class A
{
public:
    A(): m_b(new B()) { std::cout << "A Constructor" << std::endl; }
    A(const A& src) :
        m_b(new B(*(src.m_b)))
    { 
        std::cout << "A Copy Constructor" << std::endl;
    }
    A(A&& src) :
        m_b(src.m_b)
    {
        src.m_b = nullptr;
        std::cout << "A Move Constructor" << std::endl;
    }
    A& operator=(const A& src) noexcept
    {
        if (this == &src)
            return *this;

        delete m_b;
        m_b = new B(*(src.m_b));
        std::cout << "operator=(const A& src)" << std::endl;
        return *this;
    }
    A& operator=(A&& src) noexcept
    {
        if (this == &src)
            return *this;

        delete m_b;
        m_b = src.m_b;
        src.m_b = nullptr;
        std::cout << "operator=(const A&& src)" << std::endl;
        return *this;
    }
    ~A() { delete m_b; }

private:
    B* m_b;
};

static A getA()
{
    A a;
    std::cout << "1================================================" << std::endl;
    return a;
}

int main()
{
    A a = getA();//移动构造
    std::cout << "2================================================" << std::endl;
    A a1(a);//拷贝构造
    std::cout << "3================================================" << std::endl;
    A a2(std::move(a1));//移动构造
    std::cout << "4================================================" << std::endl;
    a2 = getA();//移动赋值
    std::cout << "5================================================" << std::endl;
    a2 = a1;//拷贝赋值
    return 0;
}