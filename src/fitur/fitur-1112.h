#include "../adt/map-obat-penyakit.h"
#include "../adt/user-list.h"
#include "../adt/obat-penyakit.h"
#include "../adt/matrix-denah.h"
#include "../adt/inventory-list.h"
#include <stdio.h>
#include <stdlib.h>

/* Implementasi DIAGNOSIS */
void diagnosis(Matrix m, ListPenyakit p, ListUser *l, int currentID);
// Setiap pasien yang sudah  berada di Queue sudah pasti telah melakukan checkup

/* Implementasi NGOBATIN */
void ngobatin(Matrix m, MapObatPenyakit mOP, ListPenyakit p, ListInventory *inv, ListUser *l, int currentID);

/* ASCII Art untuk Obat */
void printObat();
