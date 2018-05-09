#include<stdio.h>
#include<stdlib.h>

char* substring(char* ch,int pos,int length)  
{  
    char* pch=ch;  
//定义一个字符指针，指向传递进来的ch地址。  
    char* subch=(char*)calloc(sizeof(char),length+1);  
//通过calloc来分配一个length长度的字符数组，返回的是字符指针。  
    int i;  
//只有在C99下for循环中才可以声明变量，这里写在外面，提高兼容性。  
    pch=pch+pos;  
//是pch指针指向pos位置。  
    for(i=0;i<length;i++)  
    {  
        subch[i]=*(pch++);  
//循环遍历赋值数组。  
    }  
    subch[length]='\0';//加上字符串结束符。  
    return subch;       //返回分配的字符数组地址。  
} 

int main(){
    char* result;
    char* tstStr = "abcdefg";
    result = substring(tstStr,0,2);
    
    printf("结果：%s",result);
    
}