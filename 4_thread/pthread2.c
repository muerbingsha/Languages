//实现功能: 2个线程对count每次分别加1, 第三个线程等count大于10后一次加100.
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define THREAD_NUM 3
#define COUNT_LIMIT 10


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int sum = 0;
int thread_ids[3] = {0, 1, 2};

void* count1(void *args)
{

	for(int i = 0; i <10; i++)
    {
		pthread_mutex_lock(&mutex);
 		sum++;
		pthread_cond_signal(&cond);
		printf("thread %d, sum = %d\n", *(int *)args, sum);
		pthread_mutex_unlock(&mutex);
		sleep(1);
    }
	printf("thread %d, Threadshold reached\n", *(int *)args);
	pthread_exit(NULL);
}


void *watch_count(void *args) {
    
	printf("Starting: thread %d\n", *(int*)args);
    
	pthread_mutex_lock(&mutex);
	while(sum < 10) {
		sleep(3);
        pthread_cond_wait(&cond, &mutex);
        printf("watch_count: thread %d, Condition signal received.\n", *(int*)args);
	}
	sum += 100;
	pthread_mutex_unlock(&mutex);
    
	pthread_exit(NULL);
}


int main(int argc, char **argv)
{
    pthread_t threads[3];
    
    //pthread_mutex_init(&mutex, NULL);
    //pthread_cond_init(&cond, NULL);

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    
    pthread_create(&threads[0], &attr, count1, (void *)&thread_ids[0]);
    pthread_create(&threads[1], &attr, count1, (void *)&thread_ids[1]);
    pthread_create(&threads[2], &attr, watch_count, (void *)&thread_ids[2]);


    for (int i=0; i<THREAD_NUM; i++){
        pthread_join(threads[i], NULL);
    }
    
    printf("final sum %d\n", sum);
    
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    pthread_exit(NULL);
    printf("main return\n");
    return 0;
}
    

