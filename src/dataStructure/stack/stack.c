#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// utils
//
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

ElemType* createEmptySElem() {
    ElemType* e = (ElemType*)malloc(sizeof(ElemType));
    if (e == NULL) exit(1);

    return e;
}

void printStack(SqStack S) {
    for (ElemType* p = S.base; p < S.top; p++) {
        printf("%d ", *p);
    }
    printf("\n");
}

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

Status initStack(SqStack* S) {
    S->base = (ElemType*)malloc(INIT_SIZE * sizeof(ElemType));
    if (S->base == NULL) exit(1);

    S->top = S->base;
    S->stackSize = INIT_SIZE;

    return OK;
}

Status stackLength(SqStack S) {
    return S.top - S.base;
}

Status isEmpty(SqStack S) {
    return S.top == S.base;
}

Status getTop(SqStack S, ElemType* e) {
    if (S.top == S.base) return ERROR;          // 栈为空
    *e = *(S.top - 1);                          // 返回栈顶元素
    return OK;
}

Status push(SqStack* S, ElemType e) {
    if (S->top - S->base >= S->stackSize) {
        S->base = (ElemType*)realloc(S->base, (S->stackSize + INCREMENT_SIZE) * sizeof(ElemType));
        if (!S->base) exit(1);

        S->top = S->base + S->stackSize;
        S->stackSize += INCREMENT_SIZE;
    }
    *S->top++ = e;
    return OK;
}

Status pop(SqStack* S, ElemType* e) {
    if (S->top == S->base) return ERROR;
    *e = *--S->top;
    return OK;
}

int test() {

    SqStack S;

    initStack(&S);

    // ------------- push ---------------

    push(&S, 1);
    push(&S, 2);
    push(&S, 3);

    printf("\npush:\n");
    printf("  length               : %d\n", stackLength(S));
    printf("  stack                : ");
    printStack(S);

    // ------------- pop ---------------

    ElemType e;
    pop(&S, &e);

    printf("\npop:\n");
    printf("  elem                 : %d\n", e);
    printf("  length               : %d\n", stackLength(S));
    printf("  stack                : ");
    printStack(S);

    return 0;
}

// int main() {
//     test();
//     return 0;
// }