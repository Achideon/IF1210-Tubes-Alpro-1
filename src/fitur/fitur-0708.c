#include <stdio.h>
#include "fitur-0708.h"

void sortByNama(ListUser *l, int sort){
    User temp;
    int pass = 0;
    boolean tukar = true;
    if(sort == 1){
        while(pass < nEff(*l) && tukar){
            tukar = false;
            for(int i = nEff(*l) - 1; i > pass; i--){
                if(strcasecmp(USERNAME(*l, i), USERNAME(*l, i-1)) < 0){
                    temp =  l->contents[i];
                    l->contents[i] = l->contents[i-1];
                    l->contents[i-1] = temp;
                    tukar = true;
                }
            }
            pass += 1;
        }
    }else if(sort == 2){
        while(pass < nEff(*l) && tukar){
            tukar = false;
            for(int i = nEff(*l) - 1; i > pass; i--){
                if(strcasecmp(USERNAME(*l, i), USERNAME(*l, i-1)) > 0){
                    temp =  l->contents[i];
                    l->contents[i] = l->contents[i-1];
                    l->contents[i-1] = temp;
                    tukar = true;
                }
            }
            pass += 1;
        }
    }
}

void sortByID(ListUser *l, int sort){
    User temp;
    int pass = 0;
    boolean tukar = true;
    if(sort == 1){
        while(pass < nEff(*l) && tukar){
            tukar = false;
            for(int i = nEff(*l) - 1; i > pass; i--){
                if(ID(*l, i) < ID(*l, i-1)){
                    temp =  l->contents[i];
                    l->contents[i] = l->contents[i-1];
                    l->contents[i-1] = temp;
                    tukar = true;
                }
            }
            pass += 1;
        }
    }else if(sort == 2){
        while(pass < nEff(*l) && tukar){
            tukar = false;
            for(int i = nEff(*l) - 1; i > pass; i--){
                if(ID(*l, i) > ID(*l, i-1)){
                    temp =  l->contents[i];
                    l->contents[i] = l->contents[i-1];
                    l->contents[i-1] = temp;
                    tukar = true;
                }
            }
            pass += 1;
        }
    }
}

ListUser sortByRole(ListUser l1, int role){
    ListUser l2;
    createListUser(&l2);
    nEff(l2) = 0;
    if(role == 0){
        int N = 0;
        for(int i = 0; i < nEff(l1); i++){
            if(strcmp(ROLE(l1,i), "Pasien") == 0 || strcmp(ROLE(l1,i), "Dokter") == 0){
                l2.contents[N] = l1.contents[i];
                nEff(l2) += 1;
                N += 1;
            }
        }
    }else if(role == 1){
        int N = 0;
        for(int i = 0; i < nEff(l1); i++){
            if(strcmp(ROLE(l1,i), "Pasien") == 0){
                l2.contents[N] = l1.contents[i];
                nEff(l2) += 1;
                N += 1;
            }
        }
    }else if(role == 2){
        int N = 0;
        for(int i = 0; i < nEff(l1); i++){
            if(strcmp(ROLE(l1,i), "Dokter") == 0){
                l2.contents[N] = l1.contents[i];
                nEff(l2) += 1;
                N += 1;
            }
        }
    }
    return l2;
}

ListUser sortByPenyakit(ListUser l1, int sortby, int sort, char* penyakit){
    // sortby ( 1 = ID, 2 = Nama), sort (1 = asc, 2 = desc)
    ListUser l2;
    createListUser(&l2);
    int N = 0;
    for(int i =0; i < l1.nEff; i++){
        if(strcmp(PENYAKIT(l1, i), penyakit) == 0){
            l2.contents[N] = l1.contents[i];
            N += 1;
            nEff(l2) += 1;
        }
    }
    if(sortby == 1){
        sortByID(&l2, sort);
    }else if(sortby == 2){
        sortByNama(&l2, sort);
    }
    return l2;
}

void printSpace(int n){
    for (int i = 1; i <= n; i++){
        printf(" ");
    }  
}

void printListUser(ListUser l, int role){
    for(int i = 0; i < nEff(l); i++){
        printUser(l, i, role);
    }
}

void printUser(ListUser l, int i, int role){
    int digits = 0, n = 0;
    // print ID
    printf("%d", ID(l, i));
    if(ID(l, i) < 10) n = 3;
    else if(ID(l, i) >= 10 && ID(l, i) < 100) n = 2;
    else n = 1;
    printSpace(n);
    
    // print nama
    printf("|  ");
    printf("%s", USERNAME(l, i));
    digits = strlen(USERNAME(l, i));
    n = 16 - digits;
    printSpace(n);

    // print Role untuk LIHAT_USER
    if(role == 0){
        printf("|  ");
        printf("%s  ", ROLE(l, i));
    }

    // print Penyakit untuk LIHAT_USER dan LIHAT_PASIEN
    if(role == 0 || role == 1){
        printf("| ");
        if(!strcmp(ROLE(l, i), "Dokter")){
            printf("-");
        }else if(!strcmp(ROLE(l, i), "Pasien")){
            if(strcmp(PENYAKIT(l,i), MARK_STR) == 0) printf("-");
            else printf("%s", PENYAKIT(l, i));
        }
    }
    printf("\n");
}

