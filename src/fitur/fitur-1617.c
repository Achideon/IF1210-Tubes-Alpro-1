#include <stdio.h>
#include "fitur-1617.h"

void minumObat(ListInventory *inventory, ListPerut *perut, MapObatPenyakit *mapObat, int userID) {
    int choice;
    int obatID;
    char namaObat[MAX_NAME];

    if (isListInventoryEmpty(inventory[userID])) {
        printf("Obat belum tersedia!\n");
        return;
    }

    printf("Daftar obat yang tersedia:\n");
    for (int i = 0; i < inventory[userID].nEff; i++) {
        strcpy(namaObat, mapObatNameByID(mapObat, -1, (*inventory).contents[userID].contents[i]));
        printf("%d. %s\n", i+1, namaObat);
    }

    while(1) {
        printf(">>> Pilih nomor obat yang akan diminum: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > inventory[userID].nEff) {
            printf("Tidak ada obat dengan nomor tersebut\n");
        }
        else {
            obatID = inventory->contents[userID].contents[choice-1];
            break;
        }
    }

    if (!isUserPerutFull(perut, userID)) {
        pushObat(perut, userID, obatID);

        strcpy(namaObat, mapObatNameByID(mapObat, obatID, obatID));
        printf("GLEKGLEKGLEK... %s berhasil diminum!!!\n", namaObat);
        
        useInventory(inventory, userID, obatID, &obatID);
    } else {
        printf("Perut sudah penuh! Tidak bisa minum obat lagi.\n");
    }
}

void minumPenawar(ListInventory *inventory, ListPerut *perut, MapObatPenyakit *mapObat, int userID) {
    int salahObat;
    char namaObat[MAX_NAME];
    
    if (isUserPerutEmpty(perut, userID)) {
        printf("Perut kosong! Belum ada obat yang dimakan.\n");
        return;
    }
    
    popObat(perut, userID, &salahObat);
    
    strcpy(namaObat, mapObatNameByID(mapObat, salahObat, salahObat));
    
    insertInventory(inventory, userID, salahObat);
    printf("Uwekkk!!! obat %s keluar dan kembali ke inventory\n", namaObat);
}