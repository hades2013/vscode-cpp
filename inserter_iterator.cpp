#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include <algorithm>
 
int main()
{
    std::vector<int> v{1,2,3,4,5};
    std::list<int> l{-1,-2,-3};
    std::copy(v.begin(), v.end(), // 可用 std::inserter 简化
              std::insert_iterator<std::list<int>>(l, std::next(l.begin()))); 
    for (int n : l)
        std::cout << n << ' ';
    std::cout << '\n';
}