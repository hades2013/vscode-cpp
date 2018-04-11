#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
 
template<class ForwardIt, class T, class Compare=std::less<>>
ForwardIt binary_find(ForwardIt first, ForwardIt last, const T& value, Compare comp={})
{
    // 注意：类型 T 和 Forward 解引用后的类型都必须可隐式转换为
    // 用于 Compare 的 Type1 和 Type2 。
    // 这严格于 lower_bound 要求（见上述）
 
    first = std::lower_bound(first, last, value, comp);
    return first != last && !comp(value, *first) ? first : last;
}
 
int main()
{
    std::vector<int> data = { 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6 };
 
    auto lower = std::lower_bound(data.begin(), data.end(), 4);
    auto upper = std::upper_bound(data.begin(), data.end(), 4);
 
    std::copy(lower, upper, std::ostream_iterator<int>(std::cout, " "));
 
    std::cout << '\n';
 
    // 经典二分搜索，仅若存在才返回值
 
    data = { 1, 2, 4, 6, 9, 10 }; 
 
    auto it = binary_find(data.cbegin(), data.cend(), 4); // 选择 '5' 的 < 将返回 end()
 
    if(it != data.cend())
      std::cout << *it << " found at index "<< std::distance(data.cbegin(), it);
 
    return 0;
}