void lihatUser(ListUser l, int role, int currentID){
    // role 0 = user, 1 = pasien, 2 = dokter
    if (currentID == -1){ 
        printf("\nAnda belum login! Silakan login terlebih dahulu!\n");
    }else if(!strcmp(getRoleByID(l, currentID), "Manager")){
        int pil1, pil2;
        ListUser lSorted;
        printf("\nUrutkan berdasarkan?\n");
        printf("1. ID\n");
        printf("2. Nama\n");
        printf(">> Pilihan: ");
        scanf("%d", &pil1);
        printf("\n");

        while(pil1 != 1 && pil1 != 2){
            printf("Pilih antara 1 atau 2!\n");
            printf(">> Pilihan: ");
            scanf("%d", &pil1);
            printf("\n");
        }
        
        printf("Urutan sort?\n");
        printf("1. ASC (A-Z)\n");
        printf("2. DESC (Z-A)\n");
        printf(">> Pilihan: ");
        scanf("%d", &pil2);
        printf("\n");
        while(pil2 != 1 && pil2 != 2){
            printf("Pilih antara 1 atau 2!\n");
            printf(">> Pilihan: ");
            scanf("%d", &pil2);
            printf("\n");
        }
        
        if(pil1 == 1){
            lSorted = sortByRole(l, role);
            sortByID(&lSorted, pil2);
        }else if(pil1 == 2){
            lSorted = sortByRole(l, role);
            sortByNama(&lSorted, pil2);
        }
        if(nEff(lSorted) == 0) printf("\nUser tidak ditemukan\n");
        else {
            if(role == 0){
                printf("\nID  |  Nama            |  Role    |  Penyakit \n");
                printf("===================================================\n");
            }else if(role == 1){
                printf("\nID  |  Nama            |  Penyakit \n");
                printf("========================================\n");
            }else if(role == 2){
                printf("\nID  |  Nama            \n");
                printf("==========================\n");
            }
            printListUser(lSorted, role);
        }
    }else{
        printf("\nFitur tidak tersedia, anda bukan Manager\n");
    }
    printf("\n");
}

void cariUser(ListUser l, int role, int currentID){
    if (currentID == -1){ 
        printf("\nAnda belum login! Silakan login terlebih dahulu!\n");
    }else if(!strcmp(getRoleByID(l, currentID), "Manager")){
        int pil1, pil2, pil3, id, index;
        char nama[MAX_USERNAME_LENGTH];
        char penyakit[200];
        char penyakit1[100] = MARK_STR;
        char penyakit2[100] = MARK_STR;
        ListUser lp;
    
        printf("\nCari berdasarkan?\n");
        printf("1. ID\n");
        printf("2. Nama\n");
        if(role == 0){
            printf(">> Pilihan: ");
            scanf("%d", &pil1);
            printf("\n");
            if(pil1 == 1){
                printf(">> Masukkan ID user: ");
                scanf("%d", &id);
                index = userSearchByID(l, id);
            }else if (pil1 == 2){
                printf(">> Masukkan nama user: ");
                scanf("%s", nama);
                index = userSearchByName(l, nama);
            }            
        }else if(role == 2){
            printf(">> Pilihan: ");
            scanf("%d", &pil1);
            printf("\n");
            if(pil1 == 1){
                printf(">> Masukkan ID dokter: ");
                scanf("%d", &id);
                index = userSearchByID(l, id);
            }else if (pil1 == 2){
                printf(">> Masukkan nama dokter: ");
                scanf("%s", nama);
                index = userSearchByName(l, nama);
            }
        }else if(role == 1){
            printf("3. Penyakit\n");
            printf(">> Pilihan: ");
            scanf("%d", &pil1);
            printf("\n");

            if(pil1 == 1){
                printf(">> Masukkan ID pasien: ");
                scanf("%d", &id);
                index = userSearchByID(l, id);
            }else if (pil1 == 2){
                printf(">> Masukkan nama pasien: ");
                scanf("%s", nama);
                index = userSearchByName(l, nama);
            }else if (pil1 == 3){
                printf(">> Masukkan nama penyakit: ");
                scanf(" %[^\n]", penyakit);

                printf("\nUrut berdasarkan?\n");
                printf("1. ID\n");
                printf("2. Nama\n");
                printf(">> Pilihan: ");
                scanf("%d", &pil3);

                printf("\nUrutan sort?\n");
                printf("1. ASC (A-Z)\n");
                printf("2. DESC (Z-A)\n");
                printf(">> Pilihan: ");
                scanf("%d", &pil2);
                lp = sortByPenyakit(l, pil3, pil2, penyakit);
            }
        }
        printf("\n");
        if(role == 1 && pil1 == 3){
            if(nEff(lp) == 0) printf("Tidak ada pasien dengan penyakit %s", penyakit);
            else {
                printf("ID  |  Nama            |  Penyakit \n");
                printf("========================================\n");
                printListUser(lp, role);
            }
        }else{
            if(index == MARK_INT && pil1 == 1) printf("User dengan ID %d tidak ditemukan\n", id);
            else if(index == MARK_INT && pil1 == 2) printf("User dengan nama %s tidak ditemukan\n", nama);
            else {
                if(role == 0){
                    printf("ID  |  Nama            |  Role    |  Penyakit \n");
                    printf("===================================================\n");
                }else if(role == 1){
                    printf("ID  |  Nama            |  Penyakit \n");
                    printf("========================================\n");
                }else if(role == 2){
                    printf("ID  |  Nama            \n");
                    printf("==========================\n");
                }
                printUser(l, index, role);
            }
        }
    }else{
        printf("\nFitur tidak tersedia, anda bukan Manager\n");
    }
    printf("\n");
}
