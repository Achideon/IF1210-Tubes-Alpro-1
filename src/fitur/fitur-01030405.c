#include "fitur-01030405.h"

void login(ListUser *l, int *currentID){
    if(isUserLoggedIn(*currentID) == 1){
        printf("Anda sudah login!\n\n");
    }else{
        char username[MAX_USERNAME_LENGTH];
        char password[MAX_PASSWORD_LENGTH];
        int i, found = 0;
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);
        while(isValidUsername(*l, username) == 0){
            printf("Tidak ada Manager, Dokter, atau pun Pasien yang bernama %s!\n\n", username);
            printf("Username: ");
            scanf("%s", username);
            printf("Password: ");
            scanf("%s", password);
        }while(isValidPassword(*l, password, getIDByUsername(*l, username)) == 0){
            printf("Password salah untuk pengguna yang bernama %s!\n\n", username);
            printf("Username: ");
            scanf("%s", username);
            printf("Password: ");
            scanf("%s", password);
        }
        *currentID = getIDByUsername(*l, username);
        printf("\n");
        if(strcmp(getRoleByID(*l, *currentID), "Manager") == 0){
            printf("\033[38;5;111m"); 
            printf("Selamat datang Manager %s!\n\n", username);
        }else if(strcmp(getRoleByID(*l, *currentID), "Dokter") == 0){
            printf("\033[38;5;75m"); 
            printf("Selamat datang Dokter %s!\n\n", username);
        }else if(strcmp(getRoleByID(*l, *currentID), "Pasien") == 0){
            printf("\033[38;5;150m"); 
            printf("Selamat datang %s! Ada keluhan apa nih?\n\n", username);
        }
        printLogin();
    }
}

void logout(ListUser *l, int *currentID){
    if(isUserLoggedIn(*currentID) == 0){
        printf("Login gagal!\nLogin dulu baru bisa logout\n\n");
    }else{
        printf("Sampai Jumpa!\n\n");
        printLogout();
        *currentID = MARK_INT;
        printf("\033[38;5;229m"); 
    }
}

