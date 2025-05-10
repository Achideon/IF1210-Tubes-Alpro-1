#include <stdio.h>
#include "read-file.h"

void parsing(char *input, char *format, int dataCount, ...){
    va_list args;
    va_start(args, dataCount);
    int idxGet = 0;
    for(int i = 0; i < dataCount; i++){
        char parsedInput[50];
        int idxPut = 0;
        while(input[idxGet] != ',' && input[idxGet] != '\n' && input[idxGet] != '\0'){
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
    FILE *file = fopen("../src/file/user.csv", "r");

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
        int id, sistolik, diastolik, detak, kadarGula, tinggi, kolesterol, ldl, trombosit;
        float suhu, oksigen, berat;
        parsing(line, "issssfiiififiiii", 16, &id, username, password, role, riwayatPenyakit, &suhu, &sistolik, &diastolik, &detak, &oksigen, &kadarGula, &berat, &tinggi, &kolesterol, &ldl, &trombosit);
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
        KOLESTEROLLDL(*l, idxUser) = ldl;
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
        int id, sistolik, diastolik, detak, kadarGula, tinggi, kolesterol, ldl, trombosit;
        float suhu, oksigen, berat;
        parsing(line, "issssfiiififiiii", 16, &id, username, password, role, riwayatPenyakit, &suhu, &sistolik, &diastolik, &detak, &oksigen, &kadarGula, &berat, &tinggi, &kolesterol, &ldl, &trombosit);
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
        KOLESTEROLLDL(*l, idxUser) = ldl;
        TROMBOSIT(*l, idxUser) = trombosit;
        nEff(*l) += 1;
        idxUser++;
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
        *number = *number * 10 + (*chr - 48);
        *chr = fgetc(input);
    }
}

void readConfig(Matrix *M){
    FILE *config = fopen("../src/file/config.txt", "r");
    if(config == NULL) printf("oh nyo! there is no file!\nwe are deeply sorry for this inconvenience >w<'\n");
    int number, chr;
    readDigits(config, &number, &chr);
    int row = number;
    readDigits(config, &number, &chr);
    int col = number;
    readDigits(config, &number, &chr);
    int capacity = number;
    createMatrix(row, col, M, capacity);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            M->data[i][j].kapasitas = capacity;
            int k = 0;
            readDigits(config, &number, &chr);
            if(number > 0){ 
                M->data[i][j].idDoktor = number;
            }
            else M->data[i][j].idDoktor = MARK_INT;
            while(k < capacity && chr != '\n'){
                readDigits(config, &number, &chr);
                addQueue(&M->data[i][j].antriPasien, number);
                k++;
            }
        }
    }
    fclose(config);
}