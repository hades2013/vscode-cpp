
#include <iostream>
#include <queue>
using namespace std;


int main(int argc, char * argv[])
{
	queue<int> myQueue;
	cout << myQueue.empty() << endl;
	cout << myQueue.size()<< endl;
	myQueue.push(1);
	myQueue.push(2);
	myQueue.push(3);
	cout << myQueue.front()<<endl;
	cout << myQueue.back()<<endl;
	myQueue.pop();
	cout << myQueue.front()<<endl;
	cout << myQueue.back()<<endl;	
	return 0;
}

