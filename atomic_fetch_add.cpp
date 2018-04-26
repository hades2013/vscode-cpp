#include <string>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <chrono>
 
// cnt 的含义：
// 10 ：无活跃读者或写者
// 1...9 ：有 9...1 个读者活跃。写者被阻塞
// 0 ： fetch_sub 和 fetch_add 间的临时值在读者锁中
// -1 ：有活跃写者。读者被阻塞。
const int N = 10; // 允许九个共时读者
std::atomic<int> cnt = ATOMIC_VAR_INIT(N);
 
std::vector<int> data;
 
void reader(int id)
{
    for(;;)
    {
        // 锁定
        while(std::atomic_fetch_sub(&cnt, 1) <= 0)
            std::atomic_fetch_add(&cnt, 1);
        // 读取
        if(!data.empty())
            std::cout << (  "reader " + std::to_string(id)
                          + " sees " + std::to_string(*data.rbegin()) + '\n');
        if(data.size() == 100)
            break;
        // 解锁
        std::atomic_fetch_add(&cnt, 1);
        // 暂停
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
 
void writer()
{
    for(int n = 0; n < 100; ++n)
    {
        // 锁定
        while(std::atomic_fetch_sub(&cnt, N+1) != N)
            std::atomic_fetch_add(&cnt, N+1);
        // 写入
        data.push_back(n);
        std::cout << "writer pushed back " << n << '\n';
        // 解锁
        std::atomic_fetch_add(&cnt, N+1);
        // 暂停
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
 
int main()
{
    std::vector<std::thread> v;
    for (int n = 0; n < N; ++n) {
        v.emplace_back(reader, n);
    }
    v.emplace_back(writer);
    for (auto& t : v) {
        t.join();
    }
}