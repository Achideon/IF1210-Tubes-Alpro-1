#include "write-file.h"

void writeFile_user(ListUser l, int nEff, const char* filename) {
    FILE *file = fopen(filename, "w");
    
    if (file == NULL) {
        return;
    }
    
    fprintf(file, "id,username,password,role,riwayat_penyakit,suhu_tubuh,tekanan_darah_sistolik,tekanan_darah_diastolik,detak_jantung,saturasi_oksigen,kadar_gula_darah,berat_badan,tinggi_badan,kadar_kolesterol,kadar_kolesterol_ldl,trombosit\n");

    for (int i = 1; i <= nEff; i++) {
        fprintf(file, "%d,%s,%s,%s,%s,%.2f,%d,%d,%d,%.2f,%d,%.2f,%d,%d,%d,%d\n",
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
                KOLESTEROLLDL(l, i),
                TROMBOSIT(l, i));
    }
    
    fclose(file);
}

void writeFile_config(const Matrix *M) {
    FILE *file = fopen("../src/file/config.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk penulisan.\n");
        return;
    }

    // Baris 1: Ukuran denah rumah sakit
    fprintf(file, "%d %d\n", M->rows, M->cols);

    // Baris 2: Kapasitas maksimum setiap ruangan
    if (M->rows > 0 && M->cols > 0) {
        fprintf(file, "%d\n", M->data[0][0].kapasitas);
    } else {
        fprintf(file, "0\n");
    }

    // Baris 3 - (2 + rows*cols): State tiap ruangan
    for (int i = 0; i < M->rows; i++) {
        for (int j = 0; j < M->cols; j++) {
            Ruangan R = M->data[i][j];
            if (R.idDoktor == 0 || R.idDoktor == MARK_INT) {
                fprintf(file, "0\n");
            } else {
                fprintf(file, "%d", R.idDoktor);
                for (int k = 0; k < R.antriPasien.nEff; k++) {
                    fprintf(file, " %d", R.antriPasien.contents[k]);
                }
                fprintf(file, "\n");
            }
        }
    }

    fclose(file);
}
