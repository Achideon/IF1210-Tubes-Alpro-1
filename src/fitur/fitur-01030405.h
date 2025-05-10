#ifndef fitur2_H
#define fitur2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../adt/user-list.h"

// gcc user-list.c fitur-01030405.c -o p
void login(ListUser *l, int *currentID);

void logout(ListUser *l, int *currentID);

void lupaPassword(ListUser *l, int *currentID);

void menuHelp(ListUser *l, int *currentID);

#endif