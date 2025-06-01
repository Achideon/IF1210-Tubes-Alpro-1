#ifndef fitur2_H
#define fitur2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../adt/user-list.h"

/*
login
    - Meminta username dan password
    - Mengecek apakah username dan password valid
    - Jika valid, set currentID ke ID user yang login
    - Jika tidak valid, tampilkan pesan error
logout
    - Mengubah currentID menjadi MARK_INT
lupaPassword
    - Meminta username dan kode unik
    - Mengecek apakah username valid
    - Jika valid, lakukan RLE pada username
    - Jika kode unik sesuai dengan hasil RLE, minta password baru
    - Set password baru untuk user yang bersangkutan
    - Tampilkan pesan sukses
menuHelp
    - Menampilkan menu bantuan sesuai dengan role yang sedang login
    - Jika belum login, tampilkan menu login dan register
    - Jika sudah login, tampilkan menu sesuai dengan role
    - Tampilkan footnote tentang cara menggunakan aplikasi
*/

void login(ListUser *l, int *currentID);

void logout(ListUser *l, int *currentID);

void lupaPassword(ListUser *l, int *currentID);

void menuHelp(ListUser *l, int *currentID);

void printLogin();

void printLogout();

#endif
