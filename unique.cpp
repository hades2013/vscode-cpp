#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>
 
int main() 
{
    // 移除重复元素（正常使用）
    std::vector<int> v{1,2,3,1,2,3,3,4,5,4,5,6,7};
    std::sort(v.begin(), v.end()); // 1 1 2 2 3 3 3 4 4 5 5 6 7 
    auto last = std::unique(v.begin(), v.end());
    // v 现在保有 {1 2 3 4 5 6 7 x x x x x x} ，其中 'x' 为不确定
    v.erase(last, v.end()); 
    for (int i : v)
      std::cout << i << " ";
    std::cout << "\n";
 
    // 移除连续空格
    std::string s = "wanna go    to      space?";
    auto end = std::unique(s.begin(), s.end(), [](char l, char r){
        return std::isspace(l) && std::isspace(r) && l == r;
    });
    // s 现在保有 "wanna go to space?xxxxxxxx" ，其中 'x' 为不确定
    std::cout << std::string(s.begin(), end) << '\n';
}