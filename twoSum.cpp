#include <iostream>

using namespace std; 

int* twoSumA(int* nums, int numsSize, int target) {  
    int *a = (int*)malloc(2*sizeof(int));  
    for(int i = 0;i<numsSize;i++)  
    {  
        for(int j = i+1;(j<numsSize && j != i);j++)  
        {  
            if(nums[i] + nums[j] == target)  
            {  
                a[0] = i;  
                a[1] = j;  
            }  
        }  
    }  
    return a;  
} 


int* twoSumB(int* nums, int numsSize, int target) {
    int min = 2147483647;
    int i = 0;
    for (i = 0; i < numsSize; i++) {
        if (nums[i] < min)
            min = nums[i];
    }
    int max = target - min;
    int len = max - min + 1;   //确定hash长度
    int *table = (int*)malloc(len*sizeof(int));
    int *indice = (int*)malloc(2*sizeof(int));
    for (i = 0; i < len; i++) {
        table[i] = -1;         //hash初值
    }
    for (i = 0; i < numsSize; i++) {
        if (nums[i]-min < len) {
            if (table[target-nums[i]-min] != -1) {        //满足相加为target
                indice[0] = table[target-nums[i] - min];
                indice[1] = i;
                return indice;
            }
            table[nums[i]-min] = i;
        }
    }
    free(table);
    return indice;
} 

int main()
{
    int a[]={2, 11, 7, 15};  
    int b[2];  
    int *p = b;  
    int numsize = sizeof(a)/sizeof(int);
    int targrt = 9;  
    //cout<<"Input array count:";  
    //cin>>numsize;  
    //cout<<"Input target value:";  
    //cin>>targrt;  
    //cout<<"Input array value:";  
    //for(int i=0;i<numsize;i++)  
      //  cin>>a[i];  
    p = twoSumB(a,numsize,targrt);  
    cout<<*p<<" "<<*(p+1)<<endl;  
    return 0;  
}