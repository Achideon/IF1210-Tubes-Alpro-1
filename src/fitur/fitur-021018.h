#ifndef fitur_H
#define fitur_H

#include<stdio.h>
#include<string.h>
#include "../utils/boolean.h"
#include "../utils/write-file.h"
#include "../utils/save.h"
#include "../adt/user-list.h"
#include "../adt/matrix-denah.h"

void regist(ListUser *l, int currentId);
/*F02 : Prosedur untuk melakukan registrasi bagi pasien yang belum memiliki akun. Hanya bisa dijalankan jika belum login dan username bersifat case-insensitive.*/

void addDoctor(ListUser *l, int currentId);
/*F10 : Prosedur yang hanya bisa dijalankan oleh Manager dan berfungsi untuk menambah dokter.*/

void assignDoctor(ListUser *l, int currentId, Matrix *M);
/*F10 : Prosedur untuk assign dokter ke ruangan.*/

void ext(boolean *kondisi, ListUser l, Matrix m, ListInventory Li, ListPerut Lp);
/*F18 : Prosedur untuk menghentikan program yang sedang berlangsung. Kemudian, akan ada opsi untuk dipilih antara save semua progress yang ada atau tidak save.*/

void printAddUser();

#endif