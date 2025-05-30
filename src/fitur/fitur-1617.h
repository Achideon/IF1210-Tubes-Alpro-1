#ifndef MINUM_OBAT_H
#define MINUM_OBAT_H

#include "../adt/stack.h"
#include "../adt/inventory-list.h"
#include "../adt/map-obat-penyakit.h"
#include "../adt/user-list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100

void minumObat(ListInventory *inventory, ListPerut *perut, MapObatPenyakit *mapObat, int userID, ListPenyakit *listpenyakit, ListUser listuser);
//F16: Prosedur untuk meminum obat dari inventory ke perut
void minumPenawar(ListInventory *inventory, ListPerut *perut, MapObatPenyakit *mapObat, int userID, ListPenyakit *listpenyakit, ListUser listuser);
//F17: Prosedur untuk mengeluarkan obat dari perut kembali ke inventory

#endif