void lupaPassword(ListUser *l, int *currentID){
    char username[MAX_USERNAME_LENGTH], unique[MAX_USERNAME_LENGTH], rle[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
    char present;
    int count = 1, idx = 0;
    
    printf("Username anda: ");
    scanf("%s", username);
    printf("Kode unik: ");
    scanf("%s", unique);
    
    while(isValidUsername(*l, username) == 0){
        printf("Tidak ada Manager, Dokter, atau pun Pasien yang bernama %s!\n\n", username);
        printf("Username: ");
        scanf("%s", username);
        printf("Kode Unik: ");
        scanf("%s", unique);
    }//username valid, asumsi seterusnya juga valid
    /* --------- RLE --------- */
    int len = strlen(username);
    present = username[0];
    for (int i = 1; i < len; i++){
        char c = username[i];
        if(present == c){
            count++;
            if(i == (len - 1)){
                count += 48;
                rle[idx] = (char)count;
                idx++;
                rle[idx] = present;
                idx++;
            }
        }else{
            if (count > 1){
                count += 48;
                rle[idx] = (char)count;
                idx++;
                rle[idx] = present;
                idx++;
            }else{
                rle[idx] = present;
                idx++;
            }
            if (i == len - 1){
                rle[idx] = c;
                idx++;
            }
            present = c;
            count = 1;
        }
    }rle[idx] = '\0';
    /* END OF RLE */

    while(strcmp(rle, unique) != 0){
        printf("Kode unik salah!\n\n");
        printf("Username: ");
        scanf("%s", username);
        printf("Kode Unik: ");
        scanf("%s", unique);
    }// kode unik valid, lanjut masukkan password baru

    printf("Halo %s %s silakan daftarkan ulang password anda!\n", getRoleByID(*l, getIDByUsername(*l, username)) ,username);
    scanf("%s", password);
    printf("Password baru anda adalah: %s\n", password);
    setPassword(l, getIDByUsername(*l, username), password);
    printf("Silakan login!\n\n");
}

void menuHelp(ListUser *l, int *currentID){
    printf("===================HELP===================\n");

    if(isUserLoggedIn(*currentID) == 0){
        printf("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.!\n\n");
        printf("===================MENU===================\n");
        printf("    1. LOGIN: Masuk ke dalam akun yang sudah terdaftar\n");
        printf("    2. REGISTER: Membuat akun baru\n");
        printf("    3. LUPA_PASSWORD: Mengganti password yang sudah tersimpan saat ini\n");
    }else{
        if(strcmp(getRoleByID(*l, *currentID), "Manager") == 0){
            printf("Kamu sudah login sebagai Manager!\n\n");
            printf("===================MENU===================\n");
            printf("    1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
            printf("    2. LUPA PASSWORD: Mengganti password yang lupa\n");
            printf("    3. LIHAT_USER: Menampilkan data seluruh pengguna (pasien dan dokter)\n");
            printf("    4. LIHAT_PASIEN: Menampilkan data seluruh pasien\n");
            printf("    5. LIHAT_DOKTER: Menampilkan data seluruh dokter\n");
            printf("    6. CARI_USER: Mencari data pengguna (pasien dan dokter) berdasarkan ID atau username\n");
            printf("    7. CARI_PASIEN: Mencari data pasien berdasarkan ID atau username\n");
            printf("    8. CARI_DOKTER: Mencari data dokter berdasarkan ID atau username\n");
            printf("    9. TAMBAH_DOKTER: Menambahkan jumlah dokter pada rumah sakit\n");
            printf("    10. ASSIGN_DOKTER: Melakukan assign ruangan ke dokter tertentu yang belum memiliki ruangan\n");
            printf("    11. LIHAT_DENAH: Menampilkan denah rumah sakit secara keseluruhan\n");
            printf("    12. LIHAT_RUANGAN: Menampilkan informasi kapasitas, jumlah pasien, dan jumlah dokter pada ruangan tertentu berdasarkan ID ruangan\n");
            printf("    13. LIHAT_SEMUA_ANTRIAN: Menampilkan seluruh antrian pasien beserta kapasitas, jumlah pasien, dan dokter dari tiap ruangan\n");
            printf("    14. EXIT: Keluar dari rumah sakit\n");
            printf("    15. SAVE: Menyimpan kondisi rumah sakit saat ini\n");
            
        }else if(strcmp(getRoleByID(*l, *currentID), "Dokter") == 0){
            printf("Halo Dokter %s!\n\n", USERNAME(*l, *currentID));
            printf("===================MENU===================\n");
            printf("    1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
            printf("    2. LUPA PASSWORD: Mengganti password yang lupa\n");
            printf("    3. DIAGNOSIS: Melakukan pengecekan penyakit pasien\n");
            printf("    4. NGOBATIN: Memberi obat kepada pasien sesuai hasil diagnosis\n");
            printf("    5. LIHAT_DENAH: Menampilkan denah rumah sakit secara keseluruhan\n");
            printf("    6. LIHAT_RUANGAN: Menampilkan informasi kapasitas, jumlah pasien, dan jumlah dokter pada ruangan tertentu berdasarkan ID ruangan\n");
            printf("    7. EXIT: Keluar dari rumah sakit\n");
            printf("    8. SAVE: Menyimpan kondisi rumah sakit saat ini\n");
            
        }else if(strcmp(getRoleByID(*l, *currentID), "Pasien") == 0){
            printf("Kamu sudah login sebagai Pasien!\n\n");
            printf("===================MENU===================\n");
            printf("    1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
            printf("    2. LUPA PASSWORD: Mengganti password yang lupa\n");
            printf("    3. DAFTAR_CHECKUP: Mendaftar untuk melakukan check-up dengan dokter\n");
            printf("    4. ANTRIAN: Melihat status antrian\n");
            printf("    5. MINUM_OBAT: Mengambil obat dan meminumnya\n");
            printf("    6. PENAWAR: Meminum penawar setelah salah minum obat\n");
            printf("    7. PULANGDOK: Memeriksa kembali kondisi ke dokter, sudah cukup baik untuk pulang atau belum.\n");
            printf("    8. LIHAT_DENAH: Menampilkan denah rumah sakit secara keseluruhan\n");
            printf("    9. LIHAT_RUANGAN: Menampilkan informasi kapasitas, jumlah pasien, dan jumlah dokter pada ruangan tertentu berdasarkan ID ruangan\n");
            printf("    10. EXIT: Keluar dari rumah sakit\n");
            printf("    11. SAVE: Menyimpan kondisi rumah sakit saat ini\n");
        }
    }
    printf("Footnote:\n");
    printf("    1. Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
    printf("    2. Jangan lupa untuk memasukkan input yang valid\n\n");
}

void printLogin(){
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⢀⣠⣤⣄⡀⢀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡶⠛⢉⠤⣀⠤⡠⢫⠵⠶⢩⡢⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⣀⠀⠀⠀⠀⠀⠀⢰⠋⠀⣠⢡⠋⠉⠙⣆⢂⣤⡄⠈⡇⡇⠀⠀⣀⣶⣄⢤⠀\n");
    printf("⢠⢇⠓⠒⣂⡤⡀⠀⡆⠀⡜⣿⣜⢄⣿⢆⠜⣤⣝⣓⣢⠜⠀⡠⢛⠧⠬⠭⠸⠇\n");
    printf("⠈⠒⠓⠂⠙⠓⢌⠢⢷⡫⠐⠉⠛⠴⠶⠖⠊⠀⠉⠉⠀⢸⠌⡰⠁⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠑⡀⠙⢕⢦⠀⠀⠠⣲⣒⠲⢲⠎⢻⢈⣷⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠸⡀⠀⢣⡑⡄⠀⠑⠠⠄⠘⠴⠂⣸⣹⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠃⠀⠀⢹⣼⡶⣄⠀⠀⠀⠀⡴⢿⢻⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⡝⠁⠀⠙⠒⠒⠋⠀⢸⢸⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⢄⣀⣀⡇⠀⠀⡖⢦⣴⠊⡆⢸⣸⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠀⠉⢸⠁⠀⠸⡇⣞⣯⡷⡇⢨⢹⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⡀⠔⠃⠀⠀⠀⠑⠬⠭⠝⠀⣈⡾⡄⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⡴⢣⠑⢄⣀⣀⣀⣀⣀⠀⠤⣐⢞⣿⡡⠃⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠉⠉⠀⠀⠀⠀⠀⠀⠀⠈⠫⠙⠀⠀⠀⠀⠀⠀⠀⠀\n\n");
    return;
}

void printLogout(){
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣄⡤⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠻⡽⡾⠉⠉⠞⣿⣿⣭⡒⢤⢤⣄⠀⠀⠀\n");
    printf("⣀⡀⢀⠀⠀⠀⠀⠀⠀⠀⠸⡼⢧⣀⠠⡊⣮⣾⠖⠀⢈⢸⡆⠙⢷⣄⠀\n");
    printf("⢣⢌⠁⢔⡀⠀⠀⠀⠀⠀⢀⠟⠭⠈⠭⠵⣝⠶⠤⣔⠵⠃⣿⡀⠀⢹⡀\n");
    printf("⠈⠚⠲⣠⠳⣄⠀⠀⠀⡠⠃⠀⠀⠀⠀⠀⠈⠫⠭⠤⠤⠚⢿⣿⣆⠀⡇\n");
    printf("⠀⠀⠀⠀⠳⢄⠑⢢⠜⠀⣜⠁⣇⠉⠓⠢⢄⠀⠀⠀⠀⠀⠀⠹⣿⣧⡇\n");
    printf("⠀⠀⠀⠀⠀⠀⠉⢾⠀⠀⢳⣴⡀⠈⠑⠂⢄⡵⠀⠀⠀⠀⠀⠀⢸⡟⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⢠⡞⡀⠀⠀⠑⠚⠁⠙⠒⠉⠀⠀⠀⠀⠀⠀⡴⠁⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⡌⡿⠉⠒⠤⣀⡀⠀⠀⠀⠀⣀⠠⠄⢒⣉⣸⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⢀⡟⠀⢠⠁⠒⠠⠀⠉⣿⣏⠡⠄⠒⠉⠀⠀⠓⠤⡀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⣎⠃⠀⠸⣀⠀⡠⠀⠀⠀⡇⠀⠀⠀⢠⠦⠒⠖⢦⡸⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⢣⠀⠀⠀⠀⠀⠀⠀⠀⠀⡧⠤⠤⠤⠴⡔⢀⣀⠴⠃⠀⠀\n");
    printf("⠀⠀⠀⠀⡀⡀⢑⠤⠄⠀⣀⣀⡀⠀⢀⣀⣂⣀⣄⣀⠼⠁⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠣⣌⠓⠤⡀⢠⠊⠀⠀⠈⠁⢢⣀⢀⡹⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠈⠑⠚⠁⠀⠀⠀⠀⠀⠘⠠⠀⠃⠀⠀⣶⠖⠶⠄⠀⠀\n\n");
}