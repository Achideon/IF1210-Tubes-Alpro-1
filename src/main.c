#include <stdio.h>
#include <stdlib.h>
#include "fitur/fitur-01030405.h"
#include "fitur/fitur-021018.h"
#include "fitur/fitur-060915.h"
#include "fitur/fitur-0708.h"
#include "adt/user-list.h"
#include "adt/matrix-denah.h"
#include "adt/queue.h"
#include "utils/write-file.h"
#include "utils/read-file.h"
#include "fitur/fitur-1112.h"
#include "adt/map-obat-penyakit.h"
#include "adt/inventory-list.h"
#include "adt/obat-penyakit.h"

int main(int argc, char *argv[]){
    char *folder_name;
    if (argc > 1) {
        folder_name = argv[1];
    } else {
        folder_name = "";
    }
/* ----------- INISIALISASI -----------*/
    Matrix M;
    ListUser l;
    ListObat lo;
    ListPenyakit lp;
    ListObatPenyakit lop;
    ListInventory inv;
    MapObatPenyakit mop;
    ListPerut lpe;
    
    boolean status = true;
    int currentID = MARK_INT;
    int id = 0;
    char username[MAX_USERNAME_LENGTH];
    char cekNama[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char input[20], ruangan[10];
/* ----------- BACA FILE -----------*/
    load(&M, &l, &inv, &lpe, &status, folder_name);
    readFileObat(&lo);
    readFileObatPenyakit(&lop);
    readFilePenyakit(&lp);
    createMapObatPenyakit (lo, lop, &mop);

/* ----------- PROGRAM UTAMA -----------*/
    printf("Selamat datang di sistem informasi rumah sakit!\n");
    while(status){
        printf(">>>>");
        scanf("%s", input);
        if(strcmp(input, "LOGIN") == 0){
            login(&l, &currentID);
        }else if(strcmp(input, "LOGOUT") == 0){
            logout(&l, &currentID);
        }else if(strcmp(input, "LUPA_PASSWORD") == 0){
            lupaPassword(&l, &currentID);
        }else if(strcmp(input, "HELP") == 0){
            menuHelp(&l, &currentID);
        }else if(strcmp(input, "REGISTER") == 0){
            regist(&l, currentID);
        }else if(strcmp(input, "TAMBAH_DOKTER") == 0){
            addDoctor(&l, currentID);
        }else if(strcmp(input, "ASSIGN_DOKTER") == 0){
            assignDoctor(&l, currentID, &M);
        }else if(strcmp(input, "LIHAT_USER") == 0){
            lihatUser(l, 0, currentID);
        }else if(strcmp(input, "LIHAT_PASIEN") == 0){
            lihatUser(l, 1, currentID);
        }else if(strcmp(input, "LIHAT_DOKTER") == 0){
            lihatUser(l, 2, currentID);
        }else if(strcmp(input, "CARI_USER") == 0){
            cariUser(l, 0, currentID);
        }else if(strcmp(input, "CARI_PASIEN") == 0){
            cariUser(l, 1, currentID);
        }else if(strcmp(input, "CARI_DOKTER") == 0){
            cariUser(l, 2, currentID);
        }else if(strcmp(input, "LIHAT_DENAH") == 0){
            printDenah(M);
        }else if(strcmp(input, "LIHAT_RUANGAN") == 0){
            scanf("%s", ruangan);
            if(!isRoomValid(M, ruangan)){
                printf("Ruangan tidak ada! Coba cari ruangan lain\n");
            }else printRuangan(M, ruangan, l);
        }else if(strcmp(input, "DIAGNOSIS") == 0){
            diagnosis(M, lp, &l, currentID);
        }else if(strcmp(input, "NGOBATIN") == 0){
            ngobatin(M,mop,lp,&inv,&l,currentID);
        }else if(strcmp(input, "EXIT") == 0){
            ext(&status, l, M, inv, lp);
        }else{
            printf("Fungsi tidak terdaftar!\n\n");
        }
    }
    return 0;
}
