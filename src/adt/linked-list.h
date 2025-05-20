#include <stdio.h>
#include <stdlib.h>
#include "../utils/boolean.h"
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef int ElType;
typedef struct node* Address;
typedef struct node
{
    ElType info;
    Address next;
}Node;



#define INFO(L) (L)->info
#define NEXT(L) (L)->next

Address newNode(ElType val);
/*Membuat sebuah node baru bernilai val*/

void createLinkedList (Address *L);
/*I.S. Linked list sembarang
F.S. Terbentuk Linked List kosong*/

boolean isLinkedListEmpty (Address L);
/*Menghasilkan true jika L kosong dan false jika tidak kosong*/

int lengthLinkedList (Address L);
/*Menghasilkan banyaknya elemen di Linked List*/

void insertFirst(Address *L, ElType val);
/*I.S. L mungkin kosong
F.S. val ditambahkan sebagai node baru di posisi awal (head)*/

void insertLast(Address *L, ElType val);
/*I.S. L mungkin juga kosong
F.S. val ditambahkan sebagai node baru di posisi akhir (tail)*/





#endif