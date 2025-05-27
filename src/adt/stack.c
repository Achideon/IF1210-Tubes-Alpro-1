#include "stack.h"

/* ********** OPERASI DASAR STACK ********** */

void CreateStackPerut(StackPerut *s) {
    s->top = IDX_UNDEF;
}

boolean isStackPerutEmpty(StackPerut s) {
    return (s.top == IDX_UNDEF);
}

boolean isStackPerutFull(StackPerut s) {
    return (s.top == STACK_CAPACITY - 1);
}

void pushObat(StackPerut *s, int obatID) {
    if (isStackPerutFull(*s)) {
        printf("Stack perut penuh! Tidak bisa menambah obat lagi.\n");
        return;
    }
    s->top++;
    s->contents[s->top] = obatID;
}

void popObat(StackPerut *s, int *obatID) {
    if (isStackPerutEmpty(*s)) {
        printf("Stack perut kosong! Tidak ada obat untuk dikeluarkan.\n");
        *obatID = IDX_UNDEF;
        return;
    }
    *obatID = s->contents[s->top];
    s->top--;
}
