#include <atomic>
 
template<class T>
struct node
{
    T data;
    node* next;
    node(const T& data) : data(data), next(nullptr) {}
};
 
template<class T>
class stack
{
    std::atomic<node<T>*> head;
 public:
    void push(const T& data)
    {
        node<T>* new_node = new node<T>(data);
 
        // 将 head 的当前值放入 new_node->next
        new_node->next = head.load(std::memory_order_relaxed);
 
        // 现在令 new_node 为新的 head ，
        // 但若 head 不再是存储于 new_node->next 者
        // （某些其他线程必须已在现在插入结点）
        // 则将新的 head 放入 new_node->next 并重试
        while(!std::atomic_compare_exchange_weak_explicit(
                                &head,
                                &new_node->next,
                                new_node,
                                std::memory_order_release,
                                std::memory_order_relaxed))
                ; // 循环体为空
// 注意：上述循环非线程安全，至少在
// 早于 4.8.3 的 GCC （ bug 60272 ），早于 2014-05-05 的 clang （ bug 18899）
// 早于 2014-03-17 的 MSVC （ bug 819819 ）。变通方法见成员函数版本
    }
};
 
int main()
{
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    return 0; 
}