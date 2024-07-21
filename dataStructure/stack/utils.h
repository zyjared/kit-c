#ifndef STACK_UTILS_H

#define STACK_UTILS_H

#define INIT_SIZE 20
#define INCREMENT_SIZE 10

typedef enum {
    ERROR,
    OK
} Status;

typedef int SElemType;

typedef struct {
    SElemType* base;
    SElemType* top;
    int stackSize;
} SqStack;

#endif
