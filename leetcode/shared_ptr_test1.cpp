#include <memory>
#include <iostream>
int main()
{
    int *p = new int(30);
    std::shared_ptr<int> bptr(p);//方式1
    std::shared_ptr<int> aptr = std::make_shared<int>(20);//方式
    std::shared_ptr<int> cptr(aptr);
    std::cout << "aptr.use_count() = " << aptr.use_count() <<"  value = "<<*aptr<<std::endl;//use_count 是引用计数器
    std::cout << "bptr.use_count() = " << bptr.use_count() <<"  value = "<<*bptr<<std::endl;
    std::cout << "cptr.use_count() = " << cptr.use_count() <<"  value = "<<*cptr<<std::endl;
    //输出是：2，20
    //       1，30
    //       2，20
} 