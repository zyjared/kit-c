/*
 * 检查括号匹配是否合法
 *
 * check if brackets are matched
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.c"

const char leftBracket[3] = { '(', '[', '{' };
const char rightBracket[3] = { ')', ']', '}' };

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// utils
//
// 字符换为数字，只是为了配合 stack.h 中的 ElemType
//
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

int bracketIndex(char bracket) {
    for (int i = 0; i < 3; i++) {
        if (bracket == leftBracket[i])
            return i;
    }
    return -1;
}

int inRightBracket(char bracket) {
    for (int i = 0; i < 3; i++) {
        if (bracket == rightBracket[i])
            return true;
    }
    return false;
}

bool bracketMatch(char left, char right) {
    switch (bracketIndex(left)) {
    case 0:
        return right == rightBracket[0];
    case 1:
        return right == rightBracket[1];
    case 2:
        return right == rightBracket[2];
    }
}

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool bracketCheck(char* str) {
    SqStack S;
    initStack(&S);

    for (int i = 0; str[i] != '\0'; i++) {
        int index = bracketIndex(str[i]);
        if (index != -1) {
            push(&S, index);
        }
        else if (inRightBracket(str[i])) {
            if (isEmpty(S))
                return false;

            int popIndex;
            pop(&S, &popIndex);
            if (!bracketMatch(leftBracket[popIndex], str[i]))
                return false;
        }
        else {
            // continue
        }
    }

    return isEmpty(S);
}

int main() {
    char* str[] = { "({})", "({[()]}[])", "({[abcdef(abcdef)]}[abcdef])", "({[()]", "()]}" };
    for (int i = 0; i < sizeof(str) / sizeof(char*); i++) {
        printf("\n%s\n", str[i]);
        if (bracketCheck(str[i]))
            printf("    -> true\n");
        else
            printf("    -> false\n");
    }

    return 0;
}