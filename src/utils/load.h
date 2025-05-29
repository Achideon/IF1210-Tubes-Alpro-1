#ifndef LOAD_H
#define LOAD_H

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "read-file.h"
#include "../adt/user-list.h"
#include "../adt/matrix-denah.h"
#include "../adt/inventory-list.h"
#include "../adt/stack.h"

int isFolderExist(char *path);

void load(Matrix *M, ListUser *l, ListInventory *li, ListPerut *lp, boolean *status);

#endif
