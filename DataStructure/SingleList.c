#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

//single link list
typedef struct _LinkNode {
    struct _LinkNode *next;
    int data;
} LinkNode;

typedef struct _LinkList{
    LinkNode *head;
    LinkNode *tail;
    int count;      //当前节点数
    int maxCount;   //最大节点数
    
    int  (*singleList_insertTail)(struct _LinkList *l, LinkNode *node);
    int  (*singleList_insertHead)(struct _LinkList *l, LinkNode *node);
    int  (*singleList_insertAt)(struct _LinkList *l, int index, LinkNode *node);
    void (*singleList_removeTail)(struct _LinkList *l);
    void (*singleList_removeHead)(struct _LinkList *l);
    void (*singleList_removeAt)(struct _LinkList *l, int index);
    void (*singleList_removeNode)(struct _LinkList *l, LinkNode *node);
    void (*singleList_clear)(struct _LinkList *l);
    void (*singleList_print)(struct _LinkList *l);
}LinkList;



struct _LinkList* singleList_create(int size){
    struct _LinkList *l = malloc(sizeof(LinkList));
    bzero(l, sizeof(LinkList));
    if (size != 0){
        l->maxCount = size;
    } //or unlimited list
    return l;
}

int singleList_insertTail(struct _LinkList *l, LinkNode *node){
    if (l->maxCount != 0 && l->count == l->maxCount) {
        printf("list is full \n");
        return -1;
    }
    if (l->count == 0){
        l->head = node;
        l->tail = node;
        l->count ++;
        return 0;
    } else {
        l->tail->next = node;
        l->tail = node;
        l->count ++;
        return 0;
    }
    
    printf("insertTail failed \n");
    return -1;
    
}

int singleList_insertHead(struct _LinkList *l, LinkNode *node){
    if (l->maxCount != 0 && l->count == l->maxCount) {
        printf("list is full \n");
        return -1;
    }
    if (l->count == 0){
        l->head = node;
        l->tail = node;
        l->count++;
        return 0;
    } else {
        node->next = l->head;
        l->head = node;
        l->count++;
        return 0;
    }
    
    printf("insertHead failed \n");
    return -1;
}

int singleList_insertAt(struct _LinkList *l, int index, LinkNode *node){
    if (l->maxCount != 0 && l->count == l->maxCount) {
        printf("list is full \n");
        return -1;
    }
    
    if (index == 0){
        printf("use insertHead instead \n");
        return -1;
    } else if (index > l->count){
        printf("use insertTail instead \n");
        return -1;
    } else if (index < 1 || index > l->count) {
        printf("illegal index %d \n", index);
        return -1;
    } else {
        LinkNode *tmp = l->head;
        for (int i=1; i<(index-1); i++){
            tmp = tmp->next;
        }
        node->next = tmp->next;
        tmp->next = node;
        l->count++;
        return 0;
    }
    
    
    
    printf("insertAt %d failed \n", index);
    return -1;
}

void singleList_removeTail(struct _LinkList *l){
    
}
void singleList_removeHead(struct _LinkList *l){
    
}
void singleList_removeAt(struct _LinkList *l, int index){
    
}
void singleList_removeNode(struct _LinkList *l, LinkNode *node){
    
}

void singleList_clear(struct _LinkList *l){
    l->count = 0;
    l->head = l->tail = NULL;
}

void singleList_print(struct _LinkList *l){
    if (l->maxCount != 0) {
        printf("list's maxSize is %d \n, list's current element num is %d \n", l->maxCount, l->count);
    } else {
        printf("unlimited list, current element num is %d \n", l->count);
    }
    
    if (l->count == 0){
        printf("empty list\n");
        return;
    }

    
    printf("From head: %d", l->head->data);
    LinkNode *tmp = l->head;
    for (int i = 1; i<l->count; i++){
        if (tmp->next != NULL){
            tmp = tmp->next;
            printf(" --> %d ", tmp->data);
        } else {
            printf("\n");
        }
    }
    
}


void set_handle(LinkList *l){
    
    l->singleList_insertTail = singleList_insertTail;
    l->singleList_insertHead = singleList_insertHead;
    l->singleList_insertAt = singleList_insertAt;
    
    l->singleList_removeHead = singleList_removeHead;
    l->singleList_removeTail = singleList_removeTail;
    l->singleList_removeAt = singleList_removeAt;
    l->singleList_removeNode = singleList_removeNode;
    
    l->singleList_clear = singleList_clear;
    l->singleList_print = singleList_print;

}

int main(int argc, char* argv[]){
    LinkList *l = singleList_create(0);
    
    set_handle(l);
    
    LinkNode *n1 = malloc(sizeof(LinkNode));
    n1->data = 10;
    l->singleList_insertTail(l, n1);
    
    LinkNode *n2 = malloc(sizeof(LinkNode));
    l->singleList_insertTail(l, n2);
    n2->data = 20;
    
    LinkNode *n3 = malloc(sizeof(LinkNode));
    l->singleList_insertAt(l, 2, n3);
    n3->data = 30;
    
    l->singleList_print(l);
    
    return 0;
}
