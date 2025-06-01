#include "fitur-1112.h"

#define SEHAT "SEHAT"

/* Implementasi DIAGNOSIS */
void diagnosis(Matrix m, ListPenyakit p, ListUser *l, int currentID){
    if (currentID == -1) printf("Anda belum login! Silakan login terlebih dahulu!\n\n");
    else if (strcmp(getRoleByID(*l,currentID),"Dokter")){
        printf("Anda bukanlah seorang Dokter!\n\n");
        return;
    }
    else{
        int rowNow, colNow;
        for (int i=0;i<m.rows;i++){
            for (int j=0;j<m.cols;j++){
                if ((m.data[i][j].idDoktor) == currentID){
                rowNow=i;
                colNow=j;
                break;
                }
            }
        }
        int pasienID = getFirst(m.data[rowNow][colNow].antriPasien);
        if (strcmp(getRiwayatByID(*l, pasienID),"KOSONG")){
            printf("Pasien %s telah didiagnosis! Silakan imbau untuk minum obat!\n\n", getUsernameByID(*l,pasienID));
            return;
        }
        else if (!strcmp(getRiwayatByID(*l, pasienID), SEHAT)){
            printf("%s tidak terdiagnosis penyakit apapun! Silakan mengimbau pasien untuk pulang.\n\n", getUsernameByID(*l,pasienID));
            return;
        }
        else{
            int lengthOP = p.nEff;
            int idx = userSearchByID(*l,pasienID);
            for (int i = 0; i < lengthOP; i++){
                if (((*l).contents[idx].suhuTubuh >= p.contents[i].suhuTubuhMin && (*l).contents[idx].suhuTubuh <= p.contents[i].suhuTubuhMax) 
                        && ((*l).contents[idx].tekananSistolik >= p.contents[i].tekananSistolikMin && (*l).contents[idx].tekananSistolik <= p.contents[i].tekananSistolikMax) 
                        && ((*l).contents[idx].tekananDiastolik >= p.contents[i].tekananDiastolikMin && (*l).contents[idx].tekananDiastolik <= p.contents[i].tekananDiastolikMax) &&((*l).contents[pasienID].detakJantung >= p.contents[i].detakJantungMin && (*l).contents[pasienID].detakJantung <= p.contents[i].detakJantungMax) 
                        && ((*l).contents[idx].saturasiOksigen >= p.contents[i].saturasiOksigenMin && (*l).contents[idx].saturasiOksigen <= p.contents[i].saturasiOksigenMax) 
                        && ((*l).contents[idx].kadarGulaDarah >= p.contents[i].kadarGulaDarahMin && (*l).contents[idx].kadarGulaDarah <= p.contents[i].kadarGulaDarahMax)
                        && ((*l).contents[idx].beratBadan >= p.contents[i].beratBadanMin && (*l).contents[idx].beratBadan <= p.contents[i].beratBadanMax) 
                        && ((*l).contents[idx].tinggiBadan >= p.contents[i].tinggiBadanMin && (*l).contents[idx].tinggiBadan <= p.contents[i].tinggiBadanMax) 
                        && ((*l).contents[idx].kadarKolesterol >= p.contents[i].kadarKolesterolMin && (*l).contents[idx].kadarKolesterol <= p.contents[i].kadarKolesterolMax)
                        && ((*l).contents[idx].trombosit >= p.contents[i].trombositMin && (*l).contents[idx].trombosit <= p.contents[i].trombositMax)){
                            strcpy((*l).contents[idx].riwayatPenyakit,p.contents[i].namaPenyakit);
                            printf("%s terdiagnosa penyakit %s\n\n",getUsernameByID(*l,pasienID), p.contents[i].namaPenyakit);
                            return;
                        }
            }
            printf("Tidak ada penyakit yang cocok! Pasien sehat.\n\n");
            strcpy((*l).contents[idx].riwayatPenyakit,SEHAT);
            return;
        }
    

    }
}


void ngobatin(Matrix m, MapObatPenyakit mOP, ListPenyakit p, ListInventory *inv, ListUser *l, int currentID){
    if (strcmp(getRoleByID(*l,currentID),"Dokter")){
        printf("Anda bukanlah seorang Dokter!\n\n");
        return;
    }
    else{
        printf("Dokter sedang mengobati pasien!\n\n");
        int rowNow, colNow;
        for (int i=0;i<m.rows;i++){
            for (int j=0;j<m.cols;j++){
                if ((m.data[i][j].idDoktor) == currentID){
                rowNow=i;
                colNow=j;
                break;
                }
            }
        }
        int pasienID = getFirst(m.data[rowNow][colNow].antriPasien);
        int idxUser = userSearchByID(*l,pasienID);
        if (!(strcmp(getRiwayatByID(*l, pasienID),"KOSONG"))){
            printf("Pasien %s tidak memiliki penyakit!\nPasien belum di diagnosis!\n\n", getUsernameByID(*l,pasienID));
            return;
        }
        else if (!strcmp(getRiwayatByID(*l, pasienID), SEHAT)){
            printf("%s tidak terdiagnosis penyakit apapun!\nPasien sehat!\n\n", getUsernameByID(*l,pasienID));
            return;
        }
        else{
            int idx = -1;
            for (int i = 0; i < (*inv).nEff; i++){
                if ((*inv).nEff == 0) break;
                if ((*inv).contents[i].contents[0] == pasienID){
                    idx = i;
                    break;
                }
            }
            if (idx == -1){
                int idx = (*inv).nEff;
                (*inv).nEff++;
                (*inv).contents[idx].contents[0] = pasienID; 
                printf("Pasien memiliki penyakit %s\n",(*l).contents[idxUser].riwayatPenyakit);
                printf("Obat yang harus diberikan:\n");
                int penyakitID = getPenyakitIDByName(&p, (*l).contents[idxUser].riwayatPenyakit);
                char (*obat)[MAX_NAME] = mapGetListObatName(&mOP, penyakitID);
                ListValue listObat = mapGetListObatID(&mOP, penyakitID);
                for (int i = 0; i < listObat.nEff; i++){
                    insertInventory(inv, pasienID, listObat.contents[i]);
                    printf("%i. %s", i+1,obat[i]);
                }
                printf("\n\n");
            }
            else printf("Pasien sudah diobati! Silakan imbau untuk minum obat!\n\n");
            return;
        }

    }
}

