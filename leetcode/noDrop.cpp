#include <iostream>  
#include <vector> 
   
using namespace std;  
int maxLongNoDrop(const vector<int> &Arr)  
{  
    vector<int> stackVec;  
    stackVec.push_back(-999999);//初始化第一个数为一个尽可能小的值  
    for (size_t i = 0; i < Arr.size(); i++)  
    {  
        if (Arr[i] > stackVec.back())//stackVec.back()该数组最前面的这个值  
        {  
            stackVec.push_back(Arr[i]);//将形成一个有序的数组  
        }  
        else  
        {  
            int mid = 0, low = 1, high = stackVec.size()-1;  
            //二分检索“数组栈”（有序的）中比当前Arr[i]大的第一个数的位置（为low）  
            while (low <= high)  
            {  
                mid = (low + high) / 2;  
                if (Arr[i] > stackVec[mid])  
                    low = mid + 1;  
                else  
                    high = mid - 1;  
            }  
            //替换之  
            stackVec[low] = Arr[i];  
        }  
    }  
   
    return (stackVec.size() - 1);  
}  
   
int main()  
{  
    int n = 0;  
    while (cin>>n)  
    {  
        vector<int> srcArr(n, 0);  
        for (size_t i = 0; i < n; i++)  
            cin >> srcArr[i];  
        cout << maxLongNoDrop(srcArr) << endl;  
    }  
    return 0;  
}  