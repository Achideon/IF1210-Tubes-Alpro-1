#ifndef STACK_H
#define STACK_H

#define CAPACITY 100  
#define IDX_UNDEF -1  

#include <stdio.h>
#include "../utils/boolean.h"

typedef int ElType;   // Tipe data elemen stack

typedef struct {
    ElType contents[CAPACITY];  
    int idxTop;               // Indeks elemen teratas
} Stack;

void CreateStack(Stack *s);
/* Membuat stack kosong
 * I.S.: Sembarang
 * F.S.: Stack s terdefinisi dengan idxTop = IDX_UNDEF */

ElType top(Stack s);
/* Mengembalikan elemen teratas stack tanpa menghapus
 * Pre-kondisi: Stack tidak kosong
 * Return: Nilai elemen teratas stack */

int length(Stack s);
/* Mengembalikan jumlah elemen dalam stack
 * Return: Panjang stack saat ini */

boolean isStackEmpty(Stack s);
/* Mengecek apakah stack kosong
 * Return: true jika kosong (idxTop == IDX_UNDEF) */

boolean isStackFull(Stack s);
/* Mengecek apakah stack penuh
 * Return: true jika penuh (idxTop == CAPACITY-1) */

void push(Stack *s, ElType val);
/* Menambahkan elemen ke atas stack
 * I.S.: Stack boleh kosong, tidak penuh
 * F.S.: val menjadi elemen teratas, idxTop bertambah 1 */

void pop(Stack *s, ElType *val);
/* Mengambil elemen teratas stack
 * I.S.: Stack tidak kosong
 * F.S.: val berisi nilai elemen teratas, idxTop berkurang 1 */

#endif