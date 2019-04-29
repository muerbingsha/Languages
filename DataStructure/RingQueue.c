/* Ring Queue */

#include <jemalloc/jemalloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



typedef struct _ringQueue {
    int head;
    int tail;
    int size;
    int count;
    int tag;
    char **data;
    int (*isFull)(struct _ringQueue *q);
    int (*isEmpty)(struct _ringQueue *q);
    void (*push)(struct _ringQueue *q, char *data);
    char* (*pop)(struct _ringQueue *q);
    void (*print)(struct _ringQueue *q);
} ringQueue;



void push(ringQueue *q, char *data) {
    if (!q) return;
    if (q->isFull(q) == 0) {
        perror("queue is full\n");
        return;
    }
    q->count++;
    q->data[q->tail] = data;
    q->tail = (q->tail + 1) % q->size;
    if (q->tail == q->head) q->tag = 1;
}

char* pop(ringQueue *q) {
    if (!q) return NULL;
    if (q->isEmpty(q) == 0) {
        perror("queue is empty\n");
        return NULL;
    }
    q->count--;
    char *tmp = q->data[q->head];
    q->head = (q->head + 1) % q->size;
    if (q->head == q->tail) q->tag = 0;
    return tmp;
}

int isQueueEmpty(ringQueue *q){
    if (!q) return -1;
    if (q->head == q->tail && q->tag == 0) return 0;
    return -1;
}

int isQueueFull(ringQueue *q) {
    if (!q) return -1;
    if (q->head == q->tail && q->tag == 1)  return 0;
    return -1;
}

void printQueue(ringQueue *q) {
    printf("\n*head ");
    for(int i=0; i<q->count; i++){
        printf("%s --> ", q->data[i]);
    }
    printf(" *end\n");
}

ringQueue* createQueue(int size) {
    ringQueue *q = je_malloc(sizeof(ringQueue));
    if (q == NULL) {
        perror("ringQueue create failed\n");
        exit(-1);
    }
    memset(q, '\0', sizeof(ringQueue));
    q->head = q->tail = q->tag = q->count = 0;
    q->size = size;
    
    q->isFull = isQueueFull;
    q->isEmpty = isQueueEmpty;
    q->push = push;
    q->pop = pop;
    q->print = printQueue;
    
    q->data = je_malloc(size * sizeof(char*));
    if (q->data == NULL) {
        perror("data create failed\n");
        je_free(q);
        exit(-1);
    }
    memset(q->data, '\0', sizeof(char *) * size);
    
    return q;
}

void freeQueue(ringQueue *q) {
    if (!q) return;
    je_free(q);
}



int main(int argc, char* argv[]) {
    ringQueue *q = createQueue(8);
    q->push(q, "Name: Shark");
    q->push(q, "Location: Big Sur");
    q->push(q, "Website: jobyme88.com");
    q->push(q, "Role: Wizard");
    q->push(q, "Gift: infinity");
    q->push(q, "Weapon: MachineGun");
    q->push(q, "Friends: 100");
    q->push(q, "DefeatedEnemy: 10");
    q->push(q, "FightPower: 8");
    q->print(q);
    printf("\n---------------------\n");
    
    char *name = q->pop(q);
    char *location = q->pop(q);
    char *website = q->pop(q);
    char *role = q->pop(q);
    char *gift = q->pop(q);
    char *weapon = q->pop(q);
    char *friends = q->pop(q);
    char *defeatedEnemy = q->pop(q);
    printf("This player info: \nname: %s\nlocation: %s\nwebsite: %s\nrole: %s\ngift: %s\nweapon: %s\nfriends: %s\ndefeatedEnemy: %s\n", name, location, website, role, gift, weapon, friends, defeatedEnemy);

    char *fightPower = q->pop(q);
    
    return 0;
}
