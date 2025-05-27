/* SYSTEM MAP OBAT-PENYAKIT */
/* Berisi definisi dan primitif pemrosesan list dinamis */
/* Penempatan elemen selalu rapat kiri dan secara implisit */

#ifndef MAP_OBATPENYAKIT_H
#define MAP_OBATPENYAKIT_H

#include <stdio.h>
#include <string.h>
#include "../utils/boolean.h"
#include "../adt/obat-penyakit.h"
#include <stdlib.h>

/*  Kamus Umum */
#define MAX_NAME 200
#define MAX_MAP 500
/* Kapasitas penyimpanan */
#define IDX_MIN 0
/* Indeks minimum list */
#define IDX_UNDEF -1
/* Indeks tak terdefinisi*/
#define MARK_INT -1
#define MARK_F -1.0
#define MARK_STR "KOSONG"

typedef struct {
    int contents[20];
    int nEff;
} ListValue;

typedef struct {
    int keyPenyakit;
    ListValue valueListID;
    char valueListName[20][MAX_NAME];
} MapEntryOP;

typedef struct {
    MapEntryOP contents[MAX_MAP];
    int length;
} MapObatPenyakit;

/* ********** OPERASI DASAR MAP OBATPENYAKIT ********** */
void createMapObatPenyakit (ListObat l1, ListObatPenyakit l2, MapObatPenyakit *m);
// Prosedur membuat Map diolah dengan ListObat dan List ObatPenyakit

ListValue mapGetListObatID (MapObatPenyakit *m, int keyPenyakit);
// Fungsi mencari value list id obat dari suatu key

char (* mapGetListObatName(MapObatPenyakit *m, int keyPenyakit))[MAX_NAME];
// Fungsi mencari pointer untuk list nama obat dari suatu key

char * mapObatNameByID(MapObatPenyakit *m, int keyPenyakit, int obatID);
// Fungsi yang mencari nama obat berdasarkan letak id 

char * mapObatNameByUrutan(MapObatPenyakit *m, int keyPenyakit, int urutan);
// Mencari nama berdasarkan urutan dan id penyakit

/* ***** OPERASI TAMBAHAN ***** */
char * getNameByObatID (ListObat *l, int obatID);
// Fungsi yang mencari nama dari suatu ID Obat

int getPenyakitIDByName (ListPenyakit *l, char * name);
// Mencari ID dengan Nama Penyakit

#endif