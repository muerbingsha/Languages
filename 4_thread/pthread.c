
#include <stdio.h>  //printf
#include <string.h> //memset
#include <unistd.h> //sleep
#include <pthread.h>

/*
//数据属性
pthread_t                       //线程id
pthread_attr_t                  //线程属性

//操作函数
pthread_create()                //创建线程
pthread_exit();                 //终止线程
pthread_cancel();               //中断线程运行
pthread_join();
pthread_attr_init()
pthread_attr_setdetachstate();
pthread_attr_getdetachstate();
pthread_attr_destroy();
pthread_kill();

//同步函数
pthread_mutex_init();
pthread_mutex_destroy();
pthread_mutex_lock();
pthread_mutex_trylock();
pthread_mutex_unlock();

pthread_cond_init();
pthread_cond_destroy();
pthread_cond_signal();
pthread_cond_wait();

pthread_key_create();
pthread_key_delete();

pthread_attr_getschedparam();
pthread_attr_setschedparam()


//工具函数
pthread_equal();
pthread_detach();
pthread_self();
*/




#define MAX 5
pthread_t thread[2];
pthread_mutex_t mut;

int number = 0, i;

void *thread1(){
    printf ("thread1 : I'm thread 1\n");
    
    for (i = 0; i < MAX; i++){
        printf("thread1 : number = %d\n",number);
        
        pthread_mutex_lock(&mut);
        number++;
        pthread_mutex_unlock(&mut);
        
        sleep(2);
    }
    
    printf("thread1 :主函数在等我完成任务吗？\n");
    pthread_exit(NULL);
}


void *thread2() {
    printf("thread2 : I'm thread 2\n");
    
    for (i = 0; i < MAX; i++){
        printf("thread2 : number = %d\n",number);
        
        pthread_mutex_lock(&mut);
        number++;
        pthread_mutex_unlock(&mut);
        
        sleep(3);
    }
    
    printf("thread2 :主函数在等我完成任务吗？\n");
    pthread_exit(NULL);
}



void thread_create(void) {
    int temp;
    memset(&thread, 0, sizeof(thread));
    
    /*创建线程*/
    if((temp = pthread_create(&thread[0], NULL, thread1, NULL)) != 0)
        printf("线程1创建失败!\n");
    else
        printf("线程1被创建\n");
            
    if((temp = pthread_create(&thread[1], NULL, thread2, NULL)) != 0)
        printf("线程2创建失败");
    else
        printf("线程2被创建\n");
    }


void thread_wait(void){
    /*等待线程结束*/
    if(thread[0] !=0) {
        pthread_join(thread[0],NULL);
        printf("线程1已经结束\n");
    }
    
    if(thread[1] !=0) {
        pthread_join(thread[1],NULL);
        printf("线程2已经结束\n");
    }
}


int main() {
    
    /*用默认属性初始化互斥锁*/
    pthread_mutex_init(&mut, NULL);
    
    printf("我是主函数哦，我正在创建线程，呵呵\n");
    thread_create();
    
    printf("我是主函数哦，我正在等待线程完成任务阿，呵呵\n");
    thread_wait();
    
    return 0;
}


