#include <stdio.h>
#include <stdlib.h>
#include "fitur/fitur-01030405.h"
#include "fitur/fitur-021018.h"
#include "fitur/fitur-060915.h"
#include "fitur/fitur-0708.h"
#include "fitur/fitur-1617.h"
#include "fitur/fitur-1112.h"
#include "fitur/fitur-1314.h"
#include "adt/user-list.h"
#include "adt/matrix-denah.h"
#include "adt/queue.h"
#include "utils/write-file.h"
#include "utils/read-file.h"
#include "utils/cirnospin.h"
#include "fitur/fitur-1112.h"
#include "adt/map-obat-penyakit.h"
#include "adt/inventory-list.h"
#include "adt/obat-penyakit.h"

int main(int argc, char *argv[]){
    char *folder_name;
    char folder_path[100];
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
    folder_path[50];
    strcpy(folder_path, "../data");
    load(&M, &l, &inv, &lpe, &status, folder_name);
    if(status){
        readFileObat(&lo, folder_path);
        readFileObatPenyakit(&lop, folder_path);
        readFilePenyakit(&lp, folder_path);
        createMapObatPenyakit (lo, lop, &mop);
    }

/* ----------- PROGRAM UTAMA -----------*/
    sortByID(&l,1);
    if(status) {
        printf("\n");
        printf("\033[38;5;215m====================================================================================================\n");
        printf("\033[38;5;215m\033[5m         \033[25m _____               _      _____     _   _ _      _____ _                   \n");
        printf("\033[38;5;215m\033[5m  ██     \033[25m| __  |_ _ _____ ___| |_   |   __|___| |_|_| |_   |   | |_|_____ ___ ___ ___    \033[5m  ██       \033[0m \n");
        printf("\033[38;5;215m\033[5m██████   \033[25m|    -| | |     | .'|   |  |__   | .'| '_| |  _|  | | | | |     | . |   |_ -|   \033[5m██████    \033[0m\n");
        printf("\033[38;5;215m\033[5m  ██     \033[25m|__|__|___|_|_|_|__,|_|_|  |_____|__,|_,_|_|_|    |_|___|_|_|_|_|___|_|_|___|   \033[5m  ██       \033[0m\n");
        printf("\n");
        printf("\033[38;5;215m====================================================================================================\n\n");
        printf("\033[38;5;215mSelamat datang di sistem informasi rumah sakit!\nApakah ada yang bisa kami bantu?\033[0m");
        printf("\033[38;5;215m\nSebelum memulai, silahkan ketik \"HELP\"\n\n\033[0m");
    }
    while(status){
        setColor(l, currentID);
        printf(">>>> ");
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
            }else printRuangan(M, ruangan, l, currentID);
        }else if(strcmp(input, "LIHAT_SEMUA_RUANGAN") == 0){
            printSemuaAntrian(M, l, currentID);
        }else if(strcmp(input, "DIAGNOSIS") == 0){
            diagnosis(M, lp, &l, currentID);
        }else if(strcmp(input, "NGOBATIN") == 0){
            ngobatin(M,mop,lp,&inv,&l,currentID);
        }else if(strcmp(input, "PULANGDOK") == 0){
            pulangDok(&lo, &lp, &mop, &lpe, &l, &M, &inv, currentID);
        }else if(strcmp(input, "DAFTAR_CHECKUP") == 0){
            checkUp(&l, &M, currentID);
        }else if(strcmp(input, "ANTRIAN") == 0){
            antrianSaya(M, l, currentID);
        }else if(strcmp(input, "MINUM_OBAT") == 0){
            minumObat(&inv, &lpe, &mop, currentID, &lp, l);
        }else if(strcmp(input, "PENAWAR") == 0){
            minumPenawar(&inv, &lpe, &mop, currentID, &lp, l);
        }else if(strcmp(input, "SAVE") == 0){
            save(M, l, inv, lpe);
        }else if(strcmp(input, "EXIT") == 0){
            ext(&status, l, M, inv, lpe);
        }else if(strcmp(input, "CIRNO_SPIN") == 0){
            for(int i = 0; i < 10; i++){
                PlayCirno();
            }
        }else{
            printf("Fungsi tidak terdaftar!\n\n");
        }
    }
    printf("\033[0m");
    return 0;
}
