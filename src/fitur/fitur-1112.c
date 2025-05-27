#include "fitur-1112.h"

#define SEHAT "SEHAT"

/* Implementasi DIAGNOSIS */
void diagnosis(Matrix m, ListPenyakit p, ListUser *l, int currentID){
    if (currentID == -1) printf("Anda belum login! Silakan login terlebih dahulu!\n");
    else if (strcmp(getRoleByID(*l,currentID),"Dokter")){
        printf("Anda bukanlah seorang Dokter!\n");
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
        int pasienID = getFirst(m.data[rowNow][colNow].antriPasienDalam);
        if (strcmp(getRiwayatByID(*l, pasienID),"KOSONG")){
            printf("Pasien %s telah didiagnosis! Silakan imbau untuk minum obat!\n", getUsernameByID(*l,pasienID));
            return;
        }
        else if (!strcmp(getRiwayatByID(*l, pasienID), SEHAT)){
            printf("%s tidak terdiagnosis penyakit apapun! Silakan mengimbau pasien untuk pulang.\n", getUsernameByID(*l,pasienID));
            return;
        }
        else{
            int lengthOP = p.nEff;
            for (int i = 0; i < lengthOP; i++){
                if (((*l).contents[pasienID].suhuTubuh >= p.contents[i].suhuTubuhMin && (*l).contents[pasienID].suhuTubuh <= p.contents[i].suhuTubuhMax) 
                        && ((*l).contents[pasienID].tekananSistolik >= p.contents[i].tekananSistolikMin && (*l).contents[pasienID].tekananSistolik <= p.contents[i].tekananSistolikMax) 
                        && ((*l).contents[pasienID].tekananDiastolik >= p.contents[i].tekananDiastolikMin && (*l).contents[pasienID].tekananDiastolik <= p.contents[i].tekananDiastolikMax) &&((*l).contents[pasienID].detakJantung >= p.contents[i].detakJantungMin && (*l).contents[pasienID].detakJantung <= p.contents[i].detakJantungMax) 
                        && ((*l).contents[pasienID].saturasiOksigen >= p.contents[i].saturasiOksigenMin && (*l).contents[pasienID].saturasiOksigen <= p.contents[i].saturasiOksigenMax) 
                        && ((*l).contents[pasienID].kadarGulaDarah >= p.contents[i].kadarGulaDarahMin && (*l).contents[pasienID].kadarGulaDarah <= p.contents[i].kadarGulaDarahMax)
                        && ((*l).contents[pasienID].beratBadan >= p.contents[i].beratBadanMin && (*l).contents[pasienID].beratBadan <= p.contents[i].beratBadanMax) 
                        && ((*l).contents[pasienID].tinggiBadan >= p.contents[i].tinggiBadanMin && (*l).contents[pasienID].tinggiBadan <= p.contents[i].tinggiBadanMax) 
                        && ((*l).contents[pasienID].kadarKolesterol >= p.contents[i].kadarKolesterolMin && (*l).contents[pasienID].kadarKolesterol <= p.contents[i].kadarKolesterolMax)
                        && ((*l).contents[pasienID].trombosit >= p.contents[i].trombositMin && (*l).contents[pasienID].trombosit <= p.contents[i].trombositMax)){
                            strcpy((*l).contents[pasienID].riwayatPenyakit,p.contents[i].namaPenyakit);
                            printf("%s terdiagnosa penyakit %s\n",getUsernameByID(*l,pasienID), p.contents[i].namaPenyakit);
                            return;
                        }
            }
            printf("Tidak ada penyakit yang cocok! Pasien sehat.\n");
            strcpy((*l).contents[pasienID].riwayatPenyakit,SEHAT);
            return;
        }
    

    }
}
void ngobatin(Matrix m, MapObatPenyakit mOP, ListPenyakit p, ListInventory *inv, ListUser *l, int currentID){
    if (strcmp(getRoleByID(*l,currentID),"Dokter")){
        printf("Anda bukanlah seorang Dokter!\n");
        return;
    }
    else{
        printf("Dokter sedang mengobati pasien!");
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
        int pasienID = getFirst(m.data[rowNow][colNow].antriPasienDalam);
        if (!(strcmp(getRiwayatByID(*l, pasienID),"KOSONG"))){
            printf("Pasien %s tidak memiliki penyakit!\n Pasien belum di diagnosis!\n", getUsernameByID(*l,pasienID));
            return;
        }
        else if (!strcmp(getRiwayatByID(*l, pasienID), SEHAT)){
            printf("%s tidak terdiagnosis penyakit apapun!\n Pasien sehat!\n", getUsernameByID(*l,pasienID));
            return;
        }
        else{
            printf("Pasien memiliki penyakit %s\n",(*l).contents[pasienID].riwayatPenyakit);
            printf("Obat yang harus diberikan:\n");
            int penyakitID = getPenyakitIDByName(&p, (*l).contents[pasienID].riwayatPenyakit);
            char (*obat)[MAX_NAME] = mapGetListObatName(&mOP, penyakitID);
            ListValue listObat = mapGetListObatID(&mOP, penyakitID);
            for (int i = 1; i <= listObat.nEff; i++){
                (*inv).contents[pasienID].contents[i] = listObat.contents[i];
                printf("%i. %s", i+1,obat[i]);
            }
            return;
        }

    }
}