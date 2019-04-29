#include <stdio.h>
#include <stdlib.h> //rand()
#include <pthread.h>
#include <time.h>   //clock()

int cnt = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void *myThread(void *arg) {
    for(int i = 0; i<100000000; i++) {
        /* 非原子操作 */
        //cnt ++;
        
        /* 仿原子操作 */
        pthread_mutex_lock(&mutex);
        cnt ++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


int main(){
    clock_t beginTime, endTime;
    beginTime = clock();    //计时开始
    
    pthread_t id1, id2;
    pthread_create(&id1, NULL, myThread, NULL);
    pthread_create(&id2, NULL, myThread, NULL);
    pthread_join(id1, NULL); //主线程等待id1线程结束
    pthread_join(id2, NULL); //主线程等待id2线程结束
    printf("cnt = %d \n", cnt);
    
    
    
    /* 测试volatile int cnt = 0 不优化速度，但没什么区别 */
    endTime = clock();    //计时结束
    int delta = (endTime - beginTime )/CLOCKS_PER_SEC;
    printf("Runing time = %d s \n", delta);
    
    return 0;
}


/* 说明
cnt++
在理想中是这样执行的：
                        cnt | reg
线程1: cnt     ->  reg    0     0
线程1: reg+1   ->  reg    0     1
线程1: reg     ->  cnt    1     1
 
 
 
                        cnt | reg
线程2: cnt     ->  reg    1     1
线程2: reg+1   ->  reg    1     2
线程2: reg     ->  cnt    2     2
 
cnt结果2，正确
但实际会收到调度影响：
                        cnt | reg
线程1: cnt     ->  reg    0     0
线程1: reg+1   ->  reg    0     1
线程2: cnt     ->  reg    0     1
线程2: reg+1   ->  reg    0     1
 
线程1: reg     ->  cnt    1     1
线程2: reg     ->  cnt    1     1
 
cnt结果为1，错误
（上述程序，实行非原子操作，cnt结果每次都不同。）
 
所以，用锁来仿原子操作（一气呵成）。
