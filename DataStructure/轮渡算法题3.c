/* Author: Shark
 * Github: muerbingsha
 * 题目：P87-4, 某汽车轮渡口，过江渡船每次能载10辆车过江，过江车辆分为客车类和货车类，上渡船有如下规定：
 * 同类车先到先上船；
 * 客车先于货车上船，且每上4辆客车，才允许上一辆货车；
 * 若等待客车不足4辆，则以货车代替；
 * 若无货车等待，允许客车都上船，
 * 试设计一个算法模拟渡口管理。
 * 实现效果：客车货车交错上船。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <pthread.h>
#include <jemalloc/jemalloc.h>
#include <fcntl.h>
#include <ctype.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>



typedef struct _queue queue;
FILE *waitLog, *boardLog;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
queue *busQ, *truckQ, *boardQ;
int ticketNum = 0; //起始票号

typedef struct _car {
    int id;    //票号
    int type;   //0客车， 1货车
} car;

car* createCar(){
    car *c = je_malloc(sizeof(car));
    if (c == NULL )
    {
        perror("car create failed\n");
        exit(-1);
    }
    // c->type = rand() % 2;
    c->type = (arc4random()) % 2;
    //c->type = random() % 2;
    //c->type = arc4random_uniform(2);
    c->id = ++ticketNum;
    
    return c;
}


/**********************************************
 *----------------------队列区------------------
 **********************************************/


struct _queue
{
    void (*push)(struct _queue *q, car *c);
    car* (*pop)(struct _queue *q);
    int (*isFull)(struct _queue *q);
    int (*isEmpty)(struct _queue *q);
    
    int size;
    int count;   //当前等待数
    int head;
    int tail;
    car** cars;
};


void pushQueue(queue *q, car *c)
{
    if (!q || !c) return;
    if (q->isFull(q) == 0)
    {
        printf("waitQueue is full\n");
        return;
    }
    q->count++;
    q->cars[q->tail] = c;
    q->tail = q->tail + 1;
    return;
}


car *popQueue(queue *q)
{
    if (!q) return NULL;
    if (q->isEmpty(q) == 0)
    {
        printf("waitQueue is Empty\n");
        return NULL;
    }
    q->count--;
    car *tmp = q->cars[q->head];
    q->head = q->head + 1;
    if (q->head == q->tail) q->head = q->tail = 0;
    return tmp;
}


void freeQueue(queue *q)
{
    if (!q) return;
    for (int i; i<q->count; i++)
    {
        je_free(q->cars[i]);
    }
    je_free(q);
}


int isFullQueue(queue *q)
{
    if (!q) return -1;
    if (q->count == q->size) return 0;
    return -1;
}


int isEmptyQueue(queue *q)
{
    if (!q) return -1;
    if(q->count == 0) return 0;
    return -1;
}


queue* createQueue(int size)
{
    queue *q = je_malloc(sizeof(queue));
    if (q == NULL)
    {
        perror("waitQueue create failed\n");
        exit(-1);
    }
    memset(q, '\0', sizeof(queue));
    q->size = size;
    
    q->cars = je_malloc(q->size * sizeof(car));
    if (q->cars == NULL )
    {
        perror("waiQueue cars create failed\n");
        je_free(q);
        exit(-1);
    }
    
    q->push = pushQueue;
    q->pop = popQueue;
    q->isFull = isFullQueue;
    q->isEmpty = isEmptyQueue;
    
    return q;
}

void logWaitQueue(int first, car *c)
{
    char tmp[50] = {'\0'};
    
    if (first == 1)
    {
        waitLog = fopen("carWait.log", "a+");
        fprintf(waitLog, "--BusQueue--|--TruckQueue--\n");
        
        if (waitLog == NULL)
        {
            perror("open carWait.log failed\n");
            exit(-1);
        }
        
    } else
    {
        if (c->type == 0)
        {
            sprintf(tmp, "  客车号 %d   |\n", c->id);
            fprintf(waitLog, "%s", tmp);
        } else {
            sprintf(tmp, "            |  货车号 %d\n", c->id);
            fprintf(waitLog, "%s", tmp);
        }
    }

}


void logBoardQueue(queue *boardQ)
{
    boardLog = fopen("carBoard.log", "w");
    if (boardLog == NULL)
    {
        perror("open carBoard.log failed\n");
        exit(-1);
    }
    
    for(int i=0; i<boardQ->count; i++)
    {
        char *typeChar;
        if (boardQ->cars[i]->type == 0)
        {
            typeChar = "客车";
           } else {
            typeChar = "货车";
        }
        fprintf(boardLog, "%d, 类型：%s, 票号 %d\n", i, typeChar, boardQ->cars[i]->id);
    }
    
    if (boardQ->count == 10)
    {
        printf("\n------------\n");
    }

}


/**********************************************
 *----------------------装车区------------------
 **********************************************/


int bn = 0;     //已装客车数量
int flag = 0;   //装客车还是货车
int boardTruck()
{
    boardQ->push(boardQ, truckQ->pop(truckQ));
    return 0;
}

int boardCar ()
{
    boardQ->push(boardQ, busQ->pop(busQ));
    return 0;
   
}

//@param flag: 0上客车， 1上货车
void board(int flag)
{
    printf("decide flag %d\n", flag);
    
    if(flag == 0 && busQ->count != 0)
    {
        boardCar();
    } else if (flag == 1 && truckQ->count != 0){
        boardTruck();
    } else {
        return;
    }
    
    flag ^= 1;
    printf("---after flag %d\n", flag);
    board(flag);
}



/**********************************************
 *----------------------线程区------------------
 **********************************************/


void *gen (void *args) {
    
    printf("票务员 %d 号 上班啦!\n", *(int *)args);
    
    while (1)
    {
        pthread_mutex_lock(&mutex);
    
        car *c = createCar();
    
        if (c->type == 0){
            busQ->push(busQ, c);
            printf("票号 %d %s\n", c->id, "客车");
            logWaitQueue(0, c); //更新日志
        } else {
            truckQ->push(truckQ, c);
            printf("票号 %d %s\n", c->id, "货车");
            logWaitQueue(0, c); //更新日志
        }
        //pthread_cond_signal(&cond);
        
        pthread_mutex_unlock(&mutex);
       // sleep(arc4random() % 30);
        sleep(1);
        
    }
    
    return NULL;
}


void *shipManager(void *args)
{
    
    printf("shipManager %d 上班啦\n", *(int *)args);
    while (boardQ->count < 10) {
        pthread_mutex_lock(&mutex);
        
        /*
        while(busQ->count == 0 && truckQ->count == 0)
        {
            pthread_cond_wait(&cond, &mutex);
            printf("condition not satisfied\n");
        }*/
        if (busQ->count == 0 && truckQ->count == 0)
        {
            sleep(1);
        } else
        {
            board(0);
            logBoardQueue(boardQ);
        }
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }

    
    return NULL;
}




/**********************************************
 *----------------------入口区------------------
 **********************************************/


int main(int argc, char *argv[]) {

    
    pthread_t th[5];

    busQ = createQueue(20);
    truckQ = createQueue(20);
    boardQ = createQueue(10);
    
    logWaitQueue(1, NULL);
    
    pthread_create(&th[0], NULL, gen, (void *)&th[0]);
    //pthread_create(&th[1], NULL, gen, (void *)&th[0]);
    pthread_create(&th[2], NULL, shipManager, (void *)&th[2]);

    printf("%d, %d\n", busQ->count, truckQ->count);
    sleep(20);

    system("open carWait.log");
    system("open carBoard.log");

    return 0;
}
