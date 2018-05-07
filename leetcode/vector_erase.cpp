#include <stdio.h>
#include <vector>
using namespace std;

int main(){
    vector<int> v;
    for (int i = 0; i < 10; i++){
            v.push_back(i);
    }

    for (vector<int>::size_type ix = 0; ix != v.size(); ix ++){
            printf("%d\t", v[ix]);
    }
    printf("\n");

    //在开始插入10,10,10
    v.insert(v.begin(), 3, 10);
    for (vector<int>::size_type ix = 0; ix != v.size(); ix ++){
            printf("%d\t", v[ix]);
    }
    printf("\n");

    //删除第二个10
    int i = 0;
    vector<int>::iterator it;
    for (it = v.begin(); it != v.end(); it++){
            i++ ;
            if (i == 2){
                    v.erase(it);
                    break;
            }
    }

    for (vector<int>::size_type ix = 0; ix != v.size(); ix ++){
            printf("%d\t", v[ix]);
    }
    printf("\n");


    return 0;
}