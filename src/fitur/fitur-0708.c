#include <stdio.h>
#include "fitur-0708.h"

void sortbyNama(ListUser *l, int sort){
    User temp;
    int pass = 0;
    boolean tukar = true;
    if(sort == 1){
        while(pass < nEff(*l) && tukar){
            tukar = false;
            for(int i = nEff(*l); i > pass; i--){
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
            for(int i = nEff(*l); i > pass; i--){
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

void sortbyID(ListUser *l, int sort){
    User temp;
    int pass = 0;
    boolean tukar = true;
    if(sort == 1){
        while(pass < nEff(*l) && tukar){
            tukar = false;
            for(int i = nEff(*l); i > pass; i--){
                if(ID(*l, i) > ID(*l, i-1)){
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
            for(int i = nEff(*l); i > pass; i--){
                if(ID(*l, i) < ID(*l, i-1)){
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

ListUser lihatUserbyName(ListUser l1, int role, int sort){
    // role 0 = user, 1 = pasien, 2 = dokter
    ListUser l2;
    createListUser(&l2);
    if(role == 0){
        l2 = l1;
    }else if(role == 1){
        int N = 0;
        for(int i =1; i <= l1.nEff; i++){
            if(strcmp(l1.contents[i].role, "Pasien") == 0){
                N += 1;
                l2.contents[N] = l1.contents[i];
                l2.nEff += 1;
            }
        }
    }else if(role == 2){
        int N = 0;
        for(int i =1; i <= l1.nEff; i++){
            if(strcmp(l1.contents[i].role, "Dokter") == 0){
                N += 1;
                l2.contents[N] = l1.contents[i];
                l2.nEff += 1;
            }
        }
    }
    sortbyNama(&l2, sort);
    return l2;
}

ListUser lihatUserbyID(ListUser l1, int role, int sort){
    // role 0 = user, 1 = pasien, 2 = dokter
    ListUser l2;
    createListUser(&l2);
    if(role == 0){
        l2 = l1;
    }else if(role == 1){
        int N = 0;
        for(int i =1; i <= l1.nEff; i++){
            if(strcmp(l1.contents[i].role, "Pasien") == 0){
                N += 1;
                l2.contents[N] = l1.contents[i];
                l2.nEff += 1;
            }
        }
    }else if(role == 2){
        int N = 0;
        for(int i =1; i <= l1.nEff; i++){
            if(strcmp(l1.contents[i].role, "Dokter") == 0){
                N += 1;
                l2.contents[N] = l1.contents[i];
                l2.nEff += 1;
            }
        }
    }
    sortbyID(&l2,sort);
    return l2;
}

ListUser lihatUserByPenyakit(ListUser l1, int sortby, int sort, char* penyakit){
    // sortby ( 1 = ID, 2 = Nama), sort (1 = asc, 2 = desc)
    ListUser l2;
    createListUser(&l2);
    int N = 0;
    for(int i =1; i <= l1.nEff; i++){
        if(strcmp(PENYAKIT(l1, i), penyakit) == 0){
            N += 1;
            l2.contents[N] = l1.contents[i];
            nEff(l2) += 1;
        }
    }
    if(sortby == 1){
        sortbyID(&l2, sort);
    }else if(sortby == 2){
        sortbyNama(&l2, sort);
    }
    return l2;
}

void printSpace(int n){
    for (int i = 1; i <= n; i++){
        printf(" ");
    }  
}

void printListUser(ListUser l, int role){
    for(int i = 1; i <= l.nEff; i++){
        printUser(l, i, role);
    }
}

void printUser(ListUser l, int i, int role){
    int digits = 0, n = 0;
    // print ID
    printf("%d", l.contents[i].id);
    if(l.contents[i].id < 10) n = 2;
    else if(l.contents[i].id >= 10 && l.contents[i].id < 100) n =1;
    else n = 0;
    printSpace(n);
    
    // print nama
    printf("|  ");
    printf("%s", l.contents[i].username);
    digits = strlen(l.contents[i].username);
    n = 16 - digits;
    printSpace(n);

    // print Role untuk LIHAT_USER
    if(role == 0){
        printf("| ");
        printf("%s  ", l.contents[i].role);
    }

    // print Penyakit untuk LIHAT_USER dan LIHAT_PASIEN
    if(role == 0 || role == 1){
        printf("| ");
        if(!strcmp(l.contents[i].role, "Dokter")){
            printf("-");
        }else if(!strcmp(l.contents[i].role, "Pasien")){
            printf("%s", l.contents[i].riwayatPenyakit);
        }
    }
    printf("\n");
}

int userSearchByID(ListUser l, int x){
    int low = 1, high = l.nEff;
    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Check if x is present at mid
        if (l.contents[mid].id == x)
            return mid;

        // If x greater, ignore left half
        if (l.contents[mid].id < x)
            low = mid + 1;

        // If x is smaller, ignore right half
        else
            high = mid - 1;
    }
    // If we reach here, then element was not present
    return MARK_INT;
}

int userSearchByName(ListUser l, char *x){
    for(int i = 1; i <= l.nEff; i++){
        if(!strcasecmp(l.contents[i].username, x)){
            return i;
        }
    }
    return MARK_INT;
}

void lihatUser(ListUser l, int role, int currentID){
    // role 0 = user, 1 = pasien, 2 = dokter
    if(!strcmp(getRoleByID(l, currentID), "Manager")){
        int pil1, pil2;
        ListUser lSorted;
        printf("Urutkan berdasarkan?\n");
        printf("1. ID\n");
        printf("2. Nama\n");
        printf(">>Pilihan: ");
        scanf("%d", &pil1);
        printf("\n");

        while(pil1 != 1 && pil1 != 2){
            printf("Pilih antara 1 atau 2!");
            printf(">>Pilihan: ");
            scanf("%d", &pil1);
            printf("\n");
        }
        
        printf("Urutan sort?\n");
        printf("1. ASC (A-Z)\n");
        printf("2. DESC (Z-A)\n");
        printf(">>Pilihan: ");
        scanf("%d", &pil2);
        printf("\n");
        while(pil2 != 1 && pil2 != 2){
            printf("Pilih antara 1 atau 2!");
            printf(">>Pilihan: ");
            scanf("%d", &pil2);
            printf("\n");
        }
        if(role == 0){
            printf("ID  |  Nama            |  Role    |  Penyakit \n");
            printf("---------------------------------------\n");
        }else if(role == 1){
            printf("ID  |  Nama            |  Penyakit \n");
            printf("------------------------------------\n");
        }else if(role == 2){
            printf("ID  |  Nama            \n");
            printf("---------------------------\n");
        }
        
        if(pil1 == 1){
            lSorted = lihatUserbyID(l, role, pil2);
        }else if(pil1 == 2){
            lSorted = lihatUserbyName(l, role, pil2);
        }
        printListUser(lSorted, role);
    }else{
        printf("Fitur tidak tersedia, anda bukan Manager\n");
    }
}

void cariUser(ListUser l, int role, int currentID){
    if(!strcmp(getRoleByID(l, currentID), "Manager")){
        int pil1, pil2, id, index;
        char nama[MAX_USERNAME_LENGTH];
        char penyakit[200];
        ListUser lp;
    
        printf("Cari berdasarkan?\n");
        if(role == 0){
            printf(">>Pilihan: ");
            scanf("%d", &pil1);
            printf("\n");
            if(pil1 == 1){
                printf(">>Masukkan ID user: ");
                scanf("%d", &id);
                index = userSearchByID(l, id);
            }else if (pil1 == 2){
                printf(">>Masukkan nama user: ");
                scanf("%s", nama);
                index = userSearchByName(l, nama);
            }
            printf("ID  |  Nama            |  Role    |  Penyakit \n");
            printf("---------------------------------------\n");
            
        }else if(role == 2){
            printf(">>Pilihan: ");
            scanf("%d", &pil1);
            printf("\n");
            if(pil1 == 1){
                printf(">>Masukkan ID dokter: ");
                scanf("%d", &id);
                index = userSearchByID(l, id);
            }else if (pil1 == 2){
                printf(">>Masukkan nama dokter: ");
                scanf("%s", nama);
                index = userSearchByName(l, nama);
            }
            printf("ID  |  Nama            \n");
            printf("---------------------------\n");
        }else if(role == 1){
            if(pil1 == 1){
                printf(">>Masukkan ID dokter: ");
                scanf("%d", &id);
                index = userSearchByID(l, id);
            }else if (pil1 == 2){
                printf(">>Masukkan nama dokter: ");
                scanf("%s", nama);
                index = userSearchByName(l, nama);
            }else if (pil1 == 3){
                printf(">>Masukkan nama penyakit: ");
                scanf("%s", penyakit);
                printf("Urutan sort?\n");
                printf("1. ASC (A-Z)\n");
                printf("2. DESC (Z-A)\n");
                printf(">>Pilihan: ");
                scanf("%d", &pil2);
                lp = lihatUserByPenyakit(l, pil1, pil2, penyakit);
            }
            printf("ID  |  Nama            |  Penyakit \n");
            printf("------------------------------------\n");
        }
        if(role == 1 && pil1 == 3){
            printListUser(lp, role);
        }else{
            printUser(l, index, role);
        }
    }else{
        printf("Fitur tidak tersedia, anda bukan Manager\n");
    }
}