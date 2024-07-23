#ifndef QUEUE_H
#define QUEUE_H

typedef int ElemType;

typedef struct Node {
    ElemType data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} LinkQueue;

typedef enum {
    ERROR,
    OK
} Status;

void printQueue(LinkQueue Q);

Status initQueue(LinkQueue* Q);

Status destroyQueue(LinkQueue* Q);

Status enQueue(LinkQueue* Q, ElemType e);

Status deQueue(LinkQueue* Q, ElemType* e);

#endif