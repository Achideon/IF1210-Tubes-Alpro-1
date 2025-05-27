/* SYSTEM LIST DINAMIS OBATPENYAKIT */
/* Berisi definisi dan primitif pemrosesan list dinamis */
/* Penempatan elemen selalu rapat kiri dan secara implisit */

#include <stdio.h>
#include <string.h>
#include "../utils/boolean.h"
#include "obat-penyakit.h"
#include <stdlib.h>


/* ********** OPERASI DASAR LIST PENGGUNA ********** */

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : Create List kosong  */
void createListObat(ListObat *l)
{
   (*l).nEff = 0;
}

void createListPenyakit(ListPenyakit *l)
{
    (*l).nEff = 0;
}

void createListObatPenyakit(ListObatPenyakit *l)
{
    (*l).nEff = 0;
}

/* ********** SELEKTOR ********** */

boolean isListObatEmpty(ListObat l){
    return ((l).nEff == 0);
}

boolean isListObatFull(ListObat l)
{
    return ((l).nEff == MAX_OBAT);
}

boolean isListPenyakitEmpty(ListPenyakit l)
{
    return ((l).nEff == 0);
}

boolean isListPenyakitFull(ListPenyakit l)
{
    return ((l).nEff == MAX_PENYAKIT);
}

boolean isListObatPenyakitEmpty(ListObatPenyakit l)
{
    return ((l).nEff == 0);
}

boolean isListObatPenyakitFull(ListObatPenyakit l)
{
    return ((l).nEff == MAX_OBATPENYAKIT);
}