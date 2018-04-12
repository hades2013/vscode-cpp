#include <algorithm>
#include <vector>
#include <iostream>
 
struct S
{
    int number;
    char name;
    // 注意：此比较运算符忽略 name
    bool operator< ( const S& s ) const { return number < s.number; }
};
 
int main()
{
    // 注意：非有序，仅相对于定义于下的 S 划分
    std::vector<S> vec = { {1,'A'}, {2,'B'}, {2,'C'}, {2,'D'}, {4,'G'}, {3,'F'} };
 
    S value = {2, '?'};
 
    auto p = std::equal_range(vec.begin(), vec.end(), value);
 
    for ( auto i = p.first; i != p.second; ++i )
        std::cout << i->name << ' ';
 
 
    // 异相比较:
    struct Comp
    {
        bool operator() ( const S& s, int i ) const { return s.number < i; }
        bool operator() ( int i, const S& s ) const { return i < s.number; }
    };
 
    auto p2 = std::equal_range(vec.begin(),vec.end(), 2, Comp{});
 
    for ( auto i = p2.first; i != p2.second; ++i )
        std::cout << i->name << ' ';
}