/*
 * 双向循环链表
 *
 *   - "add (s)" 注释是相对于单链表新增的: singlyLinkedList.c
 *   - "add (d)" 注释是相对于双向链表新增的: doubleLinkedList.c
 *   - "modify" 注释是相对于双向链表修改的: doubleLinkedList.c
 *
 * Double Circular Linked List
 *
 *   - 'add (s)' comment is relative to single linked list: singlyLinkedList.c
 *   - 'add (d)' comment is relative to double linked list: doubleLinkedList.c
 *   - 'modify' comment is relative to double linked list: doubleLinkedList.c
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct DCNode {
    ElemType data;
    struct DCNode* prior;                       // add (s)
    struct DCNode* next;
} DCNode, * DCLinkList;

// ===================================
// utils
// ===================================

DCNode* createEmptyDCNode() {
    DCNode* node = (DCNode*)malloc(sizeof(DCNode));
    if (node == NULL) exit(1);

    node->next = NULL;
    node->prior = NULL;                         // add (s)

    return node;
}

bool isEqual(ElemType e1, ElemType e2) {
    return e1 == e2;
}

DCNode* getDCNode(DCLinkList L, int i) {
    if (i < 0) return NULL;

    DCNode* node = L;
    int j = 0;

    while (node && j < i) {                    // 可能 “溢出”
        node = node->next;
        j++;
    }

    return node;                               // NULL or LNode
}

void printList(DCLinkList L) {
    if (L == NULL) {
        printf("NULL\n");
        return;
    }

    DCNode* node = L->next;
    while (node != L) {                         // modify
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

// ===================================
// ===================================

bool initList(DCLinkList* L) {
    *L = createEmptyDCNode();

    (*L)->prior = *L;                           // add (d)
    (*L)->next = *L;                            // add (d)

    return true;
}

bool isEmpty(DCLinkList L) {
    return L->next == L;                        // modify
}

int listLength(DCLinkList L) {
    int length = 0;

    DCNode* node = L;
    while (node->next != L) {                   // modify
        node = node->next;
        length++;
    }

    return length;
}

bool getElem(DCLinkList L, int i, ElemType* e) {
    if (i < 1) return false;

    DCNode* node = getDCNode(L, i);
    if (node == NULL) return false;

    *e = node->data;

    return true;
}

bool listInsert(DCLinkList L, int i, ElemType e) {
    DCNode* preNode = getDCNode(L, i - 1);
    if (preNode == NULL) return false;

    // new node
    DCNode* newNode = createEmptyDCNode();
    newNode->data = e;
    newNode->next = preNode->next;
    newNode->prior = preNode;                   // add (s)

    // next
    newNode->next->prior = newNode;             // modify


    // prior
    preNode->next = newNode;

    return true;
}

bool listInsertPrior(DCNode* node, ElemType e) {
    if (node == NULL) return false;

    // next
    DCNode* copyNode = createEmptyDCNode();
    copyNode->data = node->data;
    copyNode->next = node->next;
    copyNode->prior = node;                     // add (s)

    // new node
    node->data = e;
    node->prior = node->prior;                  // add (s)
    node->next = copyNode;

    return true;
}

bool listInsertNext(DCNode* node, ElemType e) {
    // new node
    DCNode* newLNode = createEmptyDCNode();
    newLNode->data = e;
    newLNode->next = node->next;
    newLNode->prior = node;                     // add (s)

    // next
    if (node->next != NULL) {
        node->next->prior = newLNode;           // add (s)
    }

    // prior
    node->next = newLNode;

    return true;
}

bool listDelete(DCLinkList L, int i, ElemType* e) {
    DCNode* preLNode = getDCNode(L, i - 1);
    if (preLNode == NULL) return false;

    DCNode* delLNode = preLNode->next;
    *e = delLNode->data;

    // prior
    preLNode->next = delLNode->next;

    // next
    delLNode->next->prior = preLNode;           // add (s)

    free(delLNode);
    delLNode = NULL;

    return true;
}

int locateElem(DCLinkList L, ElemType e) {
    DCNode* node = L->next;
    int i = 1;

    bool complete = false;
    while (node && !isEqual(node->data, e)) {
        node = node->next;
        i++;

        if (node == L) {
            complete = true;
            break;
        }
    }

    return complete ? 0 : i;
}

int main() {
    DCLinkList L;

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