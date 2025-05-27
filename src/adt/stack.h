#ifndef STACK_PERUT_H
#define STACK_PERUT_H

#include "../utils/boolean.h"

#define STACK_CAPACITY 20
#define MAX_USERS 300
#define IDX_UNDEF -1
#define MARK_OBAT -1

typedef struct {
    int contents[STACK_CAPACITY];
    int top;
} StackPerut;

typedef struct {
    StackPerut contents[MAX_USERS];
    int nEff;
} ListPerut;

//ListPerut
void createListPerut(ListPerut *l);
boolean isListPerutEmpty(ListPerut l);
boolean isListPerutFull(ListPerut l);
boolean isUserPerutEmpty(ListPerut *l, int userID);

//StackIsiDalamPerut
void pushObat(ListPerut *l, int userID, int obatID);
void popObat(ListPerut *l, int userID, int *outObatID);
void peekObat(ListPerut l, int userID, int *outObatID);

#endif
