#ifndef WRITEFILE_H
#define WRITEFILE_H

#include <stdio.h>
#include <stdlib.h>
#include "../adt/user-list.h"
#include "../adt/matrix-denah.h"

void writeFile_user(ListUser l, char* filepath, boolean *status);
/*Menulis file user.csv*/

void writeFile_config(Matrix *M, char* filepath, boolean *status);
/*Menulis file config.txt*/

#endif
