#include <stdio.h>
#include "read-file.h"

void parsing(char *input, char *format, int dataCount, ...){
    va_list args;
    va_start(args, dataCount);
    int idxGet = 0;
    for(int i = 0; i < dataCount; i++){
        char parsedInput[50];
        int idxPut = 0;
        while(input[idxGet] != ';' && input[idxGet] != '\n' && input[idxGet] != '\0'){
            parsedInput[idxPut] = input[idxGet];
            idxGet++;
            idxPut++;
        }
        parsedInput[idxPut] = '\0';
        if(format[i] == 'i'){
            int* output;
            output = va_arg(args, int*);
            *output = atoi(parsedInput);
        }
        else if(format[i] == 'c'){
            char* output;
            output = va_arg(args, char*);
            *output = parsedInput[0];
        }
        else if(format[i] == 'f'){
            float* output;
            output = va_arg(args, float*);
            *output = atof(parsedInput);
        }
        else if(format[i] == 's'){
            char* output;
            output = va_arg(args, char*);
            strcpy(output, parsedInput);
        }
        idxGet++;
    }
    va_end(args);
}

void readFileUser(ListUser *l) 
{
    createListUser(l);
    FILE *file = fopen("file/user.csv", "r");

    char line[MAX_LINE_LENGTH];
    int idxUser = 1;
    
    // Pengecekan apakah file ada atau tidak
    if (!(file)) 
    {
        fclose(file);
        printf("Maaf terjadi kesalahan. File tidak ditemukan!\n");
        return;
    }

    // Skip header dari file dan mengecek apakah file kosong
    if (!(fgets(line, sizeof(line), file))) 
    {
        fclose(file);
        printf("Maaf terjadi kesalahan. Ternyata file kosong!\n");
        return;
    }
    
    if ((fgets(line, sizeof(line), file)))
    {
        char username[MAX_USERNAME_LENGTH];
        char password[MAX_PASSWORD_LENGTH];
        char role[10];
        char riwayatPenyakit[50];
        int id, sistolik, diastolik, detak, kadarGula, tinggi, kolesterol, trombosit;
        float suhu, oksigen, berat;
        parsing(line, "issssfiiififiiii", 15, &id, username, password, role, riwayatPenyakit, &suhu, &sistolik, &diastolik, &detak, &oksigen, &kadarGula, &berat, &tinggi, &kolesterol, &trombosit);
        ID(*l, idxUser) = id;
        strcpy(USERNAME(*l, idxUser), username);
        strcpy(PENYAKIT(*l, idxUser), riwayatPenyakit);
        strcpy(PASSWORD(*l, idxUser), password);
        strcpy(ROLE(*l, idxUser), role);
        SUHU(*l, idxUser) = suhu;
        TSISTOLIK(*l, idxUser) = sistolik;
        DSISTOLIK(*l, idxUser) = diastolik;
        DETAK(*l, idxUser) = detak;
        OKSIGEN(*l, idxUser) = oksigen;
        KADARGULA(*l, idxUser) = kadarGula;
        BERAT(*l, idxUser) = berat;
        TINGGI(*l, idxUser) = tinggi;
        KOLESTEROL(*l, idxUser) = kolesterol;
        TROMBOSIT(*l, idxUser) = trombosit;
        nEff(*l) += 1;
        idxUser++;
    } 
    
    else
    {
        fclose(file);
        printf("Maaf terjadi kesalahan. Ternyata file kosong!\n");
        return;
    }

    while ((fgets(line, sizeof(line), file)))
    {
        char username[MAX_USERNAME_LENGTH];
        char password[MAX_PASSWORD_LENGTH];
        char role[10];
        char riwayatPenyakit[50];
        int id, sistolik, diastolik, detak, kadarGula, tinggi, kolesterol, trombosit;
        float suhu, oksigen, berat;
        parsing(line, "issssfiiififiiii", 15, &id, username, password, role, riwayatPenyakit, &suhu, &sistolik, &diastolik, &detak, &oksigen, &kadarGula, &berat, &tinggi, &kolesterol, &trombosit);
        ID(*l, idxUser) = id;
        strcpy(USERNAME(*l, idxUser), username);
        strcpy(PENYAKIT(*l, idxUser), riwayatPenyakit);
        strcpy(PASSWORD(*l, idxUser), password);
        strcpy(ROLE(*l, idxUser), role);
        SUHU(*l, idxUser) = suhu;
        TSISTOLIK(*l, idxUser) = sistolik;
        DSISTOLIK(*l, idxUser) = diastolik;
        DETAK(*l, idxUser) = detak;
        OKSIGEN(*l, idxUser) = oksigen;
        KADARGULA(*l, idxUser) = kadarGula;
        BERAT(*l, idxUser) = berat;
        TINGGI(*l, idxUser) = tinggi;
        KOLESTEROL(*l, idxUser) = kolesterol;
        TROMBOSIT(*l, idxUser) = trombosit;
        nEff(*l) += 1;
        idxUser++;
    }

    fclose(file);
    return;
}



