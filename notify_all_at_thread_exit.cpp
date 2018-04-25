#include <mutex>
#include <thread>
#include <condition_variable>
 
std::mutex m;
std::condition_variable cv;
 
bool ready = false;
ComplexType result;  // 一些任意类型
 
void thread_func()
{
    std::unique_lock<std::mutex> lk(m);
    // 用 thread_local 数据赋值给 result
    result = function_that_uses_thread_locals();
    ready = true;
    std::notify_all_at_thread_exit(cv, std::move(lk));
} // 1. 销毁 thread_local 对象， 2. 解锁互斥， 3. 通知 cv
 
int main()
{
    std::thread t(thread_func);
    t.detach();
 
    // 做其他工作
    // .…
 
    // 等待脱附的线程
    std::unique_lock<std::mutex> lk(m);
    while(!ready) {
        cv.wait(lk);
    }
    process(result); // result 已准备且 thread_local 析构函数已完成
}