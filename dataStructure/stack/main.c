/*
 * initStack(&S);
 *
 * destroyStack(&S);
 *
 * clearStack(&S);
 *
 * stackEmpty(S);
 *
 * stackLength(S);
 *
 * getTop(S, &e);
 *
 * push(&S, e);
 *
 * pop(&S, &e);
 *
 * stackTraverse(S);
 */

#include <stdio.h>
#include "utils.h"

SElemType* createEmptySElem() {
    SElemType* e = (SElemType*)malloc(sizeof(SElemType));
    if (e == NULL) exit(1);

    return e;
}

Status initStack(SqStack* S) {
    S->base = (SElemType*)malloc(INIT_SIZE * sizeof(SElemType));
    S->top = S->base;
    S->stackSize = INIT_SIZE;

    return OK;
}

Status getTop(SqStack S, SElemType* e) {
    if (S.top == S.base) return ERROR;
}

int main() {
    printf("Hello, World!\n");
}