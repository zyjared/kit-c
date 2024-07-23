#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// utils
//
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void printQueue(LinkQueue Q) {
    Node* node = Q.front->next;
    while (node) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

Status initQueue(LinkQueue* Q) {
    Q->front = Q->rear = (Node*)malloc(sizeof(Node));
    if (!Q->front) exit(1);

    Q->front->next = NULL;
    return OK;
}

Status destroyQueue(LinkQueue* Q) {
    while (Q->front) {
        Q->rear = Q->front->next;

        free(Q->front);
        Q->front = Q->rear;
    }

    return OK;
}

Status enQueue(LinkQueue* Q, ElemType e) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) exit(1);

    node->data = e;
    node->next = NULL;

    Q->rear->next = node;
    Q->rear = node;

    return OK;
}

Status deQueue(LinkQueue* Q, ElemType* e) {
    if (Q->front == Q->rear) return ERROR;

    Node* node = Q->front->next;                // 此处逻辑和 enQueue 相关

    *e = node->data;

    Q->front->next = node->next;

    if (Q->rear == node) Q->rear = Q->front;

    free(node);

    return OK;
}

int main() {
    LinkQueue Q;

    initQueue(&Q);

    // --------------- enQueue -----------------

    enQueue(&Q, 1);
    enQueue(&Q, 2);
    enQueue(&Q, 3);

    printf("enQueue:\n");
    printf("  queue             : ");
    printQueue(Q);

    // --------------- deQueue -----------------

    ElemType e;
    deQueue(&Q, &e);
    printf("deQueue:\n");
    printf("  elem              : %d\n", e);
    printf("  queue             : ");
    printQueue(Q);

    return 0;
}