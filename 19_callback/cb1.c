#include <stdio.h>
void stp();

int main(void)
{
    void (*fuc)();   //定义函数指针，返回类型是void
    fuc = stp;       //函数指针赋值
    fuc();           //执行，相当于调用stp
}

void stp()
{
    printf("hello world!\n");
}
