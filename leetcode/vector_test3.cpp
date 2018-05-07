#include <stdio.h>
#include <vector>
using namespace std;

int main(){
    //第一种定义方法
    vector<int> v;
    for (int i = 0; i < 10; i++){
            v.push_back(i);
    }

    //第二种定义方法
    vector<int> v1(v);
    //第三种定义方法
    vector<int> v2(10, 1);
    //第四种定义方法
    vector<int> v3(10);

    printf("first: ");
    for (vector<int>::size_type ix = 0; ix != v.size(); ix ++){
            printf("%d\t", v[ix]);
    }
    printf("\n");
    printf("second: ");
    for (vector<int>::size_type ix1 = 0; ix1 != v1.size(); ix1 ++){
            printf("%d\t", v1[ix1]);
    }
    printf("\n");
    printf("third: ");
    for (vector<int>::size_type ix2 = 0; ix2 != v2.size(); ix2 ++){
            printf("%d\t", v2[ix2]);
    }
    printf("\n");
    printf("forth: ");
    for (vector<int>::size_type ix3 = 0; ix3 != v3.size(); ix3 ++){
            printf("%d\t", v3[ix3]);
    }
    printf("\n");

    return 0;
}