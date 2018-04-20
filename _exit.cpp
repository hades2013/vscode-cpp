#include <iostream>
 
class Static {
public:
    ~Static() 
    {
        std::cout << "Static dtor\n";
    }
};
 
class Local {
public:
    ~Local() 
    {
        std::cout << "Local dtor\n";
    }
};
 
Static static_variable; // 此对象的析构函数将*不*被调用
 
void atexit_handler()
{
    std::cout << "atexit handler\n";
}
 
int main()
{
    Local local_variable; // 将*不*调用析构函数
 
    // 将*不*调用处理函数
    const int result = std::atexit(atexit_handler);
 
    if (result != 0) {
        std::cerr << "atexit registration failed\n";
        return EXIT_FAILURE;
    }
 
    std::cout << "test" << std::endl; // 从 std::endl 冲入
        // 需要再次，否则不会打印内容
    std::_Exit(EXIT_FAILURE);
}