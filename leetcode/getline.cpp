#include<iostream>
using namespace std;

int main() {
    const int size = 20;
    char *str = new char[size];
    cout << "get():" << endl;
    cout << "请输入字符串: ";
    cin.get(str, size);
    cout << "the string is: " << str << endl;

    delete[]str;
    str = new char[size];
    cout << "请再次输入字符串: ";
    //cin.get();
    cin.get(str, size);
    cout << "the string now is: " << str << endl;
    delete[]str;

    return 0;
}