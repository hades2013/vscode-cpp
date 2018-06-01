#include <stdio.h>
#include <time.h>
#include <setjmp.h> // 非局部跳zhuan

jmp_buf jump_buffer;

/*
=========================================================
time：           2017年1月25日14:37:54
objective：      test C language's  head file of <setjmp.h> 
version：        Microsoft Visual C++
author:         ChenFei
remark:         日文system  有些字没法打要用pin音代替
=========================================================
*/

/*
    setjmp( jmp_buf ) 相当于跳zhuan点，   jmp_buf wei宏定yi lei型
    longjmp(jmp_buf, int) 相当于 goto ,    int wei 返回gei setjmp( jmp_buf ) 的参数

    setjmp() diao用 jmp_buf, 返回zhi wei 0，longjmp() diao用 jmp_buf, 返回zhi wei其参数。

    main 中的 setjmp(jump_buffer) -> func1 中的 func() --
    -> func 中的 longjmp(jump_buffer, 2); -> mian 中的 a = setjmp(jump_buffer); --
    -> a = 2;
*/

void func(void)
{
         printf("Before calling longjmp\n");
         longjmp(jump_buffer, 2);
         printf("After calling longjmp\n");
}
void func1(void)
{
         printf("Before calling func\n");
         func();
         printf("After calling func\n");
}

int main(void)
{   
    int a;
    a = setjmp(jump_buffer);
    printf("%d\n",a);
    if (a == 0){
        printf("%d\n",a);
        printf("first calling set_jmp\n");
        func1();
     }else {
        printf("%d\n",a);
        printf("second calling set_jmp\n");
     }

    return 0;
}