#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    pid_t  pid;
    
    //循环创建子进程
    int i = 0;
    while(i<10)
    {
        i++;
        
        pid = fork();
        if (pid < 0)
        {
            perror("fork error:");
            exit(1);
        } else if (pid == 0)
        {
            printf("child process %d\t  ppid %d \n I am exiting.\n", getpid(), getppid());
            //子进程退出，成为僵尸进程
            exit(0);
        }
        else
        {
            //父进程休眠20s后继续创建子进程
            sleep(10);
            continue;
        }
    }
    
    system("ps -o pid,ppid,state,command");
    return 0;
}