void readFilePenyakit(ListPenyakit *l)
{
    createListPenyakit(l);
    FILE *file = fopen("file/penyakit.csv", "r");

    char line[MAX_LINE_LENGTH];
    int idx = 0;
    
    // Pengecekan apakah file ada atau tidak
    if (!(file)) 
    {
        printf("Maaf terjadi kesalahan. File Penyakit tidak ditemukan!\n");
        return;
    }

    // Skip header dari file dan mengecek apakah file kosong
    if (!(fgets(line, sizeof(line), file))) 
    {
        fclose(file);
        printf("Maaf terjadi kesalahan. Ternyata file kosong!\n");
        return;
    }
    
    if ((fgets(line, sizeof(line), file)))
    {
        int id;
        char namaPenyakit[MAX_NAME];
        int sistolikMin, sistolikMax;
        int diastolikMin, diastolikMax;
        int detakMin, detakMax;
        int kadarGulaMin, kadarGulaMax;
        int tinggiMin, tinggiMax;
        int kolesterolMin, kolesterolMax;
        int trombositMin, trombositMax;
        float suhuMin, suhuMax;
        float oksigenMin, oksigenMax;
        float beratMin, beratMax;
        parsing(line, "isffiiiiiiffiiffiiiiii", 22, &id, namaPenyakit, &suhuMin, &suhuMax, &sistolikMin, &sistolikMax, &diastolikMin, &diastolikMax, &detakMin, &detakMax, &oksigenMin, &oksigenMax, &kadarGulaMin, &kadarGulaMax, &beratMin, &beratMax, &tinggiMin, &tinggiMax, &kolesterolMin, &kolesterolMax, &trombositMin, &trombositMax);
        (*l).contents[idx].id = id;
        strcpy((*l).contents[idx].namaPenyakit, namaPenyakit);
        (*l).contents[idx].suhuTubuhMin = suhuMin;
        (*l).contents[idx].suhuTubuhMax = suhuMax;
        (*l).contents[idx].tekananSistolikMin = sistolikMin;
        (*l).contents[idx].tekananSistolikMax = sistolikMax;
        (*l).contents[idx].tekananDiastolikMin = diastolikMin;
        (*l).contents[idx].tekananDiastolikMax = diastolikMax;
        (*l).contents[idx].detakJantungMin = detakMin;
        (*l).contents[idx].detakJantungMax = detakMax;
        (*l).contents[idx].saturasiOksigenMin = oksigenMin;
        (*l).contents[idx].saturasiOksigenMax = oksigenMax;
        (*l).contents[idx].kadarGulaDarahMin = kadarGulaMin;
        (*l).contents[idx].kadarGulaDarahMax = kadarGulaMax;
        (*l).contents[idx].beratBadanMin = beratMin;
        (*l).contents[idx].beratBadanMax = beratMax;
        (*l).contents[idx].tinggiBadanMin = tinggiMin;
        (*l).contents[idx].tinggiBadanMax = tinggiMax;
        (*l).contents[idx].kadarKolesterolMin = kolesterolMin;
        (*l).contents[idx].kadarKolesterolMax = kolesterolMax;
        (*l).contents[idx].trombositMin = trombositMin;
        (*l).contents[idx].trombositMax = trombositMax;
        idx++;
        (*l).nEff += 1;
    } 
    
    else
    {
        fclose(file);
        printf("Maaf terjadi kesalahan. Ternyata file kosong!\n");
        return;
    }

    while ((fgets(line, sizeof(line), file)))
    {
        int id;
        char namaPenyakit[MAX_NAME];
        int sistolikMin, sistolikMax;
        int diastolikMin, diastolikMax;
        int detakMin, detakMax;
        int kadarGulaMin, kadarGulaMax;
        int tinggiMin, tinggiMax;
        int kolesterolMin, kolesterolMax;
        int trombositMin, trombositMax;
        float suhuMin, suhuMax;
        float oksigenMin, oksigenMax;
        float beratMin, beratMax;
        parsing(line, "isffiiiiiiffiiffiiiiii", 22, &id, namaPenyakit, &suhuMin, &suhuMax, &sistolikMin, &sistolikMax, &diastolikMin, &diastolikMax, &detakMin, &detakMax, &oksigenMin, &oksigenMax, &kadarGulaMin, &kadarGulaMax, &beratMin, &beratMax, &tinggiMin, &tinggiMax, &kolesterolMin, &kolesterolMax, &trombositMin, &trombositMax);
        (*l).contents[idx].id = id;
        strcpy((*l).contents[idx].namaPenyakit, namaPenyakit);
        (*l).contents[idx].suhuTubuhMin = suhuMin;
        (*l).contents[idx].suhuTubuhMax = suhuMax;
        (*l).contents[idx].tekananSistolikMin = sistolikMin;
        (*l).contents[idx].tekananSistolikMax = sistolikMax;
        (*l).contents[idx].tekananDiastolikMin = diastolikMin;
        (*l).contents[idx].tekananDiastolikMax = diastolikMax;
        (*l).contents[idx].detakJantungMin = detakMin;
        (*l).contents[idx].detakJantungMax = detakMax;
        (*l).contents[idx].saturasiOksigenMin = oksigenMin;
        (*l).contents[idx].saturasiOksigenMax = oksigenMax;
        (*l).contents[idx].kadarGulaDarahMin = kadarGulaMin;
        (*l).contents[idx].kadarGulaDarahMax = kadarGulaMax;
        (*l).contents[idx].beratBadanMin = beratMin;
        (*l).contents[idx].beratBadanMax = beratMax;
        (*l).contents[idx].tinggiBadanMin = tinggiMin;
        (*l).contents[idx].tinggiBadanMax = tinggiMax;
        (*l).contents[idx].kadarKolesterolMin = kolesterolMin;
        (*l).contents[idx].kadarKolesterolMax = kolesterolMax;
        (*l).contents[idx].trombositMin = trombositMin;
        (*l).contents[idx].trombositMax = trombositMax;
        idx++;
        (*l).nEff += 1;
    }

    fclose(file);
    return;
}

