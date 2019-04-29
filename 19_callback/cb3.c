

#include <stdio.h>

int add_ret(int a, int b);

//callback函数定义
//返回类型 函数指针 参量类型
//int (*callback_name)(int, int)


//开发者层面
int add(int a, int b, int (*add_value)(int, int))
{
    return (*add_value)(a, b);
}


//用户层面，自定义回敲
int main(void)
{
    int sum = add(3,4,add_ret);
    printf("sum:%d\n",sum);
    return 0 ;
}

int add_ret(int a, int b)
{
    return a+b ;
}

