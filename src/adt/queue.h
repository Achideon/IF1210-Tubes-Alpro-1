#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include "linked-list.h"
#include "../utils/boolean.h"
#include "user-list.h"

#define IDX_UNDEF -1

typedef int Qtype;
typedef struct
{
    Address head;
    Address tail;
} Queue;

#define HEAD(Q) (Q)->head
#define TAIL(Q) (Q)->tail

void createQueue(Queue *Q);
/*I.S. Q sembarang dengan capacity>0*/
/*F.S. Q akan diisi mark dengan kapasitas (capacity)*/

int queueLength (Queue Q);
/*Mengembalikan Panjang dari antrian.*/

boolean isQueueEmpty(Queue Q);
/*Mengembalikan true jika antrian kosong*/

Qtype getQueueContents(Queue Q, int index);
/*Mengembalikan value dari antrian ke-index*/

Qtype getFirst(Queue Q);
/*Mengembalikan value dari antrian ke-1 dan jika kosong, mengembalikan mark*/

Qtype getLast(Queue Q);
/*Mengembalikan value dari antrian terakhir dan jika kosong, mengembalikan mark*/

void nextQueue(Queue *Q, int *id);
/*I.S. Q terdefinisi*/
/*F.S. Q pada antrian ke-1 dihapus dan antrian selanjutnya jika ada dimajukan satu.*/

void addQueue (Queue *Q, int id);
/*I.S. Q terdefinisi*/
/*F.S. Sebuah id akan ditambahkan pada antrian terakhir jika tersedia.*/

void viewQueue (Queue Q);
/*Menampilkan isi dari Queue.*/
#endif