#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#include <sys/wait.h>
#include <sys/types.h>


int main() {
    pid_t pid, pw;
    
    pid = fork();

    if (pid < 0) {
        puts("fork error");
        exit(1);
    } else if (pid == 0) {
        //子进程
        printf("----This is child process----\n");
        sleep(5);
        return 0;
    } else {
        //父进程
        pw = wait(NULL);
        printf("i catch a child process and this pid is %d \n", pw);
    }
    
    return 0;
}