void readFileObat(ListObat *l)
{
    createListObat(l);
    FILE *file = fopen("file/obat.csv", "r");

    char line[MAX_LINE_LENGTH];
    
    // Pengecekan apakah file ada atau tidak
    if (!(file)) 
    {
        printf("Maaf terjadi kesalahan. File Obat tidak ditemukan!\n");
        return;
    }

    // Skip header dari file dan mengecek apakah file kosong
    if (!(fgets(line, sizeof(line), file))) 
    {
        fclose(file);
        printf("Maaf terjadi kesalahan. Ternyata file kosong!\n");
        return;
    }
    
    if ((fgets(line, sizeof(line), file)))
    {
        int id;
        char namaObat[MAX_NAME];
        parsing(line, "is", 2, &id, namaObat);
        strcpy((*l).contents[id].namaObat, namaObat);
        (*l).contents[id].obatID = id;
        (*l).nEff += 1;
    } 
    
    else
    {
        fclose(file);
        printf("Maaf terjadi kesalahan. Ternyata file kosong!\n");
        return;
    }

    while ((fgets(line, sizeof(line), file)))
    {
        int id;
        char namaObat[MAX_NAME];
        parsing(line, "is", 2, &id, namaObat);
        strcpy((*l).contents[id].namaObat, namaObat);
        (*l).contents[id].obatID = id;
        (*l).nEff += 1;
    }

    fclose(file);
    return;
}

