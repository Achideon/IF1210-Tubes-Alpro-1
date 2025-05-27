/* SYSTEM LIST DINAMIS INVENTORY */
/* Berisi definisi dan primitif pemrosesan list dinamis */
/* Penempatan elemen selalu rapat kiri dan secara implisit */

#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <string.h>
#include "../utils/boolean.h"
#include "../adt/obat-penyakit.h"
#include "../adt/map-obat-penyakit.h"
#include <stdlib.h>

/*  Kamus Umum */
#define MAX_USERS 300
#define MARK_USED 0
/* Kapasitas penyimpanan */
#define IDX_MIN 0
/* Indeks minimum list */
#define IDX_UNDEF -1
/* Indeks tak terdefinisi*/
#define MARK_INT -1
#define MARK_F -1.0
#define MARK_STR "KOSONG"

typedef struct {
    ListValue contents[MAX_USERS];
    int nEff;
} ListInventory;

/* ********** OPERASI DASAR LIST PENGGUNA ********** */

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : Create List kosong  */
void createListInventory(ListInventory *l);
// I.S. l tidak terdefinisi
// F.S. Menghasilkan l sebagai list inventory

/* ********** SELEKTOR ********** */
/* *** Test List kosong *** */
boolean isListInventoryEmpty(ListInventory l);
// Mengecek apakah list kosong

/* *** Test List penuh *** */
boolean isListInventoryFull(ListInventory l);
// Mengecek apakah list penuh

void useInventory(ListInventory *l, int userID, int obatID, int *outObatID);
// Menggunakan obat dengan urutan tertentu

void insertInventory(ListInventory *l, int userID, int obatID);
// Menambahkan obat pada indeks terakhir

int getLastIdxInventory(ListInventory l, int userID);
// Menghasilkan nilai terakhir dari suatu inventory dari user


#endif