#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Report
{
public:
    Report(const std::string s):str(s)
    {
        cout<<"Object created"<<endl;
    }
    ~Report()
    {
        cout<<"Object deleted"<<endl;
    }
    void comment()const
    {
        cout<<str<<endl;
    }
private:
    std::string str;
};

int main(int argc, char* const argv[])
{
    //test1: use smart ptr
    {
        std::auto_ptr<Report> ps(new Report("using auto_ptr"));
        ps->comment();
    }
    {
        std::shared_ptr<Report> ps(new Report("using shared_ptr"));
        ps->comment();
    }
    {
        std::unique_ptr<Report> ps(new Report("using unique_ptr"));
        ps->comment();
    }
    return 0;
}