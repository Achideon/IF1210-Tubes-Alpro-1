#include "map-obat-penyakit.h"

void createMapObatPenyakit (ListObat l1, ListObatPenyakit l2, MapObatPenyakit *m) {
    m->length = 0;

    for (int i = 0; i < l2.nEff; i++) {
        int penyakitID = l2.contents[i].penyakitID;
        int obatID = l2.contents[i].obatID;
        int urutan = l2.contents[i].urutanMinum - 1;
        
        // Cek apakah penyakit sudah ada di list atau belum
        int idx = -1;
        for (int j = 0; j < m->length; j++) {
            if (m->contents[j].keyPenyakit == penyakitID) {
                idx = j;
                break;
            }
        }
        
        // Apabila tidak ada (bernilai -1), maka program akan mencari penyakitID yang sesuai
        if (idx == -1) {
            idx = m->length++;
            m->contents[idx].keyPenyakit = penyakitID;
            m->contents[idx].valueListID.nEff = 0;
        }
        
        // Append atau tambahkan obat ke list
        m->contents[idx].valueListID.contents[urutan] = obatID;
        strcpy(m->contents[idx].valueListName[urutan],getNameByObatID(&l1, obatID));
        m->contents[idx].valueListID.nEff++;
        
    }
}

ListValue mapGetListObatID (MapObatPenyakit *m, int keyPenyakit) {
    for (int i = 0; i < m->length; i++) {
        if (m->contents[i].keyPenyakit == keyPenyakit) {
            ListValue *l = &m->contents[i].valueListID;
            return *l;
        }
    }

    ListValue empty;
    empty.nEff = 0;
    return empty;
}

char (* mapGetListObatName(MapObatPenyakit *m, int keyPenyakit))[MAX_NAME] {
    for (int i = 0; i < m->length; i++) {
        if (m->contents[i].keyPenyakit == keyPenyakit) {
            return m->contents[i].valueListName; 
    }
    printf("Nama Obat tidak ada di bagian ini!");
    return NULL;
}

char * mapObatNameByID(MapObatPenyakit *m, int keyPenyakit, int obatID){
    for (int i = 0; i < m->length; i++) {
        if (m->contents[i].keyPenyakit == keyPenyakit) {
            for(int j = 0; j < 20; j++){
                if(m->contents[i].valueListID.contents[j] = obatID) return m->contents[i].valueListName[j];
            }
        }
    }
    printf("Nama Obat tidak ada di bagian ini!");
    return NULL;
}

char * mapObatNameByUrutan(MapObatPenyakit *m, int keyPenyakit, int urutan){
    for (int i = 0; i < m->length; i++) {
        if (m->contents[i].keyPenyakit == keyPenyakit) {
                return m->contents[i].valueListName[urutan];
            }
        }
    }
    printf("Nama Obat tidak ada di bagian ini!");
    return NULL;
}

char * getNameByObatID (ListObat *l, int obatID){
    if ((*l).contents[obatID].obatID == obatID) return (*l).contents[obatID].namaObat;
    printf("Obat tidak ada di database!");
    return MARK_STR;
}

int getPenyakitIDByName (ListPenyakit *l, char * name){
    for (int i = 0; i < (*l).nEff; i++){
        if (!strcmp((*l).contents[i].namaPenyakit, name)) return (*l).contents[i].id;
    }
    printf("Obat tidak ada di database!");
    return MARK_INT;
}