#include<stdio.h>
#include<set>
#include<string>
using namespace std;
struct People
{
	string name;
	int age;
	bool operator <(const People p) const  //运算符重载 
	{
		return age<p.age;       //按照年龄由小到大进行排序 
	}
}; 
int main()
{	
	set<People>s;
	s.insert((People){"张三",14});
	s.insert((People){"李四",16});
	s.insert((People){"王二麻子",10});
	set<People>::iterator it;            
	for(it=s.begin();it!=s.end();it++)  //使用迭代器进行遍历 
	{
		printf("姓名：%s 年龄：%d\n",(*it).name.c_str(),(*it).age);
	}
	return 0;
}
/*
输出结果
 姓名：王二麻子 年龄：10
姓名：张三 年龄：14
姓名：李四 年龄：16 
*/ 