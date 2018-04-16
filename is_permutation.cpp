#include <algorithm>
#include <vector>
#include <iostream>
int main()
{
    std::vector<int> v1{1,2,3,4,5};
    std::vector<int> v2{3,5,4,1,2};
    std::cout << "3,5,4,1,2 is a permutation of 1,2,3,4,5? "
              << std::boolalpha
              << std::is_permutation(v1.begin(), v1.end(), v2.begin()) << '\n';
 
    std::vector<int> v3{3,5,4,1,1};
    std::cout << "3,5,4,1,1 is a permutation of 1,2,3,4,5? "
              << std::boolalpha
              << std::is_permutation(v1.begin(), v1.end(), v3.begin()) << '\n';
}