/*
 * 双向循环链表
 *
 * 和 doubleLinkedList 的区别在于，尾节点的 next 指向头节点
 *
 * Double Circular Linked List
 *
 * The difference is the same as doubly linked list, only that the tail node's next pointer points to the head node.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct DCLNode {
    ElemType data;
    struct DCLNode* next;
    struct DCLNode* prior;
} DCLNode, * DCLinkList;


bool initDCList(DCLinkList* L) {
    *L = (DCLNode*)malloc(sizeof(DCLNode));
    if (*L == NULL) exit(1);

    // 头尾指针指向自己 - head and tail point to itself
    (*L)->next = *L;
    (*L)->prior = *L;

    return true;
}

bool isTail(DCLinkList L, DCLNode* node) {
    /*
     * 利用该函数判断尾节点，并进行相关操作
     *
     * Use this function to judge the tail node and perform related operations
     */
    return node->next == L;
}

bool insNext(DCLNode* p, DCLNode* s) {
    if (p == NULL || s == NULL) return false;

    // s 节点本身           - s node itself
    s->next = p->next;
    s->prior = p;

    // s 节点的下一个节点   - s node's next node
    p->next->prior = s;

    // s 节点的上一个节点   - s node's prior node
    p->next = s;

    return true;
}