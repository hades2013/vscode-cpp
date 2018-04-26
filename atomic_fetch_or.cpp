#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <functional>
 
// 仅为演示目的的二元信号量
// 此乃简单却有意义的示例：若无线程则原子操作为不必要。 
class Semaphore {
    std::atomic_char m_signaled;
  public:
    Semaphore(bool initial = false)
    {
        m_signaled = initial;
    }
    // 阻塞直至信号量被发信
    void take() 
    {
        while (!std::atomic_fetch_and(&m_signaled, false)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
 
    void put() 
    {
        std::atomic_fetch_or(&m_signaled, true);
    }
};
 
class ThreadedCounter {
    static const int N = 100;
    static const int REPORT_INTERVAL = 10;
    int m_count;
    bool m_done;
    Semaphore m_count_sem;
    Semaphore m_print_sem;
 
    void count_up() 
    {
        for (m_count = 1; m_count <= N; m_count++) {
            if (m_count % REPORT_INTERVAL == 0) {
                if (m_count == N) m_done = true;
                m_print_sem.put(); // 对打印发信，使之发生
                m_count_sem.take(); // 等待直至打印完成进展
            }
        }
        std::cout << "count_up() done\n";
        m_done = true;
        m_print_sem.put();
    }
 
    void print_count() 
    {
        do {
            m_print_sem.take();
            std::cout << m_count << '\n';
            m_count_sem.put();
        } while (!m_done);
        std::cout << "print_count() done\n";
    }
 
  public:
    ThreadedCounter() : m_done(false) {}
    void run() 
    {
        auto print_thread = std::thread(&ThreadedCounter::print_count, this);
        auto count_thread = std::thread(&ThreadedCounter::count_up, this);
        print_thread.join();
        count_thread.join();
    }
};
 
int main() 
{
    ThreadedCounter m_counter;
    m_counter.run();
    return 0; 
}