#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* thread_0(void* data)
{

    //pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    //pthread_setcancelstate(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    
    printf("thread_0: start\n");
    
    pthread_mutex_lock(&mutex);
    printf("thread_0: lock\n");
    
    pthread_cond_wait(&cond, &mutex);
    printf("thread_0: wait\n");

    pthread_mutex_unlock(&mutex);
    printf("thread_0: unlock\n");
    
    pthread_exit(NULL);
}

void* thread_1(void* data)
{
    //sleep(5);
    printf("thread_1: start\n");
    
    pthread_mutex_lock(&mutex);
    printf("thread_1: lock\n");
    
    pthread_cond_broadcast(&cond);
    printf("thread_1: broadcast\n");
    
    pthread_mutex_unlock(&mutex);
    printf("thread_1: unlock\n");
    
    pthread_exit(NULL);
}



int main()
{
    pthread_t tid[2];
    if (pthread_create(&tid[0], NULL, thread_0, NULL) != 0)
    {
        exit(1);
    }
    if (pthread_create(&tid[1], NULL, thread_1, NULL) != 0)
    {
        exit(1);
    }
    
    //有趣在这个sleep
    //子线程执行需要点时间
    //主线程跑得快，一下退出进程，导致子线程来不及执行完，非正常退出
    //sleep(2);
    printf("main: 1\n");

    pthread_cancel(tid[0]); //打开有死锁，关闭没有死锁
    
    //主线程等待这2个子线程结束，子线程之间执行顺序不管
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    
    printf("main: return \n");
    
    return 0;
}



//产生死锁的原因就是因为线程0被取消后，没有执行 pthread_mutex_unlock(&mutex); 。导致线程1一直获取不到 mutex 而产生死锁现象。
//pthread_cond_wait 就是一个可取消点
