/*
 * 单向链表
 * 此处首个节点仅存储下一个节点的地址，不存储数据，即固定头结点。
 * 另外，注意函数参数是双指针的情况。
 *
 *
 * Singly Linked List
 * The first node stores the address of the next node, not the data.
 * Note that the function parameter is a double pointer.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct Node {
    ElemType data;
    struct Node* next;
} Node, * LNode;

// ===================================
// utils
// ===================================

LNode createLNode() {
    LNode node = (LNode)malloc(sizeof(Node));
    if (node == NULL) exit(1);

    node->next = NULL;

    return node;
}

bool isEqual(ElemType e1, ElemType e2) {
    return e1 == e2;
}

/**
 * 获得第 i 个节点，允许获得头结点
 *
 * Get the i-th node, allowing the head node
 */
LNode getLNode(LNode L, int i) {
    if (i < 0) return NULL;

    Node* node = L;
    int j = 0;

    while (node && j < i) {
        node = node->next;
        j++;
    }

    return node; // NULL or LNode
}

void printList(LNode L) {
    if (L == NULL) {
        printf("NULL\n");
        return;
    }
    Node* node = L->next;
    while (node) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

// ===================================
// ===================================

bool initList(LNode* L) {
    *L = createLNode();
    return true;
}

bool isEmpty(LNode L) {
    return L->next == NULL;
}

int listLength(LNode L) {
    int length = 0;

    Node* node = L->next;
    while (node) {
        length++;
        node = node->next;
    }

    return length;
}

bool getElem(LNode L, int i, ElemType* e) {
    if (i < 1) return false;

    Node* node = getLNode(L, i);
    if (node == NULL) return false;

    *e = node->data;

    return true;
}

bool listInsert(LNode L, int i, ElemType e) {
    LNode preLNode = getLNode(L, i - 1);
    if (preLNode == NULL) return false;

    LNode newLNode = createLNode();
    newLNode->data = e;
    newLNode->next = preLNode->next;

    preLNode->next = newLNode;

    return true;
}

bool listInsertPrior(LNode L, ElemType e) {
    if (L == NULL) return false;

    LNode copyLNode = createLNode();
    copyLNode->data = L->data;
    copyLNode->next = L->next;

    L->data = e;
    L->next = copyLNode;

    return true;
}

bool listInsertNext(LNode L, ElemType e) {
    LNode newLNode = createLNode();
    newLNode->data = e;
    newLNode->next = L->next;

    L->next = newLNode;

    return true;
}

bool listDelete(LNode L, int i, ElemType* e) {
    LNode preLNode = getLNode(L, i - 1);
    if (preLNode == NULL) return false;

    LNode delLNode = preLNode->next;
    preLNode->next = delLNode->next;
    *e = delLNode->data;

    free(delLNode);
    delLNode = NULL;

    return true;
}

int locateElem(LNode L, ElemType e) {
    LNode preLNode = L;
    int i = 0;

    while (preLNode->next && !isEqual(preLNode->next->data, e)) {
        preLNode = preLNode->next;
        i++;
    }

    return preLNode->next == NULL ? 0 : i + 1;
}

int main() {
    LNode L;

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