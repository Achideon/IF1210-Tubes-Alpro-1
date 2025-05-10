#include "fitur-021018.h"

/*Realisasi Prosedur REGISTER atau Fitur F02*/
void regist(ListUser *l, int currentId){
    if (!(isUserLoggedIn(currentId))){
        char username[MAX_USERNAME_LENGTH];
        char pass[MAX_PASSWORD_LENGTH];
        printf("Username: "); 
        scanf("%s",username); /*Memasukkan username akun yang ingin didaftarkan dan username tidak boleh sama.*/
        printf("Password: ");
        scanf("%s",pass);  /*Memasukkan password dari akun yang ingin didaftarkan.*/
        if (!(isUniqueUser(*l, username))){
            printf("Registrasi pasien gagal! %s dengan nama %s sudah terdaftar.\n", getRoleByID(*l,getIDByUsername(*l, username)), username); 
            /*Sudah ada pasien yang teregristasi dengan nama yang sama.*/
        }else{
            addNewUser(l, username, pass); /*Menambah akun pasien baru*/
            setRole(l, getIDByUsername(*l, username), "Pasien");
            /*Setelah berhasil mendaftar, pasien akan otomatis terdaftar sebagai pasien*/
        }
        printf("\n");
    } else {
        return;
    }
}

/*Realisasi Prosedur TAMBAHDOKTER atau Fitur F10*/
void addDoctor(ListUser *l, int currentId){
    if (strcmp(getRoleByID(*l,currentId), "Manager") == 0){
        char username[MAX_USERNAME_LENGTH];
        char pass[MAX_PASSWORD_LENGTH];
        printf("Username: ");
        scanf("%s",username);
        printf("Password: ");
        scanf("%s",pass);
        if (!(isUniqueUser(*l,username))){
            printf("Dokter %s sudah ada", username);
        }else{
            addNewUser(l,username,pass);
            /*Menambah akun dokter baru*/
            setRole(l, getIDByUsername(*l, username), "Dokter");
            /*Setelah berhasil mendaftar, dokter akan otomatis terdaftar sebagai dokter*/
        }
        printf("\n");
    }else {
        return;
    }
}

/*Realisasi Prosedur ASSIGNDOKTER*/
void assignDoctor(ListUser *l, int currentId, Matrix *M){
    if (strcmp(getRoleByID(*l,currentId), "Manager") == 0){
        char username[MAX_USERNAME_LENGTH];
        char ruang[MAX_PASSWORD_LENGTH];
        printf("Username: ");
        scanf("%s",username);
        printf("Ruangan: ");
        scanf("%s",ruang);
        if ((isDoctorAssigned(*M, getIDByUsername(*l,username))) && (isRoomAssigned(*M,ruang))){
            /*Jika dokter sudah di assign ke ruangan lain dan ruangan yang dituju sudah ada dokter lain.*/
            printf("Dokter %s sudah menempati ruangan %s\n", username, getRoomByDoctor(*M,getIDByUsername(*l,username)));
            printf("Ruangan %s juga sudah ditempati dokter %s\n",ruang,getDoctorByRoom(*M,ruang,*l));
        }
        else if (isDoctorAssigned(*M, getIDByUsername(*l,username))){
            /*Jika dokter sudah diassign*/
            printf("Doker %s sudah diassign ke ruangan %s!\n",username,getRoomByDoctor(*M,getIDByUsername(*l,username)));
        }else if (isRoomAssigned(*M,ruang)){
            printf("Dokter %s sudah menempati ruangan %s\n", getDoctorByRoom(*M,ruang,*l),ruang);
            printf("Silahkan cari ruangan lain untuk dokter %s.\n",username);
        }else{
            /*Jika ruangan kosong dan dokter belum di assign ke manapun.*/
            int row,col;
            char rowf;
            sscanf(ruang, "%c%d", &rowf,&col);
            row = rowf - 'A';
            col -= 1;
            M->data[row][col].idDoktor = getIDByUsername(*l,username);
            printf("Dokter %s sudah diassign ke ruangan %s\n",username,ruang);
        }
        printf("\n");
        /*tercatat di matrix bahwa ada dokter di ruangan tersebut.*/
    }else {
        return;
    }
}

void ext(boolean *kondisi, ListUser l,Matrix m){
    /*Kondisi adalah boolean yang membuat program utama mengulang terus jika bernilai true.*/
    *kondisi = false;
    /*Dengan membuatnya false, maka program utama akan berhenti setelah command ini dijalankan.*/
    /*loop program utama akan berakhir dan selanjutnya, akan ada pertanyaan tentang save file*/
    printf("Apakah anda mau melakukan penyimpanan file yang sudah diubah? (y/n)");
    char save;
    scanf("%c",&save);
    while ((save != 'y') && (save != 'n')){
        scanf("%c",&save);
    }
    if (save == 'y'){
        writeFile_user(l,l.nEff,"user.csv");
        writeFile_config(&m);
    }
    
}
