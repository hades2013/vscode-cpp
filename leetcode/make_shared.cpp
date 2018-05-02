#include <string>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <memory>
using namespace std; 
#else 
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
using namespace std; 
#endif 

class Foo
{
    public: 
    typedef shared_ptr<Foo> Ptr; 
    Foo():a(42), b(false), c(12.234){}

    private: 
    int a; 
    bool b; 
    float c; 
    std::string d; 
};

const int loop_count = 100000000; 

int main()
{
    for(int i =0; i < loop_count; i++){
        Foo::Ptr p = make_shared<Foo>();
    }
    return 0; 
}
