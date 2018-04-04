#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
 
int main()
{
    std::vector<int> v(5);
    std::srand(0); // 仅为示例
    std::generate(v.begin(), v.end(), std::rand); // 使用 C 函数 std::rand()
 
    std::cout << "v: ";
    for (auto iv: v) {
        std::cout << iv << " ";
    }
    std::cout << "\n";
 
    // 以来自 lambda 函数的默认值 0,1,2,3,4 初始化
    // 等价于 std::iota(v.begin(), v.end(), 0);
    std::generate(v.begin(), v.end(), [n = 0] () mutable { return n++; });
 
    std::cout << "v: ";
    for (auto iv: v) {
        std::cout << iv << " ";
    }
    std::cout << "\n";
}