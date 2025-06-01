#include "stack.h"
#include <stdio.h>

void createListPerut(ListPerut *l) {
    for (int i = 0; i < MAX_USERS; i++) {
        (*l).contents[i].contents[0] = MARK_OBAT;  
        (*l).contents[i].top = IDX_UNDEF;                  
        for (int j = 1; j < STACK_CAPACITY; j++) {
            (*l).contents[i].contents[j] = MARK_OBAT;
        }
    }
    (*l).nEff = 0;
}

boolean isListPerutEmpty(ListPerut l) {
    return (l.nEff == 0);
}

boolean isListPerutFull(ListPerut l) {
    return (l.nEff == MAX_USERS - 1);
}

boolean isUserPerutEmpty(ListPerut *l, int userID) {
    for (int i = 0; i < l->nEff; i++) {
        if ((*l).contents[i].contents[0] == userID) {
            return ((*l).contents[i].top == 0);
        }
    }
    return true;  
}

boolean isUserPerutFull(ListPerut *l, int userID) {
    for (int i = 0; i < l->nEff; i++) {
        if ((*l).contents[i].contents[0] == userID) {
            return ((*l).contents[i].top == STACK_CAPACITY - 1);
        }
    }
    return false;  
}

void addUserPerut(ListPerut *l, int userID){
    int n = l->nEff;
    l->contents[n].contents[0] = userID;
    l->contents[n].top = 0;
    l->nEff++;
}

void pushObat(ListPerut *l, int userID, int obatID) {
    if(l->nEff == 0){
        (*l).contents[0].contents[0] = userID;
        (*l).contents[0].contents[1] = obatID;
        (*l).contents[0].top = 1;
        (*l).nEff++;
        return;
    }
    for (int i = 0; i < l->nEff; i++) {
        if ((*l).contents[i].contents[0] == userID) {
            if ((*l).contents[i].top == STACK_CAPACITY - 1) { //perut penuh
                return;
            }
            (*l).contents[i].top++;
            (*l).contents[i].contents[(*l).contents[i].top] = obatID; //memasukkan obat ke index paling atas    
            return;
        }
    }
    (*l).contents[(*l).nEff].contents[0] = userID;
    (*l).contents[(*l).nEff].contents[1] = obatID;
    (*l).contents[(*l).nEff].top = 1;
    (*l).nEff++;
}

void popObat(ListPerut *l, int userID, int *outObatID) {
    for (int i = 0; i < MAX_USERS; i++) {
        if ((*l).contents[i].contents[0] == userID) {
            if ((*l).contents[i].top == 0) { //perut kosong
                *outObatID = MARK_OBAT;
                return;
            }
            
            *outObatID = (*l).contents[i].contents[(*l).contents[i].top];
            (*l).contents[i].contents[(*l).contents[i].top] = MARK_OBAT;
            (*l).contents[i].top--;
            
            if ((*l).contents[i].top == 0) {
                (*l).contents[i].contents[0] = MARK_OBAT;
                (*l).nEff--;
            }
            return;
        }
    }
    *outObatID = MARK_OBAT;
}

void topObat(ListPerut l, int userID, int *outObatID) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (l.contents[i].contents[0] == userID) {
            if (l.contents[i].top == 0) {
                *outObatID = MARK_OBAT;
                return;
            }
            *outObatID = l.contents[i].contents[l.contents[i].top];
            return;
        }
    }
    *outObatID = MARK_OBAT;
}
