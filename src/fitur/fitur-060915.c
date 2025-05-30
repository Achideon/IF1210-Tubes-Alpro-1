#include "fitur-060915.h"

/* Output dari denah */
void printDenah(Matrix M){
    printf("   ");
    for(int i = 0; i < M.cols; i++) printf("   %d  ", i+1);
    printf("\n");
    for(int i = 0; i < M.rows; i++){
        if(i == 0){
            printf("   +");
            for(int j = 1; j < M.cols; j++) printf("=====+");
            if(M.cols > 0) printf("=====+\n");
        }
        printf(" %c ", i + 65);
        for(int j = 0; j < M.cols; j++) printf("| %c%d  ", i + 65, j + 1);
        if(M.cols > 0) printf("|\n");
        if(i == 5 - 1){
            printf("   +");
            for(int j = 1; j < M.cols; j++) printf("=====+");
            if(M.cols > 0) printf("=====+\n");
        } 
        else{
            printf("   +");
            for(int j = 1; j < M.cols; j++) printf("=====+");
            if(M.cols > 0) printf("=====+\n");
        }
    }
}

void printRuangan(Matrix M, char * ruangan, ListUser dataUser){
    int i = ruangan[0] - 65;
    int j = ruangan[1] - 49;
    printf("--- Detail Ruangan %s ---\n", ruangan);
    printf("Kapasitas: %d\n", M.data[i][j].kapasitas);
	printf("Doktor   : ");
    if(M.data[i][j].idDoktor > 0) printf("%s\n", getUsernameByID(dataUser, M.data[i][j].idDoktor)); // dataUser == placeholder list user
    else printf(" -\n");
    printf("Pasien di dalam ruangan:\n");
    if(queueLength(M.data[i][j].antriPasien) != 0){
        int k = 1;
        Address temp = M.data[i][j].antriPasien.head;
        while(temp != M.data[i][j].antriPasien.tail && k < M.data[i][j].kapasitas){
            printf("   %d. %s\n", k, getUsernameByID(dataUser, temp->info));
            k++;
            temp = temp->next;
        } printf("   %d. %s\n", k, getUsernameByID(dataUser, temp->info)); // print tail queue
    } else printf("   Tidak ada pasien di dalam ruangan saat ini\n");
}

void printSemuaAntrian(Matrix M, ListUser dataUser, int currentID){
    if (currentID == -1){ 
        printf("Anda belum login! Silakan login terlebih dahulu!\n");
        return;
    }
    else if (strcmp(getRoleByID(dataUser,currentID),"Manager")){
        printf("Anda bukanlah seorang Manager!\n");
        return;
    }
    printDenah(M);
    for(int i = 0; i < M.rows; i++){
        for(int j = 0; j < M.cols; j++){
            if(M.data[i][j].idDoktor > 0){
                printf("============ %c%d ============\n", i+65, j+1);
                printf("Kapasitas: %d\n", M.data[i][j].kapasitas);
                printf("Doktor   : %s\n", getUsernameByID(dataUser, M.data[i][j].idDoktor)); // dataUser == placeholder list user
                printf("Pasien di dalam ruangan:\n");
                int k = 1;
                Address temp = M.data[i][j].antriPasien.head;
                if(queueLength(M.data[i][j].antriPasien) > 0){
                    while(temp != M.data[i][j].antriPasien.tail && k < M.data[i][j].kapasitas){
                        printf("   %d. %s\n", k, getUsernameByID(dataUser, temp->info));
                        k++;
                        temp = temp->next;
                    } printf("   %d. %s\n", k, getUsernameByID(dataUser, temp->info)); // print tail queue
                } else printf("   Tidak ada pasien di dalam ruangan saat ini\n");
                printf("Pasien di antrian:\n");
                if(queueLength(M.data[i][j].antriPasien) > M.data[i][j].kapasitas){
                    while(temp != M.data[i][j].antriPasien.tail && k < M.data[i][j].kapasitas + M.data[i][j].kapasitasAntrian){
                        printf("   %d. %s\n", k - M.data[i][j].kapasitas + 1, getUsernameByID(dataUser, temp->info));
                        k++;
                        temp = temp->next;
                    } printf("   %d. %s\n", k - M.data[i][j].kapasitas + 1, getUsernameByID(dataUser, temp->info)); // print tail queue
                } else printf("   Tidak ada pasien di antrian saat ini\n");
                printf("\n");
            }
        }
    }
}

void antrianSaya(Matrix M, ListUser dataUser, int userID, int currentID){
    if (currentID == -1) printf("Anda belum login! Silakan login terlebih dahulu!\n");
    else if (strcmp(getRoleByID(*l,currentID),"Pasien")){
        printf("Anda bukanlah seorang Pasien!\n");
        return;
    }
    Ruangan *lokasi;
    lokasi = pasienRuangan(&M, userID);
    if(lokasi != NULL){
		int idx = 0;
        Address temp = lokasi->antriPasien.head;
		int i = 0; int j = 0;
		while(i < M.rows && M.data[i][j].idDoktor != lokasi->idDoktor){
			j = 0;
			while(j < M.cols && M.data[i][j].idDoktor != lokasi->idDoktor){
				j++;
			}
			i++;
		}
        while(temp->info != userID){
            temp = temp->next;
			idx++;
        }
		if(idx < lokasi->kapasitas){
			printf("Anda sudah di ruangan dokter!\n");
		}
		else{
			printf("Status antrian anda:\n");
			printf("Dokter: %s\n", getUsernameByID(dataUser, lokasi->idDoktor));
			printf("Ruangan: %c%d\n", i+65, j+1);
			printf("Posisi antrian: %d dari %d\n", idx - lokasi->kapasitas + 1, lokasi->kapasitasAntrian);
		}
    } else {
		printf("Anda belum terdaftar dalam antrian check-up!\n");
		printf("Silakan daftar terlebih dahulu dengan command DAFTAR_CHECKUP\n");
    }
}