void readFileObatPenyakit(ListObatPenyakit *l)
{
    createListObatPenyakit(l);
    FILE *file = fopen("file/obat_penyakit.csv", "r");

    char line[MAX_LINE_LENGTH];
    int idx = 0;
    
    // Pengecekan apakah file ada atau tidak
    if (!(file)) 
    {
        printf("Maaf terjadi kesalahan. File Obat Penyakit tidak ditemukan!\n");
        return;
    }

    // Skip header dari file dan mengecek apakah file kosong
    if (!(fgets(line, sizeof(line), file))) 
    {
        fclose(file);
        printf("Maaf terjadi kesalahan. Ternyata file kosong!\n");
        return;
    }
    
    if ((fgets(line, sizeof(line), file)))
    {
        int idObat, idPenyakit, urutan;
        parsing(line, "iii", 3, &idObat, &idPenyakit, &urutan);
        (*l).contents[idx].obatID= idObat;
        (*l).contents[idx].penyakitID = idPenyakit;
        (*l).contents[idx].urutanMinum = urutan;
        idx++;
        (*l).nEff += 1;
    } 
    
    else
    {
        fclose(file);
        printf("Maaf terjadi kesalahan. Ternyata file kosong!\n");
        return;
    }

    while ((fgets(line, sizeof(line), file)))
    {
        int idObat, idPenyakit, urutan;
        parsing(line, "iii", 3, &idObat, &idPenyakit, &urutan);
        (*l).contents[idx].obatID= idObat;
        (*l).contents[idx].penyakitID = idPenyakit;
        (*l).contents[idx].urutanMinum = urutan;
        idx++;
        (*l).nEff += 1;
    }

    fclose(file);
    return;
}


void readDigits(FILE *input, int *number, int *chr){
    *chr = fgetc(input);
    *number = 0;
    
    while(*chr == ' ' || *chr == '\n'){ /* lewati jika ada whitespace */
        *chr = fgetc(input);
    }

    while(*chr >= 48 && *chr <= 57){ /* baca setiap digit */
        *number = *number * 10 + (*chr - '0');
        *chr = fgetc(input);
    }
}

void readConfig(Matrix *M, ListInventory *Li){
    FILE *config = fopen("file/config.txt", "r");
    if(config == NULL) printf("oh nyo! there is no file!\nwe are deeply sorry for this inconvenience >w<'\n");
    int number, chr;
    readDigits(config, &number, &chr);
    int row = number;
    readDigits(config, &number, &chr);
    int col = number;
    readDigits(config, &number, &chr);
    int capacityDalam = number;
    readDigits(config, &number, &chr);
    int capacityLuar = number;
    createMatrix(row, col, M, capacityDalam, capacityLuar);
    createListInventory(Li);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            M->data[i][j].kapasitas = capacityDalam;
            M->data[i][j].kapasitasAntrian = capacityLuar;
            int k = 0;
            readDigits(config, &number, &chr);
            if(number > 0){ 
                M->data[i][j].idDoktor = number;
            }
            else M->data[i][j].idDoktor = MARK_INT;
            createQueue(&M->data[i][j].antriPasienDalam);
            createQueue(&M->data[i][j].antriPasienLuar);
            while(k < capacityDalam && chr == ' '){
                readDigits(config, &number, &chr);
                addQueue(&M->data[i][j].antriPasienDalam, number);
                k++;
            } 
            while(k == capacityDalam && k < capacityDalam + capacityLuar && chr == ' '){
                readDigits(config, &number, &chr);
                addQueue(&M->data[i][j].antriPasienLuar, number);
                k++;
            } 
        }
    }
    readDigits(config, &number, &chr);
    int inventory = number;
    for(int i = 0; i < inventory; i++){
        readDigits(config, &number, &chr);
        int j = number;
        int k = 1;
        Li->contents[j].contents[0] = MARK_USED;
        while(chr == ' '){
            readDigits(config, &number, &chr);
            Li->contents[j].contents[k] = number;
            k++;
        }
    }
    fclose(config);
}