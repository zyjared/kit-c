/*
 * 双向链表
 *
 *   - "add" 注释是相对于单向链表的: singlyLinkedList.c
 *
 * Double Linked List
 *
 *   - 'add' comment is relative to singly linked list: singlyLinkedList.c
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct DNode {
    ElemType data;
    struct DNode* prior;                        // add
    struct DNode* next;
} DNode, * DLinkList;

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// utils
//
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

DNode* createEmptyDNode() {
    DNode* node = (DNode*)malloc(sizeof(DNode));
    if (node == NULL) exit(1);

    node->next = NULL;
    node->prior = NULL;                         // add

    return node;
}

bool isEqual(ElemType e1, ElemType e2) {
    return e1 == e2;
}

DNode* getDNode(DLinkList L, int i) {
    if (i < 0) return NULL;

    DNode* node = L;
    int j = 0;

    while (node && j < i) {
        node = node->next;
        j++;
    }

    return node;                                 // NULL or LNode
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

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool initList(DLinkList* L) {
    *L = createEmptyDNode();
    return true;
}

bool isEmpty(DLinkList L) {
    return L->next == NULL;
}

int listLength(DLinkList L) {
    int length = 0;

    DNode* node = L->next;
    while (node) {
        node = node->next;
        length++;
    }

    return length;
}

bool getElem(DLinkList L, int i, ElemType* e) {
    if (i < 1) return false;

    DNode* node = getDNode(L, i);
    if (node == NULL) return false;

    *e = node->data;

    return true;
}

bool listInsert(DLinkList L, int i, ElemType e) {
    DNode* preNode = getDNode(L, i - 1);
    if (preNode == NULL) return false;

    // new node
    DNode* newNode = createEmptyDNode();
    newNode->data = e;
    newNode->next = preNode->next;
    newNode->prior = preNode;                   // add

    // next
    if (newNode->next != NULL) {
        newNode->next->prior = newNode;         // add
    }

    // prior
    preNode->next = newNode;

    return true;
}

bool listInsertPrior(DNode* node, ElemType e) {
    if (node == NULL) return false;

    // next
    DNode* copyNode = createEmptyDNode();
    copyNode->data = node->data;
    copyNode->next = node->next;
    copyNode->prior = node;                     // add

    // new node
    node->data = e;
    node->prior = node->prior;                  // add
    node->next = copyNode;

    return true;
}

bool listInsertNext(DNode* node, ElemType e) {
    // new node
    DNode* newLNode = createEmptyDNode();
    newLNode->data = e;
    newLNode->next = node->next;
    newLNode->prior = node;                     // add

    // next
    if (node->next != NULL) {
        node->next->prior = newLNode;           // add
    }

    // prior
    node->next = newLNode;

    return true;
}

bool listDelete(DLinkList L, int i, ElemType* e) {
    DNode* preLNode = getDNode(L, i - 1);
    if (preLNode == NULL) return false;

    DNode* delLNode = preLNode->next;
    *e = delLNode->data;

    // prior
    preLNode->next = delLNode->next;

    // next
    if (delLNode->next != NULL) {
        delLNode->next->prior = preLNode;       // add
    }

    free(delLNode);
    delLNode = NULL;

    return true;
}

int locateElem(DLinkList L, ElemType e) {
    DNode* preLNode = L;
    int i = 0;

    while (preLNode->next && !isEqual(preLNode->next->data, e)) {
        preLNode = preLNode->next;
        i++;
    }

    return preLNode->next == NULL ? 0 : i + 1;
}

int main() {
    DLinkList L;

    // ================= init ===============

    initList(&L);
    printf("initList:                %3d\n", L == NULL);

    // ================ insert ==============

    listInsert(L, 1, 6);
    printf("listInsert:               ");
    printList(L);

    // =============== insert next ==========

    ElemType testData[4] = { 5, 4, 3, 1 };
    for (int i = 0; i < sizeof(testData) / sizeof(ElemType); i++) {
        listInsertNext(L, testData[i]);
    }
    printf("listInsertNext:           ");
    printList(L);

    // ============ insert prior =============

    listInsertPrior(L->next->next, 2);
    printf("listInsertPrior:          ");
    printList(L);

    // =============== isEmpty ==============

    printf("isEmpty:                %3d\n", isEmpty(L));

    // ================= length =============

    printf("listLength:             %3d\n", listLength(L));

    // ================= get ================

    ElemType getE;
    getElem(L, 3, &getE);
    printf("getElem:                %3d\n", getE);

    // ================= delete =============

    ElemType delE;
    listDelete(L, 3, &delE);
    printf("listDelete:             %3d -> ", delE);
    printList(L);

    // ================= locate =============

    printf("locateElem:             %3d\n", locateElem(L, 5));

    return 0;
}