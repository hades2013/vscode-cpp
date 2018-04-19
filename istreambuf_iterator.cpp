#include <vector>
#include <sstream>
#include <iostream>
#include <iterator>
 
int main()
{
    // 典型使用：输入流以一对迭代器表示
    std::istringstream in("Hello, world");
    std::vector<char> v( (std::istreambuf_iterator<char>(in)),
                          std::istreambuf_iterator<char>() );
    std::cout << "v has " << v.size() << " bytes. ";
    v.push_back('\0');
    std::cout << "it holds \"" << &v[0] << "\"\n";
 
 
    // 单趟生态的演示
    std::istringstream s("abc");
    std::istreambuf_iterator<char> i1(s), i2(s);
    std::cout << "i1 returns " << *i1 << '\n'
              << "i2 returns " << *i2 << '\n';
    ++i1;
    std::cout << "after incrementing i1, but not i2\n"
              << "i1 returns " << *i1 << '\n'
              << "i2 returns " << *i2 << '\n';
    ++i2; // 这使得 *i2 的表观值从 'a' 跳到 'c'
    std::cout << "after incrementing i2, but not i1\n"
              << "i1 returns " << *i1 << '\n'
              << "i2 returns " << *i2 << '\n';
 
}