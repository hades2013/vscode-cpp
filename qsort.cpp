#include <iostream>
#include <cstdlib>
#include <climits>
 
int main()
{
    int a[] = {-2, 99, 0, -743, 2, INT_MIN, 4};
    constexpr std::size_t size = sizeof a / sizeof *a;
 
    std::qsort(a, size, sizeof *a, [](const void* a, const void* b)
    {
        int arg1 = *static_cast<const int*>(a);
        int arg2 = *static_cast<const int*>(b);
 
        if(arg1 < arg2) return -1;
        if(arg1 > arg2) return 1;
        return 0;
 
    //  返回 (arg1 > arg2) - (arg1 < arg2); // 可行的缩写
    //  返回 arg1 - arg2; // 错误的缩写（若有 INT_MIN 则失败）
    });
 
    for(int ai : a)
        std::cout << ai << ' ';
}