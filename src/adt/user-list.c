#include "user-list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ********** OPERASI DASAR LIST PENGGUNA ********** */

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : Create List kosong  */
void createUser(User *user)
{
    user->id = MARK_INT;
    strcpy(user->username, MARK_STR);
    strcpy(user->riwayatPenyakit, MARK_STR);
    strcpy(user->password, MARK_STR);
    strcpy(user->role, MARK_STR);
    user->suhuTubuh = MARK_F;
    user->tekananDiastolik = MARK_INT;
    user->tekananSistolik = MARK_INT;
    user->detakJantung = MARK_INT;
    user->saturasiOksigen = MARK_F;
    user->kadarGulaDarah = MARK_INT;
    user->beratBadan = MARK_F;
    user->tinggiBadan = MARK_INT;
    user->kadarKolesterol = MARK_INT;
    user->trombosit = MARK_INT;
}

void createListUser(ListUser *l)
{
    for(int i = 0; i < MAX_USERS; i++)
    {
        ID(*l, i) = MARK_INT;
        strcpy(USERNAME(*l, i), MARK_STR);
        strcpy(PENYAKIT(*l, i), MARK_STR);
        strcpy(PASSWORD(*l, i), MARK_STR);
        strcpy(ROLE(*l, i), MARK_STR);
        SUHU(*l, i) = MARK_F;
        TSISTOLIK(*l, i) = MARK_INT;
        DSISTOLIK(*l, i) = MARK_INT;
        DETAK(*l, i) = MARK_INT;
        OKSIGEN(*l, i) = MARK_F;
        KADARGULA(*l, i) = MARK_INT;
        BERAT(*l, i) = MARK_F;
        TINGGI(*l, i) = MARK_INT;
        KOLESTEROL(*l, i) = MARK_INT;
        TROMBOSIT(*l, i)= MARK_INT;
    }
    (*l).nEff = 0;
    (*l).maxID = -999; // Nilai pasti terganti apabila file sedang dibaca dan terdapat isi
}
/* ********** SELEKTOR ********** */

/* *** Test List kosong *** */
boolean isListUserEmpty(ListUser l)
{
    return (l.nEff == 0);
}
/* *** Test List penuh *** */
boolean isListUserFull(ListUser l)
{
    return (l.nEff == MAX_USERS);
}

int getLastIdx(ListUser l)
{
    return (l.nEff-1);
}

/* ********** OPERASI PRIMITIF LAINNYA ********** */
void setPassword(ListUser *l, int currentID, char * password)
{
    int idx = userSearchByID(*l,currentID);
    strcpy(PASSWORD(*l, idx), password);
}

void setRole(ListUser *l, int currentID, char * role){
    int idx = userSearchByID(*l,currentID);
    strcpy(ROLE(*l, idx), role);
}

void setRiwayatPenyakit(ListUser *l, int currentID, char * namaPenyakit){
    int idx = userSearchByID(*l,currentID);
    strcpy(PENYAKIT(*l,idx), namaPenyakit);
}


/* ********** OPERASI DASAR PENGGUNA ********** */

void addNewUser(ListUser *l, char * username, char * password)
{
    if (!(isListUserFull(*l)))
    {
        int lastIdx = nEff(*l) + 1;
        ID(*l, lastIdx) = (*l).maxID + 1;
        strcpy(USERNAME(*l, lastIdx), username);
        strcpy(PENYAKIT(*l, lastIdx), MARK_STR);
        strcpy(PASSWORD(*l, lastIdx), password);
        strcpy(ROLE(*l, lastIdx), MARK_STR);
        SUHU(*l, lastIdx) = MARK_F;
        TSISTOLIK(*l, lastIdx) = MARK_INT;
        DSISTOLIK(*l, lastIdx) = MARK_INT;
        DETAK(*l, lastIdx) = MARK_INT;
        OKSIGEN(*l, lastIdx) = MARK_F;
        KADARGULA(*l, lastIdx) = MARK_INT;
        BERAT(*l, lastIdx) = MARK_F;
        TINGGI(*l, lastIdx) = MARK_INT;
        KOLESTEROL(*l, lastIdx) = MARK_INT;
        TROMBOSIT(*l, lastIdx)= MARK_INT;
        nEff(*l)++;
        MAX(*l)++;
    }
    else
    {
        printf("Database penuh!");
    }
}

int getIDByUsername(ListUser l, char * username)
{
    for(int i = 0; i < nEff(l); i++)
    {
        if (!(strcmp(USERNAME(l,i), username))) return ID(l,i);
    }
    return IDX_UNDEF;
}

char * getUsernameByID(ListUser l, int currentID)
{
    int idx = userSearchByID(l,currentID);
    char* username = malloc(100);
    strcpy(username, USERNAME(l, idx));
    return (username);
}

char * getRoleByID(ListUser l, int currentID)
{
    int idx = userSearchByID(l,currentID);
    char* username = malloc(100);
    strcpy(username, ROLE(l, idx));
    return (username);
}

char * getRiwayatByID(ListUser l, int currentID)
{
    int idx = userSearchByID(l,currentID);
    char* riwayat = malloc(100);
    strcpy(riwayat, PENYAKIT(l, idx));
    return (riwayat);
}

boolean isUserLoggedIn(int currentID)
{
    return ((currentID != MARK_INT));
}

boolean isValidUsername(ListUser l, char * username)
{
    for(int i = 0; i < nEff(l); i++)
    {
        if (!(strcmp(USERNAME(l,i), username))) return true;
    }
    return false;
}

boolean isValidPassword(ListUser l, char * password, int currentID)
{
    int id = userSearchByID(l,currentID);
    if (!(strcmp(PASSWORD(l,id), password))) return true;
    return false;
}

boolean isUniqueUser(ListUser l, char * username)
{
    for(int i = 0; i < nEff(l); i++)
    {
        if (!(strcasecmp(USERNAME(l,i), username))) return false;
    }
    return true;
}

int userSearchByID(ListUser l, int x){
    int low = 0, high = l.nEff;
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
    for(int i = 0; i <= l.nEff; i++){
        if(!strcasecmp(l.contents[i].username, x)){
            return i;
        }
    }
    return MARK_INT;
}
