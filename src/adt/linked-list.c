#include "linked-list.h"

Address newNode(ElType val){
    Address L = (Address) malloc(sizeof(Node));
    if (L != NULL){
        INFO(L) = val;
        NEXT(L) = NULL;
    }
    return L;
}

void createLinkedList (Address *L){
    *L = NULL;
}

boolean isLinkedListEmpty (Address L){
    return (L == NULL);
}

int lengthLinkedList (Address L){
    int len = 0;
    while (L != NULL){
        len += 1;
        L = NEXT(L);
    }
    return len;
}

void insertFirst(Address *L, ElType val){
    Address new = newNode(val);
    if (new != NULL){
        NEXT(new) = *L;
        *L = new;
    }
}

void insertLast(Address *L, ElType val){
    Address new = newNode(val);
    if (new != NULL){
        if (isLinkedListEmpty(*L)){
            *L = new;
        }else{
            Address Ltemp = *L;
            while (NEXT(Ltemp) != NULL)
            {
                Ltemp = NEXT(Ltemp);
            }
            NEXT(Ltemp) = new;
        }
    }
}