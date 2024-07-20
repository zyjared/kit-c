/*
 * 双向链表
 *
 * 基本和 singlyLinkedList 一致，只是增加了前后指针。
 * 操作一个节点的时候，需要考虑修改其前后节点的情况。
 *
 * Double Linked List
 *
 * The basic is the same as singlyLinkedList, only that the next and prior pointers are added.
 * When you want to operate a node, you need to consider the modification of its next and prior nodes.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct DNode {
    ElemType data;
    struct DNode* prior;
    struct DNode* next;
} DNode, * DLinkList;

// ----------------------------------
// utils
// ----------------------------------

DNode* createEmptyDNode() {
    DNode* p = (DNode*)malloc(sizeof(DNode)); // 注意释放 - don't forget to use free()
    if (p == NULL) exit(1);
    p->prior = NULL;
    p->next = NULL;

    return p;
}

void printList(DLinkList L) {
    if (L == NULL) {
        printf("NULL\n");
        return;
    }
    DNode* node = L->next;
    while (node) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

// ----------------------------------
// ----------------------------------

bool initDList(DLinkList* L) {
    *L = createEmptyDNode();
    return true;
}

bool isEmpty(DLinkList L) {
    return L->next == NULL;
}

bool insNext(DNode* p, DNode* s) {
    if (p == NULL || s == NULL) return false;

    // s 节点本身           - s node itself
    s->next = p->next;
    s->prior = p;

    // s 节点的下一个节点   - s node's next node
    if (p->next != NULL)
        p->next->prior = s;

    // s 节点的上一个节点   - s node's prior node
    p->next = s;

    return true;
}

int main() {
    DLinkList L;

    initDList(&L);

    DNode* node = createEmptyDNode();

    // ------------insert------------

    node->data = 1;
    insNext(L, node);
    printf("insNext:    %d\n", L->next->data);

    int testData[4] = { 2, 3, 4, 5 };
    for (int i = 0; i < sizeof(testData) / sizeof(int); i++) {
        node = createEmptyDNode();
        node->data = testData[i];
        insNext(L, node);
    }

    printf("            ");
    printList(L);

    return 0;
}