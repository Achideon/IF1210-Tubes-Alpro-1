#include "inventory-list.h"


/* ********** OPERASI DASAR LIST PENGGUNA ********** */

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : Create List kosong  */
void createListInventory(ListInventory *l){
    for (int i = 1; i < MAX_USERS; i++) 
    {
        (*l).contents[i].contents[0] = MARK_INT;
        for (int j = 1; j < 20; j++)
        {
            (*l).contents[i].contents[i] = MARK_USED;
        } 
        (*l).contents[i].nEff = 0;
    }
    (*l).nEff = 0;
}

/* ********** SELEKTOR ********** */
/* *** Test List kosong *** */
boolean isListInventoryEmpty(ListInventory l){
    return ((l).nEff == 0);
}

/* *** Test List penuh *** */
boolean isListInventoryFull(ListInventory l){
    return ((l).nEff == MAX_USERS - 1);
}

boolean isInventoryEmpty(ListInventory l, int userID){
    for (int i=0; i<l.nEff; i++){
        if(l.contents[i].contents[0] == userID){
            return l.contents[i].nEff == 0;
        }
    }
}

void useInventory(ListInventory *l, int userID, int obatID, int *outObatID){
    int idxUser;
    for (int i=0; i<(*l).nEff; i++){
        if((*l).contents[i].contents[0] == userID){
            idxUser = i;
        }
    }

    for (int i = 1; i <= (*l).contents[idxUser].nEff; i++)
    {
        if ((*l).contents[idxUser].contents[i]==obatID) 
        {
            *outObatID = obatID;
            for (int j = i; j < (*l).contents[idxUser].nEff - 1; j++) 
            {
                (*l).contents[idxUser].contents[j] = (*l).contents[idxUser].contents[j + 1];
            }
            (*l).contents[idxUser].nEff--;
        }
    }
}

void insertInventory(ListInventory *l, int userID, int obatID){
    if ((*l).nEff == 0)
    {
        (*l).contents[0].contents[0] = userID;
        (*l).contents[0].contents[1] = obatID;
        (*l).contents[0].nEff++;
        (*l).nEff++;
    }
    else
    {
        int now = -999;
        for (int i = 0; i < (*l).nEff; i++){
            if (l->contents[i].contents[0] == userID) now = i;
        }
        if (now == -999){
            now = l->nEff;
            (*l).contents[now].contents[0] = userID;
            (*l).contents[now].nEff = 0;
        }
        int id = (*l).contents[now].nEff + 1;
        (*l).contents[now].nEff++;
        (*l).contents[now].contents[id] = obatID;
    }
}

boolean isUserInventoryEmpty(ListInventory *l, int userID){
    return ((*l).contents[userID].nEff == 0);
}

int getLastIdxInventory(ListInventory l, int userID){
    return ((l).contents[userID].nEff);
}