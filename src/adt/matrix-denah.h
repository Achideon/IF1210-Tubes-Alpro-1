/*
{ Definisi ABSTRACT DATA TYPE MATRIKS }
{ ********** HUBUNGAN DENGAN ADT LAIN ********** }
{ Tidak ada }
{ Alokasi elemen matriks selalu dilakukan sekaligus }
{ ********** Definisi TYPE MATRIKS dengan indeks integer ********** }
{ Ukuran minimum dan maksimum baris dan kolom }
type indeks : integer { indeks baris, kolom }
*/
#ifndef MATRIXDENAH_H
#define MATRIXDENAH_H

#include <stdio.h>
#include "../utils/boolean.h"
#include "queue.h"
#include "user-list.h"

#define MIN_BARIS 1
#define MAX_BARIS 100
#define MIN_KOLOM 1
#define MAX_KOLOM 100
#define MAX_PASIEN 100
#define MARK_INT -1

typedef struct {
    int idDoktor;
    Queue antriPasienDalam;
    Queue antriPasienLuar;
    int kapasitas;
    int kapasitasAntrian;
} Ruangan;

#define MAX_ROWS 100
#define MAX_COLS 100

typedef struct
{
    Ruangan data[MAX_ROWS][MAX_COLS];
    int rows;
    int cols;
} Matrix;

/* Konstruktor */
void createRuangan(Ruangan *R, int capacityDalam, int capacityLuar);

void createMatrix(int rows, int cols, Matrix *M, int capacityDalam, int capacityLuar);
/* I.S. rows dan cols terdefinisi dan valid (1 <= rows,cols <= MAX) */
/* F.S. Terbentuk matrix M dengan ukuran rows x cols */
/* Semua elemen diinisialisasi dengan 0.0 */

Ruangan *getElement(Matrix *M, int row, int col);
/* Mengembalikan pointer ke elemen matrix M pada baris row dan kolom col */
/* Mengembalikan NULL jika row atau col tidak valid untuk matrix M */

/* Mutator */
boolean setElement(Matrix *M, int row, int col, Ruangan value);
/* I.S. M terdefinisi */
/* F.S. Jika row dan col valid, elemen M pada baris row dan kolom col bernilai value, mengembalikan true */
/*      Jika row atau col tidak valid, mengembalikan false */

boolean isRoomValid (Matrix M, char* ruangan);

boolean isDoctorAssigned (Matrix M, int id);

char* getRoomByDoctor (Matrix M, int id);

boolean isRoomAssigned (Matrix M, char* ruangan);

char* getDoctorByRoom (Matrix M,char* ruangan, ListUser L);

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

#endif