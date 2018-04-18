#include <iostream>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <vector>
 
int main()
{
    std::vector<int> v;
    std::generate_n(std::back_insert_iterator<std::vector<int>>(v), // std::back_inserter
                    10, [](){ return std::rand() % 10; });        // 可用以简化
    for (int n : v)
        std::cout << n << ' ';
    std::cout << '\n';
}