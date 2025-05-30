#ifndef WRITEFILE_H
#define WRITEFILE_H

#include <stdio.h>
#include <stdlib.h>
#include "../adt/user-list.h"
#include "../adt/matrix-denah.h"
#include "../adt/inventory-list.h"
#include "../adt/stack.h"

void writeFileUser(ListUser l, char* filepath, boolean *status);
/*Menulis file user.csv*/

void writeFileConfig(Matrix *M, ListInventory *Li, ListPerut *Lp, char* filepath, boolean *status);
/*Menulis file config.txt*/

#endif
