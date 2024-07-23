#ifndef STACK_H
#define STACK_H

#define INIT_SIZE 20
#define INCREMENT_SIZE 10

typedef enum {
    ERROR,
    OK
} Status;

typedef int ElemType;

typedef struct {
    ElemType* base;
    ElemType* top;
    int stackSize;
} SqStack;

ElemType* createEmptySElem();

void printStack(SqStack S);

Status initStack(SqStack* S);

Status isEmpty(SqStack S);

Status stackLength(SqStack S);

Status getTop(SqStack S, ElemType* e);

Status push(SqStack* S, ElemType e);

Status pop(SqStack* S, ElemType* e);
#endif