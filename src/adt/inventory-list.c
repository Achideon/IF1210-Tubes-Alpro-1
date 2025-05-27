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

void useInventory(ListInventory *l, int userID, int obatID, int *outObatID){
    for (int i=1; i<(*l).contents[userID].nEff; i++)
    {
        if ((*l).contents[userID].contents[i]==obatID) 
        {
            *outObatID = obatID;
            for (int j = i; j < (*l).contents[userID].nEff - 1; j++) 
            {
                (*l).contents[userID].contents[j] = (*l).contents[userID].contents[j + 1];
            }
            (*l).contents[userID].nEff--;
        }
    }
}

void insertInventory(ListInventory *l, int userID, int obatID){
    if ((*l).contents[userID].contents[0]==MARK_INT)
    {
        (*l).contents[userID].contents[0] = MARK_USED;
        (*l).contents[userID].contents[1] = obatID;
        (*l).contents[userID].nEff++;
    }
    else
    {
        int id = (*l).contents[userID].nEff + 1;
        (*l).contents[userID].contents[id] = obatID;
    }
}

boolean isUserInventoryEmpty(ListInventory *l, int userID){
    return ((*l).contents[userID].nEff == 0);
}

int getLastIdxInventory(ListInventory l, int userID){
    return ((l).contents[userID].nEff);
}

