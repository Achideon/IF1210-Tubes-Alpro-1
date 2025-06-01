#include "fitur-060915.h"

/* Output dari denah */
void printDenah(Matrix M){
    printf("\033[38;5;15m");
    printf("\n");
    printf("     ");
    for(int i = 0; i < M.cols; i++) printf("   %d  ", i+1);
    printf("\n");
    for(int i = 0; i < M.rows; i++){
        if(i == 0){
            printf("     +");
            for(int j = 1; j < M.cols; j++) printf("=====+");
            if(M.cols > 0) printf("=====+\n");
        }
        printf("   %c ", i + 65);
        for(int j = 0; j < M.cols; j++){ 
            printf("| ");
            if(M.data[i][j].idDoktor <= 0) printf("\033[38;5;243m"); 
            else if(queueLength(M.data[i][j].antriPasien) < M.data[i][j].kapasitas) printf("\033[38;5;82m");
            else if(queueLength(M.data[i][j].antriPasien) < M.data[i][j].kapasitas + M.data[i][j].kapasitasAntrian) printf("\033[38;5;226m");
            else if(queueLength(M.data[i][j].antriPasien) == M.data[i][j].kapasitas + M.data[i][j].kapasitasAntrian) printf("\033[38;5;196m");
            printf("%c%d  ", i + 65, j + 1);
            printf("\033[38;5;15m");
        }
        if(M.cols > 0) printf("|\n");
        if(i == 5 - 1){
            printf("     +");
            for(int j = 1; j < M.cols; j++) printf("=====+");
            if(M.cols > 0) printf("=====+\n");
        } 
        else{
            printf("     +");
            for(int j = 1; j < M.cols; j++) printf("=====+");
            if(M.cols > 0) printf("=====+\n");
        }
    }
    printf("\n");
}

void printRuangan(Matrix M, char * ruangan, ListUser dataUser, int currentId){
    int i = ruangan[0] - 65;
    int j = ruangan[1] - 49;
    printf("\n--- Detail Ruangan %s ---\n", ruangan);
    printf("Kapasitas: \033[38;5;51m%d\n", M.data[i][j].kapasitas);
    setColor(dataUser, currentId);
	printf("Doktor   : ");
    if(M.data[i][j].idDoktor > 0) printf("\033[38;5;51m%s\n", getUsernameByID(dataUser, M.data[i][j].idDoktor)); // dataUser == placeholder list user
    else printf(" -\n");
    setColor(dataUser, currentId);
    printf("Pasien di dalam ruangan:\n");
    if(queueLength(M.data[i][j].antriPasien) > 0){
        int k = 1;
        Address temp = M.data[i][j].antriPasien.head;
        while(temp != M.data[i][j].antriPasien.tail && k < M.data[i][j].kapasitas){
            printf("   %d. \033[38;5;51m%s\n", k, getUsernameByID(dataUser, temp->info));
            k++;
            temp = temp->next;
            setColor(dataUser, currentId);
        } printf("   %d. \033[38;5;51m%s\n", k, getUsernameByID(dataUser, temp->info)); // print tail queue
    } else printf("   \033[38;5;51mTidak ada pasien di dalam ruangan saat ini\n");
    setColor(dataUser, currentId);
    printf("\n");
}

void printSemuaAntrian(Matrix M, ListUser dataUser, int currentID){
    if (currentID == -1){ 
        printf("Anda belum login! Silakan login terlebih dahulu!\n\n");
        return;
    }
    else if (strcmp(getRoleByID(dataUser,currentID),"Manager")){
        printf("Anda bukanlah seorang Manager!\n\n");
        return;
    }

    printf("\n===== DENAH RUMAH SAKIT =====\n\n");
    printDenah(M);
    printf("\033[38;5;111m"); 
    for(int i = 0; i < M.rows; i++){
        for(int j = 0; j < M.cols; j++){
            if(M.data[i][j].idDoktor > 0){
                printf("============ %c%d ============\n", i+65, j+1);
                printf("Kapasitas: \033[38;5;51m%d\033[38;5;111m\n", M.data[i][j].kapasitas);
                printf("Doktor   : \033[38;5;51m%s\033[38;5;111m\n", getUsernameByID(dataUser, M.data[i][j].idDoktor)); // dataUser == placeholder list user
                printf("Jumlah pasien dalam dan luar ruangan: \033[38;5;51m%d\033[38;5;111m\n", queueLength(M.data[i][j].antriPasien));
                printf("Pasien di dalam ruangan:\n");
                int k = 1;
                Address temp = M.data[i][j].antriPasien.head;
                if(queueLength(M.data[i][j].antriPasien) > 0){
                    while(temp != M.data[i][j].antriPasien.tail && k < M.data[i][j].kapasitas){
                        printf("   %d. \033[38;5;51m%s\033[38;5;111m\n", k, getUsernameByID(dataUser, temp->info));
                        k++;
                        temp = temp->next;
                    } printf("   %d. \033[38;5;51m%s\033[38;5;111m\n", k, getUsernameByID(dataUser, temp->info)); // print tail queue
                } else printf("   \033[38;5;51mTidak ada pasien di dalam ruangan saat ini\033[38;5;111m\n");
                printf("Pasien di antrian:\n");
                if(queueLength(M.data[i][j].antriPasien) > M.data[i][j].kapasitas){
                    temp = temp->next;
                    while(temp != M.data[i][j].antriPasien.tail && k < M.data[i][j].kapasitas + M.data[i][j].kapasitasAntrian){
                        printf("   %d. \033[38;5;51m%s\033[38;5;111m\n", k - M.data[i][j].kapasitas + 1, getUsernameByID(dataUser, temp->info));
                        k++;
                        temp = temp->next;
                    } printf("   %d. \033[38;5;51m%s\033[38;5;111m\n", k - M.data[i][j].kapasitas + 1, getUsernameByID(dataUser, temp->info));
                } else printf("   \033[38;5;51mTidak ada pasien di antrian saat ini\033[38;5;111m\n");
                printf("\n");
            }
        }
    }
}

void antrianSaya(Matrix M, ListUser dataUser, int userID){
    if (userID == -1) printf("Anda belum login! Silakan login terlebih dahulu!\n");
    else if (strcmp(getRoleByID(dataUser,userID),"Pasien")){
        printf("Anda bukanlah seorang Pasien!\n\n");
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
			printf("Dokter: \033[38;5;51m%s\033[38;5;150m\n", getUsernameByID(dataUser, lokasi->idDoktor));
			printf("Ruangan: \033[38;5;51m%c%d\033[38;5;150m\n", i+65, j+1);
			printf("Posisi antrian: \033[38;5;51m%d\033[38;5;150m dari \033[38;5;51m%d\033[38;5;150m\n\n", idx - lokasi->kapasitas + 1, lokasi->kapasitasAntrian);
		}
    } else {
		printf("Anda \033[38;5;51mbelum terdaftar\033[38;5;150m dalam antrian check-up!\n");
		printf("Silakan daftar terlebih dahulu dengan command \033[38;5;51mDAFTAR_CHECKUP\033[38;5;150m\n\n");
    }
}