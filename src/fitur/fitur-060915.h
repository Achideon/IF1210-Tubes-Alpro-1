#ifndef fitur3_H
#define fitur3_H

#include<stdio.h>
#include<string.h>
#include "../utils/boolean.h"
#include "../adt/user-list.h"
#include "../adt/matrix-denah.h"
#include "../utils/write-file.h"

void printDenah(Matrix M);
/* I.S. M terdefinisi */
/* F.S. Seluruh elemen M tertulis ke layar dalam bentuk denah rumah sakit */
/*
Format Denah:
      1     2     3     4
   +-----+-----+-----+-----+
 A | A1  | A2  | A3  | A4  |
   +-----+-----+-----+-----+
 B | B1  | B2  | B3  | B4  |
   +-----+-----+-----+-----+
 C | C1  | C2  | C3  | C4  |
   +-----+-----+-----+-----+
 D | D1  | D2  | D3  | D4  |
   +-----+-----+-----+-----+
*/

void printRuangan(Matrix M, char * ruangan, ListUser dataUser);
/* I.S. M dan ruangan terdefinisi */
/* F.S. Mencetak data kapasitas, dokter, dan pasien ke layar */

void printSemuaAntrian(Matrix M, ListUser dataUser, int currentID);
/* I.S. M dan ruangan terdefinisi */
/* F.S. Mencetak semua data kapasitas, dokter, dan pasien ke layar */

void antrianSaya(Matrix M, ListUser dataUser, int userID);

#endif