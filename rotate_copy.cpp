#include <algorithm>
#include <vector>
#include <iostream>
 
int main()
{
    std::vector<int> src = {1, 2, 3, 4, 5}; 
    auto pivot = std::find(src.begin(), src.end(), 3); 
    std::vector<int> dest(src.size());                                          
 
    std::rotate_copy(src.begin(), pivot, src.end(), dest.begin());
 
    for (const auto &i : dest) {
        std::cout << i << ' ';
    }   
    std::cout << '\n';
}