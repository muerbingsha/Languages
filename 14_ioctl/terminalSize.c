#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(void)
{
    struct winsize size;    //该结构体是在sys/ioctl.h中被内核定义的
    
    //isatty(fd);           //作用是检测fd中的文件描述符是否为tty终端文件,是则返回大于0的数
    if (isatty(STDOUT_FILENO) == 0)
        exit(1);
    
    //获取终端窗口的大小,将获取的值放到size结构体中
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &size)<0) {
        perror("ioctl TIOCGWINSZ error");
        exit(1);
    }
    
    printf("%d rows, %d columns\n,%d", size.ws_row, size.ws_col,size);
    return 0;
}
//在图形界面的终端里多次改变终端窗口的大小并运行该程序，观察结果。
