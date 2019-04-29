#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    pid = fork();
    
    if (pid < 0)
    {
        perror("fork error:");
        exit(1);
    } else if (pid == 0) {
        printf("child process %d is exiting.\n", getpid());
        exit(0);
    }
    
    printf("father process.I will sleep two seconds\n");
    //等待子进程先退出
    sleep(2);
    
    //输出进程信息
    system("ps -o pid,ppid,state,tty,command"); //不要有空格
    printf("father process is exiting.\n\n\n\n\n\n");
    
    system("ps -ef | grep a.out");
    return 0;
}


