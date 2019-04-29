//FIFO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct _node {
    int data;
    struct _node *prev;
    struct _node *next;
} node;

typedef struct _queue {
    node *head;
    node *tail;
    void (*push)(struct _queue *q, node *n);
    node* (*pop)(struct _queue *q);
    void (*print)();
} queue;


void push(queue *q, node *n){
    if (!q || !n) return;
    //first
    if (q->head == NULL) {
        q->head = n;
        q->tail = n;
    } else {
        q->tail->next = n;
        n->prev = q->tail;
        q->tail = n;
    }
}

node* pop(struct _queue *q) {
    if (!q) return NULL;
    node *n = q->head;
    q->head = q->head->next;
    q->head->prev = NULL;
    return n;
}

void queue_print(queue *q){
    if (!q) return;
    

    printf("from tail: ");
    node *c = q->tail;
    while(c != NULL) {
        printf("%d --> ", c->data);
        c = c->prev;
    }
    printf(" head\n");
}

node* create_node(int data) {
    node *n = (node *)malloc(sizeof(node));
    if (n == NULL) return NULL;
    memset(n, '\0', sizeof(node));
    n->prev = NULL;
    n->next = NULL;
    n->data = data;
    return n;
}

queue* create_queue() {
    queue *q = (queue *)malloc(sizeof(queue));
    if (q == NULL) return NULL;
    memset(q, '\0', sizeof(queue));
    q->head = NULL;
    q->tail = NULL;
    
    q->push = push;
    q->pop = pop;
    q->print = queue_print;
    
    return q;
}

int main() {

    queue *q = create_queue();
    node *n1 = create_node(10);
    q->push(q, n1);
    node *n2 = create_node(20);
    q->push(q, n2);
    node *n3 = create_node(30);
    q->push(q, n3);
    
    q->print(q);

    node *n4 = q->pop(q);
    printf("n4 %d\n", n4->data);
    q->print(q);
  
    
    return 0;
    
}
