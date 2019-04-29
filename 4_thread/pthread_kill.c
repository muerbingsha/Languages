#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>




void handle_quit(int signo)
{
    printf("in qq handle sig %d \n", signo);
    //to show the print
    //pthread_exit is faster than printf
    sleep(1);
    pthread_exit(NULL);
}
void* test(void *arg)
{
    signal(SIGQUIT, handle_quit);
    for(int i=0;i<100;i++)
    {
        printf("in pthread test \n");
        sleep(1);
    }
    return (void*)0;
}

int main(void)
{
    pthread_t pid;
    pthread_create(&pid, NULL , test, NULL);
    
    //pid线程有5秒执行时间（打印5次in pthread test）
    //不加sleep，会阻塞在thread exists!不知道why
    sleep(5);
    
    
    if(pthread_kill(pid, 0)!= ESRCH)
    {
        printf("thread %d exists!\n", (int)pid);
        pthread_kill(pid, SIGQUIT);
        //pthread_exit(NULL);//this won't work
        printf("after kill\n");
    }

    return 0;
}
