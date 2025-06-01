#ifndef FITUR1314_H
#define FITUR1314_H

#include<stdio.h>
#include<string.h>
#include "../utils/boolean.h"
#include "../adt/user-list.h"
#include "../adt/matrix-denah.h"
#include "../utils/write-file.h"
#include "../adt/queue.h"
#include "../adt/inventory-list.h"
#include "../adt/stack.h"
/*
Fitur
F13 : Pulang Dok -> Untuk pasien yang sudah melakukan check-up dan mendapat obat untuk bertanya kepada dokter, apakah sudah selesai atau belom?
F14 : Daftar Check-Up -> Untuk Pasien yang belum mendaftar, pasien bisa melakukan daftar dengan 
memasukkan data dan memilih dokter.
*/
boolean urutanBenar (ListPerut L1, ListPenyakit L2, MapObatPenyakit M, char * penyakit, int currentId);

void pulangDok(ListObat *Lobat,ListPenyakit *Listp,MapObatPenyakit *Map,ListPerut *Perut,ListUser *L, Matrix *M, ListInventory *I, int currentId);
/*F13 : Mengecek apakah pasien sudah diperbolehkan pulang atau belum dengan syarat : */
/*Berada di posisi antrian pertama, sudah meminum semua obat/sembuh, dan tidak ada obat yang salah*/

void checkUp(ListUser *L, Matrix *M, int currentId);
/*F14 : Melakukan pendaftaran pasien ke dokter oleh pasien. Selain itu, ada proses pengisian data check-up.*/
/*Listuser L adalah data akun yang berasal dari user.csv, Matrix M adalah Matrix Denah Rumah Sakit, dan int CurrentId adalah ID akun yang sedang login*/

void printASCIIPulangDok();

#endif