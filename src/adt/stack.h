#ifndef STACK_PERUT_H
#define STACK_PERUT_H

#include "../utils/boolean.h"
#include "inventory-list.h"

#define STACK_CAPACITY 20
#define MAX_USERS 300
#define IDX_UNDEF -1
#define MARK_OBAT -1

typedef struct {
    int contents[STACK_CAPACITY];
    int top;
} StackObat;

typedef struct {
    StackObat contents[MAX_USERS];
    int nEff;
} ListPerut;

// ListPerut
void createListPerut(ListPerut *l);
/* I.S.: l sembarang */
/* F.S.: l berisi stack kosong di setiap user (top = IDX_UNDEF, semua contents = MARK_OBAT), nEff = 0 */

boolean isListPerutEmpty(ListPerut l);
/* I.S.: l terdefinisi */
/* F.S.: mengembalikan true jika nEff == 0 (tidak ada user dengan isi perut) */

boolean isListPerutFull(ListPerut l);
/* I.S.: l terdefinisi */
/* F.S.: mengembalikan true jika nEff == MAX_USERS - 1 (jumlah user maksimum) */

boolean isUserPerutEmpty(ListPerut *l, int userID);
/* I.S.: l terdefinisi, userID valid */
/* F.S.: mengembalikan true jika stack perut user dengan ID tertentu kosong (top == IDX_UNDEF) */

boolean isUserPerutFull(ListPerut *l, int userID);
/* I.S.: l terdefinisi, userID valid */
/* F.S.: mengembalikan true jika stack perut user dengan ID tertentu penuh (top == STACK_CAPACITY-1) */

// StackIsiDalamPerut
void pushObat(ListPerut *l, int userID, int obatID);
/* I.S.: l terdefinisi, userID valid, obatID valid */
/* F.S.: obatID ditambahkan ke stack perut user dengan ID userID, nEff bertambah jika sebelumnya kosong */

void popObat(ListPerut *l, int userID, int *outObatID);
/* I.S.: l terdefinisi, userID valid, outObatID terdefinisi */
/* F.S.: outObatID berisi obat paling atas yang dihapus, nEff berkurang jika stack menjadi kosong */

void topObat(ListPerut l, int userID, int *outObatID);
/* I.S.: l terdefinisi, userID valid, outObatID terdefinisi */
/* F.S.: outObatID berisi obat paling atas tanpa menghapus */
#endif
