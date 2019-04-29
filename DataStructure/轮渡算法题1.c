/* Author: Pinghong Deng
 * Github: wishkind
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
typedef struct _gameobject {
	int id;
	char *color;
	char *name;
	} gameobject;

typedef struct _dqueue {
    int header;
    int tail;
    void **obj;
    int size;
    int num;
    int flag;
}dqueue;

dqueue *qboat;

dqueue *qcar ;
dqueue *qtruck ;
dqueue*  queue_create(int size) {
	dqueue *q = malloc(sizeof(dqueue));
		if(q == NULL) {
			perror("queue malloc error\n");
			exit(-1);
			}
		q->size = size;
		q->flag = 0; 
		q->header = 0;
		q->tail = 0;
		q->num = 0;
		q->obj = malloc(q->size * sizeof(void*));
		if(q->obj == NULL) {
			perror("queue->obj malloc error\n");
			exit(-1);
			}
	return q;
}

int queue_init(dqueue *q) {
		if (q == NULL) {
			perror("queue not created error \n");
			exit(-1);
			}
		q->header = 0; 
		q->tail = 0;
		q->num = 0;
		q->flag = 0;
	return 1;		
}

int queue_isempty(dqueue *q) {
	if(q == NULL) {
			perror("queue not created error\n");
			exit(-1);
		}
	if ((q->header == q->tail) && (q->flag == 0)) {
		return 1;
		}
	return 0;
}
int queue_isfull(dqueue *q) {
	if(q == NULL)
		{
			perror("queue not created error\n");
			exit(-1);
	}
	return ((q->header == q->tail) && (q->flag == 1)) ? 1 : 0;
}
int queue_push(dqueue *q, void *data) {
		if(q == NULL || data == NULL) {
			perror("queue not created or data is null error \n");
			exit(-1);
			}
		if(queue_isfull(q)) {
			printf("queue is full ,please wait\n");
			return 0;
			}


		q->obj[q->tail] = data;
		q->tail = (q->tail +1) % q->size;
		q->num++;
		if(q->tail == q->header && q->flag == 0 ) q->flag = 1;
	return 1;
	}
void *queue_pop(dqueue *q) {
		if(q == NULL) {
			perror("queue not created error\n");
			exit(-1);
		}
	if(queue_isempty(q)) {
		printf("queue if empty ,please wait\n");
		return NULL;
		}
	void *data = q->obj[q->header];
		q->header = (q->header + 1) % q->size;
		q->num--;
		if(q->header == q->tail) q->flag = 0;
		
	return data;
}

void *car(void *arg) {

	int delta;
	int i = 0;
	char *color[3] = {"red", "blue", "green"};
    char *name[5] ={ "奔驰", "宝马", "劳斯莱斯", "卡迪拉克", "丰田"};
	while(1) {
		if(queue_isfull(qboat)) continue;
		delta  = rand() % 5;
		gameobject *car = malloc(sizeof(gameobject));
		car->id = i;
		i++;
		car->color = color[rand() % 3];
		car->name = name[rand() % 5];
		queue_push(qcar, (void*)car);
        printf("car come in :pointer = %p, id = %d, color = %s, name = %s\n", car, car->id, car->color, car->name);
		sleep(delta);
	

	}
	pthread_exit(NULL);
	return (void*)1;
}

void *truck(void *arg) {

        int delta;
	int i = 0;
        while(1) {
                if(queue_isfull(qtruck)) continue;
                delta  = rand() % 5;
                gameobject *truck = malloc(sizeof(gameobject));
		truck->id = i;
		truck->color = "red";
		truck->name = "tractor";
	i++;
                queue_push(qtruck, (void*)truck);
                sleep(delta);
 printf("truck come in :pointer = %p, id = %d, color = %s, name = %s\n", truck, truck->id, truck->color, truck->name);
        }
	pthread_exit(NULL);
        return (void*)1;
}



void *boat(void *arg) {

    int delta;
    int num = 0;
    char c;
	gameobject *g;
    while(1) {

            while(qcar->num) {
                    delta = rand() % 2;
                queue_push(qboat, queue_pop(qcar));
		 sleep(delta);
                num++;
                if (num == 4) {
                    break;
                }
            }

        if(qtruck->num) {
            delta = rand() % 2;
            queue_push(qboat, queue_pop(qtruck));
            num++;
        }
        if(num == 10) {
            printf("go\n");
		while(qboat->num){
			g = (gameobject*)queue_pop(qboat);			
		 printf("car : pointer = %p, id = %d, color = %s, name = %s\n", g, g->id, g->color, g->name);
}
break;
        }
    }
	pthread_exit(NULL);
return (void *)1;
}
		





int main(int argc, char **argv) {
	srand(time(NULL));
	qboat = queue_create(1024);
		
	qcar = queue_create(1024);
	qtruck = queue_create(1024);
	pthread_t tcar,ttruck,tboat;
	pthread_attr_t attr;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	printf("game begin\n");
	queue_init(qboat);
	queue_init(qcar);
		queue_init(qtruck);
	pthread_create(&tcar, NULL, car, (void *)&tcar);
	pthread_create(&ttruck, NULL, truck, (void *)&ttruck);
	pthread_create(&tboat, NULL, boat, (void *)&tboat);
	//pthread_join(tboat, NULL);
	pthread_exit(NULL);
	printf("game over\n");
	return 1;
}

