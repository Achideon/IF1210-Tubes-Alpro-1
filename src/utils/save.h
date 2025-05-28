#ifndef SAVE_H
#define SAVE_H

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../adt/user-list.h"
#include "../adt/matrix-denah.h"
#include "load.h"
#include "write-file.h"

void save(Matrix M, ListUser l);

#endif