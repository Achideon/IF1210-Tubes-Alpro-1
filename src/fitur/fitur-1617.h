#ifndef MINUM_OBAT_H
#define MINUM_OBAT_H

#include "../adt/stack.h"
#include "../adt/inventory-list.h"
#include "../adt/map-obat-penyakit.h"
#include <stdio.h>

void minumObat(ListInventory *inventory, ListPerut *perut, MapObatPenyakit *mapObat, int userID);
//F16: Prosedur untuk meminum obat dari inventory ke perut
void minumPenawar(ListInventory *inventory, ListPerut *perut, MapObatPenyakit *mapObat, int userID);
//F17: Prosedur untuk mengeluarkan obat dari perut kembali ke inventory

#endif