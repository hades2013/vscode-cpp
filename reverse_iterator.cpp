#include <iostream>
#include <string>
#include <iterator>
 
int main()
{
    std::string s = "Hello, world";
    std::reverse_iterator<std::string::iterator> r = s.rbegin();
    r[7] = 'O'; // 以 'O' 替换 'o'
    r += 7; // 迭代器现在指向 'O'
    std::string rev(r, s.rend());
    std::cout << rev << '\n';
}