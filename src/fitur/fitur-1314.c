#include "fitur-1314.h"
boolean urutanBenar (ListPerut L1, ListPenyakit L2, MapObatPenyakit M, char * penyakit, int currentId, boolean rightOrder[]){
    boolean order = true;
    printf("Cek urutan...\n");
    ListValue obat = mapGetListObatID(&M, getPenyakitIDByName(&L2, penyakit));
    ListPerut dummyPerut = L1;
    int idxobat = obat.nEff-1;
    int idx;
    for (int k=0;k<dummyPerut.nEff;k++){
        if (dummyPerut.contents[k].contents[0] == currentId) {
            idx = k;
            break;
        }
    }
    for(idxobat=obat.nEff-1; idxobat>=0; idxobat--){
        rightOrder[obat.nEff - 1 - idxobat] = true;
        if (obat.contents[idxobat] != dummyPerut.contents[idx].contents[dummyPerut.contents[idx].top]){
            order = false;
            rightOrder[obat.nEff - 1 - idxobat] = false;
        }
        int obatOut;
        popObat(&dummyPerut, currentId, &obatOut);
    }
    return order;
}

void pulangDok(ListObat *Lobat,ListPenyakit *Listp,MapObatPenyakit *Map,ListPerut *Perut,ListUser *L, Matrix *M, ListInventory *I, int currentId){
    int idx, idxPerut, nEffPerut;
    for (int k=0;k<Perut->nEff;k++){
        if (Perut->contents[k].contents[0] == currentId) {
            idxPerut = k;
            nEffPerut = Perut->contents[k].top;
            break;
        }
    }
    boolean rightOrder[nEffPerut];

    if (strcmp(getRoleByID(*L, currentId),"Pasien")!=0) return;
    if (strcmp(getRiwayatByID(*L,currentId),MARK_STR) == 0){/*Belum didiagnosis*/
        printf("Anda masih belum didiagnosis!\n\n");
        return;
    }else if (strcmp(getRiwayatByID(*L,currentId),SEHAT) == 0){ /*Tidak ada penyakit yang cocok*/
        for (int i=0;i<=L->nEff;i++){
            if (L->contents[i].id==currentId) {
                idx = i;
                break;
            }
        }
        L->contents[idx].suhuTubuh          = MARK_F;
        L->contents[idx].tekananSistolik    = MARK_INT;
        L->contents[idx].tekananDiastolik   = MARK_INT;
        L->contents[idx].detakJantung       = MARK_INT;
        L->contents[idx].saturasiOksigen    = MARK_F;
        L->contents[idx].kadarGulaDarah     = MARK_INT;
        L->contents[idx].beratBadan         = MARK_F;
        L->contents[idx].tinggiBadan        = MARK_INT;
        L->contents[idx].kadarKolesterol    = MARK_INT;
        L->contents[idx].trombosit          = MARK_INT;
        strcpy(L->contents[idx].riwayatPenyakit, MARK_STR);
        int val;
        nextQueue(&pasienRuangan(M, currentId)->antriPasien,&val);
        printf("Selamat anda dinyatakan Sehat dan tidak terkena penyakit apa-apa!\n");
        return;
    }else if (!isInventoryEmpty(*I, currentId)){ 
        printf("Dokter sedang memeriksa keadaanmu...\n");
        printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk!\n\n");
        return;
    }else if(isUserPerutEmpty(Perut, currentId)){
        printf("Kamu belum diberikan obat!\n");
        return;
    }else if (!urutanBenar(*Perut,*Listp, *Map, PENYAKIT(*L, userSearchByID(*L, currentId)), currentId, rightOrder)){ /*Obat salah susunan*/
        /*Mencari indeks, tempat currentId berada*/
        for (int k=0;k<Perut->nEff;k++){
            if (Perut->contents[k].contents[0] == currentId) {
                idx = k;
                break;
            }
        }
        printf("Dokter sedang memeriksa keadaanmu... \n");
        printf("Maaf, tapi kamu masih belum bisa pulang!\n\n");
        printf("Urutan peminuman obat yang diharapkan: \n");
        /*List obat yang benar*/
        ListValue obat = mapGetListObatID(Map, getPenyakitIDByName(Listp, getRiwayatByID(*L,currentId)));
        for (int i=0;i<obat.nEff;i++){
            char obatName[50];
            strcpy(obatName, getNameByObatID(Lobat, obat.contents[i]));
            obatName[strlen(obatName) - 1] = 0;
            printf("%s", obatName);
            if (i!=obat.nEff-1) printf(" -> ");
        }/*Penulisan : dari yang pertama dimakan sampai terakhir dimakan*/
        printf("\n====================================================\n");
        /*Setelah sudah diprint list obat yang benar*/
        /*Buat salinan ListPerut *Perut supaya tidak mengubah-ubah isi Perut. Lalu, ada ListValue obatPerut memuat obat-obat yang ada di perut dengan pengurutan sesuai indeks.*/
        printf("Urutan obat yang kamu minum\n");
        ListPerut dummyPerut = *Perut;
        dummyPerut.nEff = Perut->nEff;
        ListValue obatPerut;
        obatPerut.nEff = 0;

        while(dummyPerut.contents[idxPerut].top != 0){
            popObat(&dummyPerut, currentId, &obatPerut.contents[obatPerut.nEff]);
            obatPerut.nEff++;
        }   /*Pengisian ListValue obatPerut dari yang terbaru dimakan sampai yang terlama dimakan*/
        for (int i=obatPerut.nEff-1;i>=0;i--){
            char obatName[50];
            strcpy(obatName, getNameByObatID(Lobat, obatPerut.contents[i]));
            obatName[strlen(obatName) - 1] = 0;
            if(rightOrder[i]){
                printf("\033[38;5;46m");
                printf("%s", obatName);
                printf("\033[38;5;150m"); 
            }
            else{ 
                printf("\033[38;5;196m\033[5m"); 
                printf("%s", obatName);
                printf("\033[0m");
                printf("\033[38;5;150m"); 
            }
            if (i!=0) printf(" -> ");
        }
        printf("\n\n");
        printf("Silahkan kunjungi dokter untuk meminta penawar yang sesuai!\n\n");
        return;
    }else { 
        /*Mencari indeks tempat ID berada*/
        for (int i=0;i<=L->nEff;i++){
            if (L->contents[i].id==currentId) {
                idx = i;
                break;
            }
        }
        printf("Dokter sedang memeriksa keadaanmu... \n");
        if ((getFirst(pasienRuangan(M, currentId)->antriPasien)) == currentId){
            L->contents[idx].suhuTubuh          = MARK_F;
            L->contents[idx].tekananSistolik    = MARK_INT;
            L->contents[idx].tekananDiastolik   = MARK_INT;
            L->contents[idx].detakJantung       = MARK_INT;
            L->contents[idx].saturasiOksigen    = MARK_F;
            L->contents[idx].kadarGulaDarah     = MARK_INT;
            L->contents[idx].beratBadan         = MARK_F;
            L->contents[idx].tinggiBadan        = MARK_INT;
            L->contents[idx].kadarKolesterol    = MARK_INT;
            L->contents[idx].trombosit          = MARK_INT;
            strcpy(L->contents[idx].riwayatPenyakit, MARK_STR);
            int val;
            nextQueue(&pasienRuangan(M, currentId)->antriPasien,&val);
            printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n\n");
            printASCIIPulangDok();
            return;
        }else{
            printf("Sabar! Masih ada orang di depanmu.\n\n");
            return;
        }
    }   
}

