#ifndef FITUR0708_H
#define FITUR0708_H
#include<stdio.h>
#include<string.h>
#include "../adt/user-list.h"

void sortByNama(ListUser *l, int sort);

void sortByID(ListUser *l, int sort);

ListUser sortByRole(ListUser l1, int role);

ListUser sortByPenyakit(ListUser l1, int sortby, int sort, char* penyakit);

void printSpace(int n);

void printListUser(ListUser l, int role);

void printUser(ListUser l, int index, int role);

void lihatUser(ListUser l, int role, int currentID);

void cariUser(ListUser l, int role, int currentID);

#endif
