#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
 
std::atomic<bool> lock(false); // 锁定时保有 true
                               // 解锁时保有 false
 
void f(int n)
{
    for (int cnt = 0; cnt < 100; ++cnt) {
        while(std::atomic_exchange_explicit(&lock, true, std::memory_order_acquire))
             ; // 自旋直至获得
        std::cout << "Output from thread " << n << '\n';
        std::atomic_store_explicit(&lock, false, std::memory_order_release);
    }
}
int main()
{
    std::vector<std::thread> v;
    for (int n = 0; n < 10; ++n) {
        v.emplace_back(f, n);
    }
    for (auto& t : v) {
        t.join();
    }
}