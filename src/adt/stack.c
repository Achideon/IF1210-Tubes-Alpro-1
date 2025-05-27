#include "stack.h"
#include <stdio.h>


//ListPerut
void createListPerut(ListPerut *l) {
    for (int i = 1; i < MAX_USERS; i++) {
        (*l).contents[i].top = IDX_UNDEF;
        for (int j = 0; j < STACK_CAPACITY; j++) {
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
    return ((*l).contents[userID].top == IDX_UNDEF);
}

//StackIsiDalamPerut
void pushObat(ListPerut *l, int userID, int obatID) {
    if ((*l).contents[userID].top == STACK_CAPACITY - 1) {
        printf("Stack perut penuh untuk user %d!\n", userID);
        return;
    }
    
    (*l).contents[userID].top++;
    (*l).contents[userID].contents[(*l).contents[userID].top] = obatID;
    
    if ((*l).contents[userID].top == 0) { // Jika sebelumnya kosong
        (*l).nEff++;
    }
}

void popObat(ListPerut *l, int userID, int *outObatID) {
    if ((*l).contents[userID].top == IDX_UNDEF) {
        printf("Stack perut kosong untuk user %d!\n", userID);
        *outObatID = MARK_OBAT;
        return;
    }
    
    *outObatID = (*l).contents[userID].contents[(*l).contents[userID].top];
    (*l).contents[userID].contents[(*l).contents[userID].top] = MARK_OBAT;
    (*l).contents[userID].top--;
    
    if ((*l).contents[userID].top == IDX_UNDEF) {
        (*l).nEff--;
    }
}

void peekObat(ListPerut l, int userID, int *outObatID) {
    if (l.contents[userID].top == IDX_UNDEF) {
        printf("Stack perut kosong untuk user %d!\n", userID);
        *outObatID = MARK_OBAT;
        return;
    }
    
    *outObatID = l.contents[userID].contents[l.contents[userID].top];
}
