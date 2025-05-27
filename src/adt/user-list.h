/* SYSTEM LIST STATIK */
/* Berisi definisi dan primitif pemrosesan list statik */
/* Penempatan elemen selalu rapat kiri dan secara implisit */

#ifndef USERLIST_H
#define USERLIST_H

#include <stdio.h>
#include <string.h>
#include "../utils/boolean.h"
#include <stdlib.h>

/*  Kamus Umum */
#define MAX_USERS 300
/* Kapasitas penyimpanan */
#define IDX_MIN 0
/* Indeks minimum list */
#define IDX_UNDEF -1
/* Indeks tak terdefinisi*/
#define MARK_INT -1
#define MARK_F -1.0
#define MARK_STR "KOSONG"
#define SEHAT "SEHAT"

#define MAX_USERNAME_LENGTH 40
#define MAX_PASSWORD_LENGTH 40

typedef struct {
    int id;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char role[10];
    char riwayatPenyakit[50];
    float suhuTubuh;
    int tekananSistolik;
    int tekananDiastolik;
    int detakJantung;
    float saturasiOksigen;
    int kadarGulaDarah;
    float beratBadan;
    int tinggiBadan;
    int kadarKolesterol;
    int trombosit;
} User;

typedef struct{
    User contents[MAX_USERS]; /* Memori tempat penyimpan elemen (container) */
    int nEff; /* Nilai efektif dari suatu list */
} ListUser;

#define nEff(l) (l).nEff
#define ID(l, i) (l).contents[(i)].id
#define USERNAME(l, i) (l).contents[(i)].username
#define PASSWORD(l, i) (l).contents[(i)].password

#define ROLE(l, i) (l).contents[(i)].role
#define PENYAKIT(l, i) (l).contents[(i)].riwayatPenyakit
#define SUHU(l, i) (l).contents[(i)].suhuTubuh

#define TSISTOLIK(l, i) (l).contents[(i)].tekananSistolik
#define DSISTOLIK(l, i) (l).contents[(i)].tekananDiastolik
#define DETAK(l, i) (l).contents[(i)].detakJantung

#define OKSIGEN(l, i) (l).contents[(i)].saturasiOksigen
#define KADARGULA(l, i) (l).contents[(i)].kadarGulaDarah

#define BERAT(l, i) (l).contents[(i)].beratBadan
#define TINGGI(l, i) (l).contents[(i)].tinggiBadan

#define KOLESTEROL(l, i) (l).contents[(i)].kadarKolesterol
#define TROMBOSIT(l, i) (l).contents[(i)].trombosit

/* ********** OPERASI DASAR LIST PENGGUNA ********** */

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : Create List kosong  */
void createListUser(ListUser *l);
// I.S. l tidak terdefinisi
// F.S. Menghasilkan l sebagai list pengguna

/* Kosntruktor : Create User kosong */

/* ********** SELEKTOR ********** */
void createUser(User *user);

/* *** Test List kosong *** */
boolean isListUserEmpty(ListUser l);
// Mengecek apakah list kosong

/* *** Test List penuh *** */
boolean isListUserFull(ListUser l);
// Mengecek apakah list penuh

int getLastIdx(ListUser l);
// Menghasilkan nilai terakhir dari suatu ListUser

/* ********** OPERASI PRIMITIF LAINNYA ********** */
void setPassword(ListUser *l, int currentID, char * password);
// I.S. l, userID, masukan terdefinisi
// F.S. Menghasilkan l baru di mana password pengguna berhasil diganti

void setRole(ListUser *l, int currentID, char * role);

void setRiwayatPenyakit(ListUser *l, int currentID, char * namaPenyakit);

/* ********** OPERASI DASAR PENGGUNA ********** */

void addNewUser(ListUser *l, char * username, char * password);
// I.S. l harus terdefinisi, dan username unik
// F.S. Mengeluarkan l di mana pengguna telah membuat akun baru 

int getIDByUsername(ListUser l, char * username);
// Mencari ID pengguna apabila telah login akun

char * getUsernameByID(ListUser l, int currentID);
// Mencari username pengguna apabila telah login akun

char * getRoleByID(ListUser l, int currentID);
// Mencari role pengguna apabila telah login akun

char * getRiwayatByID(ListUser l, int currentID);
// Mencari riwayat pengguna 

boolean isUserLoggedIn(int currentID);
// Mengecek apakah pengguna telah melakukan login

boolean isValidUsername(ListUser l, char * username);
// Mengecek apakah masukan Username dari pengguna ada di database

boolean isValidPassword(ListUser l, char * password, int currentID);
// Mengecek apakah input password dari user valid untuk akun tersebut

boolean isUniqueUser(ListUser l, char * username);
// Mengecek apakah Username yang akan diregister unik

#endif