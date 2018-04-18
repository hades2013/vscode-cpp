#include <iostream>
#include <deque>
#include <algorithm>
#include <iterator>
 
int main()
{
    std::deque<int> v{1,2,3,4,5,6,7,8,9,10};
    std::fill_n(std::front_inserter(v), 3, -1);
    for (int n : v)
        std::cout << n << ' ';
}