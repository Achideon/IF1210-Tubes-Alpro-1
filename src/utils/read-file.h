/* SYSTEM PEMBACAAN FILE */
/* Berisi definisi dan primitif pemrosesan pembacaan file secara sekuensial */
/* Setelah dibaca, file akan menyimpan value ke database sederhana (berupa list dari struct) */

#ifndef READFILE_H
#define READFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "boolean.h"
#include "../adt/obat-penyakit.h"
#include "../adt/inventory-list.h"
#include "../adt/user-list.h"
#include "../adt/matrix-denah.h"
#include "../adt/queue.h"
// #include "matrix-denah.h"
// #include "queue.h"

#define MAX_LINE_LENGTH 2048

#define MAX_NAME 200
#define MARK_USED 0
#define MAX_USERNAME_LENGTH 40
#define MAX_PASSWORD_LENGTH 40

// Buat skema pembacaan .txt dan .CSV, value akan disimpan dan diubah 
// menjadi ListUser berdasarkan definisi di file "user-list.h"

/* ********** OPERASI PEMBACAAN FILE ********** */

void readFileUser(ListUser *l);
// Memindahkan data dari File User ke databaseUser sementara

void readFilePenyakit(ListPenyakit *l, char path);
// Memindahkan data dari File Penyakit ke databasePenyakit sementara

void readFileObat(ListObat *l);
// Memindahkan data dari File Obat ke databaseObat sementara

void readFileObatPenyakit(ListObatPenyakit *l);
// Memindahkan data dari File Obat-Penyakit ke databaseObatPenyakit sementara

void readConfig(Matrix *M, char path, ListInventory *Li);
// Memindahkan data dari File Config ke databaseMatriks

/* ********** OPERASI PENDUKUNG PEMBACAAN FILE ********** */

void parsing(char *input, char *format, int dataCount, ...);
// Untuk melakukan parsing tiap pembacaan line CSV

void readDigits(FILE *input, int *number, int *chr);
// Untuk melakukan parsing terhadap tiap digit pada txt

#endif