#include "stack.h"

void CreateStack(Stack *s)
/* Membuat stack 
 * I.S.: s sembarang
 * F.S.: s menjadi stack kosong dengan idxTop = IDX_UNDEF */
{
    s->idxTop = IDX_UNDEF;
}

ElType top(Stack s)
/* Mengembalikan elemen teratas tanpa menghapus
 * Pra-kondisi: stack tidak kosong */
{
    return s.contents[s.idxTop];
}

int length(Stack s)
/* Mengembalikan jumlah elemen dalam stack */
{
    return s.idxTop + 1;
}

boolean isStackEmpty(Stack s)
/* Mengecek apakah stack masih empty */
{
    return (s.idxTop == IDX_UNDEF);
}

boolean isStackFull(Stack s)
/* Mengecek apakah stack sudah full */
{
    return (s.idxTop == CAPACITY - 1);
}

void push(Stack *s, ElType val)
/* Menambahkan elemen 
 * I.S.: s mungkin kosong, tidak penuh
 * F.S.: val menjadi TOP baru, TOP bertambah 1 */
{
    if (isStackFull(*s)) return;
    if (isStackEmpty(*s)) {
        s->idxTop = 0;
    } else {
        s->idxTop++;
    }
    s->contents[s->idxTop] = val;
}

void pop(Stack *s, ElType *val)
/* Menghapus elemen 
 * I.S.: s tidak kosong
 * F.S.: val berisi nilai TOP lama, TOP berkurang 1 */
{
    if (isStackEmpty(*s)) {
        return;
    }

    *val = s->contents[s->idxTop];
    
    if (s->idxTop == 0) {
        s->idxTop = IDX_UNDEF;
    } else {
        s->idxTop--;
    }
}