void checkUp(ListUser *L, Matrix *M, int currentId){
    if (strcmp(getRoleByID(*L, currentId),"Pasien")!=0){
        printf("Maaf, Anda bukanlah seorang Pasien.\n\n");
        return;
    }
    if ((strcmp(getRoleByID(*L,currentId), "Pasien") == 0) && (!cekPasienQueue(M,currentId))){  
        /*Syaratnya adalah ketika pasien dengan id "currentId" belum terdaftar di antrian apa pun (Dengan arti lain adalah dia tidak berada di matrix denah juga.)*/
        int idx;
        for(int i = 0; i <= L->nEff; i++){
            if(L->contents[i].id == currentId) {
                idx = i;
                break;
            }
        }
        printf("Silahkan masukkan data check-up Anda: \n");

        printf("Suhu Tubuh (Celcius): ");
        scanf("%f", &L->contents[idx].suhuTubuh);
        while (L->contents[idx].suhuTubuh < 0) {
            printf("Suhu tubuh harus bernilai positif.\n");
            printf("Suhu Tubuh (Celcius): ");
            scanf("%f", &L->contents[idx].suhuTubuh);
        }

        printf("Tekanan Darah (sistol/diastol, contoh 120 80): ");
        scanf("%d %d", &L->contents[idx].tekananSistolik, &L->contents[idx].tekananDiastolik);
        while (L->contents[idx].tekananSistolik < 0 || L->contents[idx].tekananDiastolik < 0) {
            printf("Tekanan darah harus bernilai positif.\n");
            printf("Tekanan Darah (sistol/diastol): ");
            scanf("%d %d", &L->contents[idx].tekananSistolik, &L->contents[idx].tekananDiastolik);
        }

        printf("Detak Jantung (bpm): ");
        scanf("%d", &L->contents[idx].detakJantung);
        while (L->contents[idx].detakJantung < 0) {
            printf("Detak Jantung harus bernilai positif.\n");
            printf("Detak Jantung (bpm): ");
            scanf("%d", &L->contents[idx].detakJantung);
        }

        printf("Saturasi Oksigen (%%): ");
        scanf("%f", &L->contents[idx].saturasiOksigen);
        while (L->contents[idx].saturasiOksigen < 0) {
            printf("Saturasi Oksigen harus bernilai positif.\n");
            printf("Saturasi Oksigen (%%): ");
            scanf("%f", &L->contents[idx].saturasiOksigen);
        }

        printf("Kadar Gula Darah (mg/dL): ");
        scanf("%d", &L->contents[idx].kadarGulaDarah);
        while (L->contents[idx].kadarGulaDarah < 0) {
            printf("Kadar Gula Darah harus bernilai positif.\n");
            printf("Kadar Gula Darah (mg/dL): ");
            scanf("%d", &L->contents[idx].kadarGulaDarah);
        }

        printf("Berat Badan (kg): ");
        scanf("%f", &L->contents[idx].beratBadan);
        while (L->contents[idx].beratBadan < 0) {
            printf("Berat Badan harus bernilai positif.\n");
            printf("Berat Badan (kg): ");
            scanf("%f", &L->contents[idx].beratBadan);
        }

        printf("Tinggi Badan (cm): ");
        scanf("%d", &L->contents[idx].tinggiBadan);
        while (L->contents[idx].tinggiBadan < 0) {
            printf("Tinggi Badan harus bernilai positif.\n");
            printf("Tinggi Badan (cm): ");
            scanf("%d", &L->contents[idx].tinggiBadan);
        }

        printf("Kadar Kolesterol (mg/dL): ");
        scanf("%d", &L->contents[idx].kadarKolesterol);
        while (L->contents[idx].kadarKolesterol < 0) {
            printf("Kadar Kolesterol harus bernilai positif.\n");
            printf("Kadar Kolesterol (mg/dL): ");
            scanf("%d", &L->contents[idx].kadarKolesterol);
        }

        printf("Trombosit (ribu/µL): ");
        scanf("%d", &L->contents[idx].trombosit);
        while (L->contents[idx].trombosit < 0) {
            printf("Trombosit harus bernilai positif.\n");
            printf("Trombosit (ribu/µL): ");
            scanf("%d", &L->contents[idx].trombosit);
        }

        /*Setelah pengisian data pasien, maka selanjutnya adalah proses untuk memilih dokter.*/
        printf("\nBerikut adalah dokter yang tersedia: \n");
        int number=1,idtemp;    /*number berfungsi untuk penomoran dan idtemp berfungsi untuk penomoran id dokter agar lebih mudah*/
        int row = M->rows, col = M->cols;
        int arrayDokter[row*col];   /*Menyimpan id dokter yang tersedia*/
        int antri; /*Menyimpan jumlah antrian sementara*/
        for (int i=0;i<M->rows;i++){
            for (int j=0;j<M->cols;j++){
                idtemp = M->data[i][j].idDoktor;
                if(idtemp!=MARK_INT){
                    if (queueLength(M->data[i][j].antriPasien) <= M->data[i][j].kapasitas) {
                        antri = 0;
                    }else {
                        antri= (queueLength(M->data[i][j].antriPasien) - M->data[i][j].kapasitas);
                    }
                    printf("%d. Dr. %s - Ruangan %s (Antrian: %d orang)\n",number,getUsernameByID(*L,idtemp),getRoomByDoctor(*M,idtemp), antri);
                    arrayDokter[number-1] = M->data[i][j].idDoktor;
                    number += 1;
                }
            }
        }
        boolean found = false;
        printf("\n");
        while (!found){
            if (number == 1) printf("Pilih dokter (1): ");
            else printf("Pilih dokter (1-%d): ",number-1);
            int option;
            scanf("%d",&option);   
            while (option < 1 || option > number-1){
                printf("Input kembali, pilih dokter yang tersedia : ");
                scanf("%d",&option);  
            }
            idtemp = arrayDokter[option-1];/*idtemp menjadi id dokter yang dipilih*/
            /*Proses menambahkan pasien ke queue*/
            /*Loop untuk mencari indeks ruangan*/
            int antrian, i, j; /*Menunjukkan posisi antrian pasien setelah check-up*/
            boolean dalam; /*Boolean untuk menunjukkan posisi pasien di dalam atau luar ruangan*/
            for (i=0;i<M->rows && !found;i++){
                for (j=0;j<M->cols;j++){
                    if(M->data[i][j].idDoktor==idtemp){
                        if (queueLength(M->data[i][j].antriPasien)<(M->data[i][j].kapasitasAntrian+M->data[i][j].kapasitas)){ 
                            if (queueLength(M->data[i][j].antriPasien)==0) createQueue(&M->data[i][j].antriPasien);
                            addQueue(&M->data[i][j].antriPasien, currentId);
                            if (queueLength(M->data[i][j].antriPasien) <= M->data[i][j].kapasitas) {
                                antrian = queueLength(M->data[i][j].antriPasien);
                                dalam = true;
                            }else{
                                antrian =(queueLength(M->data[i][j].antriPasien) - M->data[i][j].kapasitas);
                                dalam = false;
                            }
                            found = true;
                            break;  
                        }
                    }
                }
            }
            if (found){
                printf("\nPendaftaran check-up berhasil!\n");
                printf("Anda terdaftar pada antrian Dr. %s di ruangan %s.\n", getUsernameByID(*L, idtemp), getRoomByDoctor(*M, idtemp));
                if (dalam) printf("Posisi antrian Anda: %d ( di dalam ruangan ) \n", antrian);
                else if (!dalam)  printf("Posisi antrian Anda: %d ( di luar ruangan ) \n", antrian);
            }else if (!found){
                printf("\nMohon maaf antrian sudah penuh!\n");
                printf("Mohon pilih ulang dokter yang berbeda!\n");
            }
            /*Pesan terakhir*/
            printf("\n");
        }
    }else if ((cekPasienQueue(M,currentId))){   
        printf("Anda sudah terdaftar dalam antrian check-up!\n");
        printf("Silakan selesaikan check-up yang sudah terdaftar terlebih dahulu.\n\n");
    }
}

