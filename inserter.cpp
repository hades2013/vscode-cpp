#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <set>
 
int main()
{
 
    std::multiset<int> s {1, 2, 3};
 
    // std::inserter 常用于 set
    std::fill_n(std::inserter(s, s.end()), 5, 2);
 
    for (int n : s)
        std::cout << n << ' ';
    std::cout << '\n';
 
    std::vector<int> d {100, 200, 300};
    std::vector<int> l {1, 2, 3, 4, 5};
 
    // 插入顺序容器是，插入点前进，因为每次
    // std::insert_iterator::operator= 都更新目标迭代器
    std::copy(d.begin(), d.end(), std::inserter(l, std::next(l.begin())));
 
    for (int n : l)
        std::cout << n << ' ';
    std::cout << '\n';
}