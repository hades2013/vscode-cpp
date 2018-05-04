#include<iostream>
#include<vector>
#include<list>
using namespace std;
int main()
{
    vector<int> v;
    list<int> l;
    for(int i=0;i<8;i++) ////往v和l中分别添加元素
    {
        v.push_back(i);
        l.push_back(i);
    }
    cout<<"v[2]="<<v[2]<<endl;
    //cout<<"l[2]="<<l[2]<<endl;  //编译错误,list没有重载[]
    cout<<(v.begin()<v.end())<<endl; 
    //cout<<(l.begin()<l.end())<<endl; /编译错误,list::iterator没有重载<或>
    cout<<*(v.begin()+1)<<endl;
    //cout<<*(l.begin()+1)<<endl; //编译错误,list::iterator没有重载+
    vector<int>::iterator itv=v.begin();
    list<int>::iterator itl=l.begin();
    itv = itv+2;
    //itl=itl+2; //编译错误,list::iterator没有重载+
    itl++; //list::iterator中重载了++，只能使用++进行迭代访问。
    itl++;
    cout<<*itv<<endl;
    cout<<*itl<<endl;
    getchar();
    return 0;
}