void printASCIIPulangDok(){
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⠤⠤⠤⠀⣀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠐⢉⠴⣚⠉⣙⠢⢄⡤⢞⡂⢀⣐⢄⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡔⡤⣞⢁⠊⢀⣀⠐⢿⡄⠰⢁⡀⠈⠺⣦⢡⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣗⣟⡸⠀⠻⡿⠃⢸⣇⢃⠿⠿⠀⠀⣽⢸⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠈⠙⢷⣴⡀⠀⠠⣪⣾⣷⡄⡀⠠⣐⢕⠁⠀\n");
    printf("⠀⢰⡦⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠙⠲⡖⠓⠉⠁⠈⠉⠒⠀⠈⢸⠀⠀\n");
    printf("⢶⣿⣷⣤⢀⣀⡀⠀⠀⣏⡑⠢⢄⠀⠀⠀⠈⠐⠀⠐⠀⠀⠀⠀⠀⡸⡀⠀\n");
    printf("⠛⠛⠛⠟⠀⠤⠤⠌⢉⠀⠈⠓⢬⣿⣦⡤⣤⣤⠤⠤⣤⣤⣤⣤⣚⣔⣄⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⡤⠂⠀⠀⢀⠤⠤⢄⡨⠔⠒⢍⠉⢁⣯⡆\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⡗⢤⡤⣬⠀⠀⠀⢇⠀⠀⠀⠁⠀⠀⡸⢰⣿⣿⡿\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢌⡿⣽⡀⠀⠀⠈⠒⢄⡀⠀⢀⠔⠁⠈⠙⡋⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⠳⢧⣠⣤⣄⣠⣀⣈⣱⡥⠤⠴⠦⠴⠃⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿⠀⣿⣿⣿⣄⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠉⠉⠀⠈⠉⠉⠉⠀⠀⠀⠀⠀⠀\n\n");
    return;
}
