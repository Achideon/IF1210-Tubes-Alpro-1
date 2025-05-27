/* SYSTEM LIST DINAMIS OBATPENYAKIT */
/* Berisi definisi dan primitif pemrosesan list dinamis */
/* Penempatan elemen selalu rapat kiri dan secara implisit */

#ifndef OBATPENYAKIT_H
#define OBATPENYAKIT_H

#include <stdio.h>
#include <string.h>
#include "../utils/boolean.h"
#include <stdlib.h>

/*  Kamus Umum */
#define MAX_NAME 200
#define MAX_OBAT 350
#define MAX_PENYAKIT 350
#define MAX_OBATPENYAKIT 350
/* Kapasitas penyimpanan */
#define IDX_MIN 0
/* Indeks minimum list */
#define IDX_UNDEF -1
/* Indeks tak terdefinisi*/
#define MARK_INT -1
#define MARK_F -1.0
#define MARK_STR "KOSONG"

/* Definisi Type Struct */
/* Definisi Elemen List */
typedef struct {
    int obatID;
    char namaObat[MAX_NAME];
} Obat;

typedef struct {
    int id;
    char namaPenyakit[MAX_NAME];
    float suhuTubuhMin;
    float suhuTubuhMax;
    int tekananSistolikMin;
    int tekananSistolikMax;
    int tekananDiastolikMin;
    int tekananDiastolikMax;
    int detakJantungMin;
    int detakJantungMax;
    float saturasiOksigenMin;
    float saturasiOksigenMax;
    int kadarGulaDarahMin;
    int kadarGulaDarahMax;
    float beratBadanMin;
    float beratBadanMax;
    int tinggiBadanMin;
    int tinggiBadanMax;
    int kadarKolesterolMin;
    int kadarKolesterolMax;
    int trombositMin;
    int trombositMax;
} Penyakit;

typedef struct {
    int obatID;
    int penyakitID;
    int urutanMinum;
} ObatPenyakit;

/* Definisi List */
typedef struct{
    Obat contents[MAX_OBAT]; /* Memori tempat penyimpan elemen (container) */
    int nEff; /* Nilai efektif dari suatu list */
} ListObat;

typedef struct{
    Penyakit contents[MAX_PENYAKIT]; /* Memori tempat penyimpan elemen (container) */
    int nEff; /* Nilai efektif dari suatu list */
} ListPenyakit;

typedef struct{
    ObatPenyakit contents[MAX_OBATPENYAKIT]; /* Memori tempat penyimpan elemen (container) */
    int nEff; /* Nilai efektif dari suatu list */
} ListObatPenyakit;

/* ********** OPERASI DASAR LIST PENGGUNA ********** */

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : Create List kosong  */
void createListObat(ListObat *l);
// I.S. l tidak terdefinisi
// F.S. Menghasilkan l sebagai list pengguna

void createListPenyakit(ListPenyakit *l);
// I.S. l tidak terdefinisi
// F.S. Menghasilkan l sebagai list pengguna

void createListObatPenyakit(ListObatPenyakit *l);
// I.S. l tidak terdefinisi
// F.S. Menghasilkan l sebagai list pengguna

/* ********** SELEKTOR ********** */

boolean isListObatEmpty(ListObat l);
// Mengecek apakah list kosong

boolean isListObatFull(ListObat l);
// Mengecek apakah list penuh

boolean isListPenyakitEmpty(ListPenyakit l);
// Mengecek apakah list kosong

boolean isListPenyakitFull(ListPenyakit l);
// Mengecek apakah list penuh

boolean isListObatPenyakitEmpty(ListObatPenyakit l);
// Mengecek apakah list kosong

boolean isListObatPenyakitFull(ListObatPenyakit l);
// Mengecek apakah list penuh

#endif