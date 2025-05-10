#ifndef WRITEFILE_H
#define WRITEFILE_H

#include <stdio.h>
#include <stdlib.h>
#include "user-list.h"
#include "matrix-denah.h"

void writeFile_user(ListUser l, int nEff, const char* filename);
/*Menulis file user.csv*/

void writeFile_config(const Matrix *M);
/*Menulis file config.txt*/

#endif