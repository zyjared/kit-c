/*
 * 单向链表

 * 此处首个节点仅存储下一个节点的地址，不存储数据，即固定头结点。
 *
 *
 * Singly Linked List
 *
 * The first node stores the address of the next node, not the data.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct Node {
    ElemType data;
    struct Node* next;
} Node, * LinkList;

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// utils
//
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

LinkList createEmptyLinkList() {
    LinkList node = (LinkList)malloc(sizeof(Node));
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
LinkList getLinkList(LinkList L, int i) {
    if (i < 0) return NULL;

    Node* node = L;
    int j = 0;

    while (node && j < i) {
        node = node->next;
        j++;
    }

    return node; // NULL or LinkList
}

void printList(LinkList L) {
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

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool initList(LinkList* L) {
    *L = createEmptyLinkList();
    return true;
}

bool isEmpty(LinkList L) {
    return L->next == NULL;
}

int listLength(LinkList L) {
    int length = 0;

    Node* node = L->next;
    while (node) {
        length++;
        node = node->next;
    }

    return length;
}

bool getElem(LinkList L, int i, ElemType* e) {
    if (i < 1) return false;

    Node* node = getLinkList(L, i);
    if (node == NULL) return false;

    *e = node->data;

    return true;
}

bool listInsert(LinkList L, int i, ElemType e) {
    LinkList preLinkList = getLinkList(L, i - 1);
    if (preLinkList == NULL) return false;

    LinkList newLinkList = createEmptyLinkList();
    newLinkList->data = e;
    newLinkList->next = preLinkList->next;

    preLinkList->next = newLinkList;

    return true;
}

bool listInsertPrior(LinkList L, ElemType e) {
    if (L == NULL) return false;

    LinkList copyLinkList = createEmptyLinkList();
    copyLinkList->data = L->data;
    copyLinkList->next = L->next;

    L->data = e;
    L->next = copyLinkList;

    return true;
}

bool listInsertNext(LinkList L, ElemType e) {
    LinkList newLinkList = createEmptyLinkList();
    newLinkList->data = e;
    newLinkList->next = L->next;

    L->next = newLinkList;

    return true;
}

bool listDelete(LinkList L, int i, ElemType* e) {
    LinkList preLinkList = getLinkList(L, i - 1);
    if (preLinkList == NULL) return false;

    LinkList delLinkList = preLinkList->next;
    preLinkList->next = delLinkList->next;
    *e = delLinkList->data;

    free(delLinkList);
    delLinkList = NULL;

    return true;
}

int locateElem(LinkList L, ElemType e) {
    LinkList preLinkList = L;
    int i = 0;

    while (preLinkList->next && !isEqual(preLinkList->next->data, e)) {
        preLinkList = preLinkList->next;
        i++;
    }

    return preLinkList->next == NULL ? 0 : i + 1;
}

int main() {
    LinkList L;

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