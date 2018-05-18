#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <stdlib.h>
using namespace std;

unique_ptr<int> make_int(int n)
{
    return unique_ptr<int> (new int(n));
}

void show(unique_ptr<int> & pi)     //pass by reference
{
    cout<< *pi <<' ';
}

int main()
{
    vector<unique_ptr<int> > vp(5);
    for(int i = 0; i < vp.size(); ++i)
    {
        vp[i] = make_int(rand() % 1000);//copy temporary unique_ptr
    }
    vp.push_back(make_int(rand() % 1000));//ok because arg is temporary
    for_each(vp.begin(), vp.end(), show);
    unique_ptr<int> pup(make_int(rand() % 1000));
   // shared_ptr<int> spp(pup);//not allowed. pup is lvalue
    shared_ptr<int> spr(make_int(rand() % 1000));

    return 0;
}