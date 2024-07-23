/*
 * 顺序表 (Sequenatial List)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INIT_SIZE 5
#define INCREMENT_SIZE 10

typedef struct {
    int id;
    int val;
} ElemType;

typedef struct {
    ElemType* data;
    int maxSize;
    int length;
} SqList;

void initList(SqList* L) {
    L->data = (ElemType*)calloc(INIT_SIZE, sizeof(ElemType));
    L->maxSize = INIT_SIZE;
    L->length = 0;
}

ElemType getElem(SqList L, int i) {
    return L.data[i - 1];
}

bool isEqual(ElemType e1, ElemType e2) {
    return e1.id == e2.id;
}

int locateElem(SqList L, ElemType e) {
    for (int i = 0; i < L.length; i++) {
        if (isEqual(L.data[i], e)) return i + 1;
    }
    return 0;
}

void increaseSize(SqList* L, int len) {
    if (len <= 0) return;
    ElemType* temp = (ElemType*)realloc(L->data, (L->maxSize + len) * sizeof(ElemType));

    if (temp == NULL) {
        printf("realloc error\n");
        return;
    }

    L->data = temp;
    L->maxSize += len;
    memset(L->data + L->maxSize, 0, len * sizeof(ElemType));
}

/**
 * 如果最大容量不够，将自动扩容。
 * If maxSize is not enough, the list will be automatically expanded.
 */
bool listInsert(SqList* L, int i, ElemType e) {
    if (i < 1 || i > L->length + 1) return false;

    if (L->length + 1 > L->maxSize) {
        increaseSize(L, INCREMENT_SIZE);
    }

    for (int j = L->length; j >= i; j--) {
        L->data[j] = L->data[j - 1];
    }

    L->data[i - 1] = e;
    L->length++;

    return true;
}

bool listDelete(SqList* L, int i, ElemType* e) {
    if (i < 1 || i > L->length) return false;

    *e = L->data[i - 1];
    for (int j = i; j < L->length; j++) {
        L->data[j - 1] = L->data[j];
    }

    L->length--;

    return true;
}

int main() {
    SqList L;

    // ============ init ==============

    initList(&L);

    // ============ insert =============

    ElemType testData[6] = { {1, 11}, {2, 22}, {3, 33}, {4, 44}, {5, 55}, {6, 66} };
    for (int i = 0; i < sizeof(testData) / sizeof(ElemType); i++) {
        listInsert(&L, i + 1, testData[i]);
    }

    printf("\nlength: %d\n", L.length);

    // =========== delete =============

    ElemType delE = { 0 };
    listDelete(&L, 2, &delE);

    printf("\ndelete: %d\n", delE.val);

    // =========== get =============

    printf("\ndata: %d(length)\n  ", L.length);
    for (int i = 1; i <= L.length; i++) {
        printf("%d ", getElem(L, i).val);
    }

    // =========== locate =============

    int locate = locateElem(L, testData[5]);
    if (locate == 0) {
        printf("\n\nlocate: not found\n");
    }
    else {
        printf("\n\nlocate: %d\n", locate);
    }

    return 0;
}



