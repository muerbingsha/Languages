#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main() {
    pid_t pid;
    
    //创建一个进程
    pid = fork();
    
    //创建失败
    if (pid < 0){
        perror("fork error:");
        exit(1);
    }
    
    //子进程
    if (pid == 0) {
        printf("-----child process\n");
        //输出进程ID和父进程ID
        printf("pid: %d\t  ppid:%d\n", getpid(), getppid());
        printf("child sleep five seconds.\n");
        //睡眠5s，保证父进程先退出
        sleep(5);
        printf("pid: %d\t  ppid:%d \n", getpid(), getppid()); //ppid: i //init进程
        printf("child process is exited.\n");
        
        system("ps -ef |grep a.out");
        
    }
    //父进程
    else{
        printf("-----father process.\n");
        //父进程睡眠1s，保证子进程输出进程id
        sleep(1);
        printf("father process is exited.\n");
        
        system("ps -ef |grep a.out");

    }

    return 0; //父进程退出
}

