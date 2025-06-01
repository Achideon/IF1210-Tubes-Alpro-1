#include <stdio.h>
#include "fitur-1617.h"

void minumObat(ListInventory *inventory, ListPerut *perut, MapObatPenyakit *mapObat, int userID, ListPenyakit *listpenyakit, ListUser listuser) {
    int choice;
    int obatID;
    char namaObat[MAX_NAME];

    int idxUser;
    for (int i=0; i<(*inventory).nEff; i++){
        if((*inventory).contents[i].contents[0] == userID){
            idxUser = i;
        }
    }

    if (strcmp(getRoleByID(listuser,userID),"Pasien")){
        printf("Anda bukan Pasien!\n\n");
        return;
    }

    if (isInventoryEmpty(*inventory, userID)) {
        printf("Tidak ada obat untuk diminum!\n\n");
        return;
    }

    int keyPenyakit = getPenyakitIDByName(listpenyakit,getRiwayatByID(listuser,userID));

    printf("Daftar obat yang tersedia:\n");
    for (int i = 1; i <= inventory->contents[idxUser].nEff; i++) {
        strcpy(namaObat, mapObatNameByID(mapObat, keyPenyakit, (*inventory).contents[idxUser].contents[i]));
        namaObat[strlen(namaObat) - 1] = 0;
        printf("%d. %s\n", i, namaObat);
    }

    while(1) {
        printf(">>> Pilih nomor obat yang akan diminum: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > inventory->contents[idxUser].nEff) {
            printf("Tidak ada obat dengan nomor tersebut\n");
        }
        else {
            obatID = inventory->contents[idxUser].contents[choice];
            break;
        }
    }

    if (!isUserPerutFull(perut, userID)) {
        pushObat(perut, userID, obatID);
        strcpy(namaObat, mapObatNameByID(mapObat, keyPenyakit, obatID));
        namaObat[strlen(namaObat) - 1] = 0;
        printf("GLEKGLEKGLEK... %s berhasil diminum!!!\n\n", namaObat);
        int val;
        useInventory(inventory, userID, obatID, &val);
    } else {
        printf("Perut sudah penuh! Tidak bisa minum obat lagi.\n\n");
    }
}

void minumPenawar(ListInventory *inventory, ListPerut *perut, MapObatPenyakit *mapObat, int userID, ListPenyakit *listpenyakit, ListUser listuser) {
    int salahObat;
    char namaObat[MAX_NAME];
    
    if (strcmp(getRoleByID(listuser,userID),"Pasien")){
        printf("Anda bukan Pasien!\n\n");
        return;
    }
    
    if (isUserPerutEmpty(perut, userID)) {
        printf("Perut kosong! Belum ada obat yang dimakan.\n\n");
        return;
    }

    int keyPenyakit = getPenyakitIDByName(listpenyakit,getRiwayatByID(listuser,userID));
    
    popObat(perut, userID, &salahObat);
    
    strcpy(namaObat, mapObatNameByID(mapObat, keyPenyakit, salahObat));
    namaObat[strlen(namaObat) - 1] = 0;
    insertInventory(inventory, userID, salahObat);
    printf("Uwekkk!!! obat %s keluar dan kembali ke inventory\n\n", namaObat);
}
