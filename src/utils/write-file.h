#ifndef WRITEFILE_H
#define WRITEFILE_H

#include <stdio.h>
#include <stdlib.h>
#include "../adt/user-list.h"
#include "../adt/matrix-denah.h"

void writeFileUser(ListUser l, char* filepath, boolean *status);
/*Menulis file user.csv*/

void writeFileConfig(Matrix *M, char* filepath, boolean *status);
/*Menulis file config.txt*/

#endif
