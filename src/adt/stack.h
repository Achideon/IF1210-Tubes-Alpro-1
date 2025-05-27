#ifndef STACK_PERUT_H
#define STACK_PERUT_H

#include <stdio.h>
#include <string.h>
#include "../utils/boolean.h"
#include "../adt/obat-penyakit.h"

/* Kamus Umum */
#define STACK_CAPACITY 20
#define IDX_UNDEF -1

/* Definisi Stack */
typedef struct {
    int contents[STACK_CAPACITY];  // Menyimpan ID obat
    int top;                       // Indeks elemen teratas
} StackPerut;

void CreateStackPerut(StackPerut *s);
// I.S. s sembarang
// F.S. Membuat stack s kosong dengan top = IDX_UNDEF

/* Predikat */
boolean isStackPerutEmpty(StackPerut s);
// Mengembalikan true jika stack kosong

boolean isStackPerutFull(StackPerut s);
// Mengembalikan true jika stack penuh

void pushObat(StackPerut *s, int obatID);
// I.S. s terdefinisi, mungkin kosong, tidak penuh
// F.S. obatID menjadi elemen teratas stack

void popObat(StackPerut *s, int *obatID);
// I.S. s terdefinisi, tidak kosong
// F.S. obatID berisi nilai elemen teratas yang dihapus, 
//      elemen teratas stack dihapus


#endif
