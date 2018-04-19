#include <iostream>
#include <iterator>
#include <vector>
 
int main() 
{
    std::vector<int> v{ 3, 1, 4 };
 
    auto it = v.end();
 
    auto pv = std::prev(it, 2);
 
    std::cout << *pv << '\n';
}