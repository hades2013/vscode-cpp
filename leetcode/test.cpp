#include <iostream>
using namespace std; 
class A
{
public:
	A() { m_a = 1, m_b =2; }
	~A(){}
	void fun() { printf("%d \t%d\n", m_a, m_b); }
	int m_a;
	int m_b;
};
class B
{
public:
	B() { m_c = 3;}
	~B(){}
	void fun() {printf("%d\n",m_c); } //为什么是1，思考！
	int m_c;
};
int main()
{
	A a;
	B *pb = (B*)&a;
	pb->fun(); //为什么是1，思考！
	cout << &a<<endl; //12FF6C
	cout << &(a.m_a)<<endl; //12FF6C
	printf("%08x\n",&A::m_a);
	printf("%08x\n",&A::m_b);
	printf("%08x\n",&B::m_c);
	return 0;
}
