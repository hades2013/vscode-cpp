#include <stdio.h>
#include <vector>
using namespace std;

int main(){
    vector<int> v;
    for (int i = 0; i < 10; i++){
            v.push_back(i);
    }
    //利用下标      
    for (vector<int>::size_type ix = 0; ix != v.size(); ix ++){
            printf("%d\t", v[ix]);
    }
    printf("\n");

    //利用迭代器
    vector<int>::iterator it;
    for (it = v.begin(); it != v.end(); it ++){
            printf("%d\t", *it);
    }
    printf("\n");


    return 0;
}