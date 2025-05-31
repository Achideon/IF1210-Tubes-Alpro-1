#include "write-file.h"

void writeFileUser(ListUser l, char* filepath, boolean *status) {
    FILE *file = fopen(filepath, "w");
    
    if (file == NULL) {
        status = false;
        return;
    }
    
    fprintf(file, "id;username;password;role;riwayat_penyakit;suhu_tubuh;tekanan_darah_sistolik;tekanan_darah_diastolik;detak_jantung;saturasi_oksigen;kadar_gula_darah;berat_badan;tinggi_badan;kadar_kolesterol;trombosit\n");

    for (int i = 0; i < l.nEff; i++) {
        fprintf(file, "%d;%s;%s;%s;%s;%.2f;%d;%d;%d;%.2f;%d;%.2f;%d;%d;%d\n",
                ID(l, i),
                USERNAME(l, i),
                PASSWORD(l, i),
                ROLE(l, i),
                PENYAKIT(l, i),
                SUHU(l, i),
                TSISTOLIK(l, i),
                DSISTOLIK(l, i),
                DETAK(l, i),
                OKSIGEN(l, i),
                KADARGULA(l, i),
                BERAT(l, i),
                TINGGI(l, i),
                KOLESTEROL(l, i),
                TROMBOSIT(l, i));
    }
    
    fclose(file);
}

void writeFileConfig(Matrix *M, ListInventory *Li, ListPerut *Lp, char* filepath, boolean *status) {
    FILE *file = fopen(filepath, "w");

    if (file == NULL) {
        status = false;
        return;
    }

    // Baris 1: Ukuran denah rumah sakit
    fprintf(file, "%d %d\n", M->rows, M->cols);

    // Baris 2: Kapasitas maksimum setiap ruangan
    if (M->rows > 0 && M->cols > 0) {
        fprintf(file, "%d %d\n", M->data[0][0].kapasitas, M->data[0][0].kapasitasAntrian);
    } else {
        fprintf(file, "0 0\n");
    }

    // Baris 3 - (2 + rows*cols): State tiap ruangan
    for (int i = 0; i < M->rows; i++) {
        for (int j = 0; j < M->cols; j++) {
            Ruangan R = M->data[i][j];
            if (R.idDoktor == 0 || R.idDoktor == MARK_INT) {
                fprintf(file, "0\n");
            } else {
                fprintf(file, "%d", R.idDoktor);
                if(!isQueueEmpty(R.antriPasien)){
                    Address temp = R.antriPasien.head;
                    while(temp != R.antriPasien.tail){
                        fprintf(file, " %d", temp->info);
                        temp = temp->next;
                    } fprintf(file, " %d", temp->info);
                } else {
                    fprintf(file, " 0");
                }
                fprintf(file, "\n");
            }
        }
    }

    fprintf(file, "%d\n", Li->nEff);
    // writing list inventory :/
    for(int i  = 0; i < Li->nEff; i++){
        fprintf(file, "%d", Li->contents[i].contents[0]);
        for(int j = 0; j < Li->contents[i].nEff; j++){
            fprintf(file, " %d", Li->contents[i].contents[j+1]);
        }
        fprintf(file, "\n");
    }
    // writing list perut :v
    fprintf(file, "%d\n", Lp->nEff);
    for(int i  = 0; i < Lp->nEff; i++){
        fprintf(file, "%d", Lp->contents[i].contents[0]);
        for(int j = 0; j < Lp->contents[i].top; j++){
            fprintf(file, " %d", Lp->contents[i].contents[j+1]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}
