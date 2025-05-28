#include "save.h"

void save(Matrix M, ListUser l){
    char folder_name[30];
    char path[50];
    char user_path[100];
    char config_path[100];

    const char *base_path = "/src/file/";
    const char *user_file = "user.csv";
    const char *config_file = "config.txt"; 

    boolean status = false;
    while(!status){
        status = true;

        printf("Masukkan nama folder: ");
        scanf("%99s", folder_name); // baca nama folder dari pengguna
        printf("\n");
    
        // Gabungkan base_path dan folder_name
        snprintf(path, sizeof(path), "%s%s/", base_path, folder_name);

        if(isFolderExist(path)){
            if (mkdir(path, 0755) == 0) {
                printf("Membuat Folder %s\n", path);
                status = true;
            } else {
                perror("Gagal membuat folder\n");
                break;
            }
            snprintf(user_path, sizeof(user_path), "%s%s", path, user_file);
            writeFileUser(l, user_path, &status);
            snprintf(config_path, sizeof(config_path), "%s%s", path, config_file);
            writeFileConfig(&M, config_path, &status);
        }else{
            snprintf(user_path, sizeof(user_path), "%s%s", path, user_file);
            writeFileUser(l, user_path, &status);
            snprintf(config_path, sizeof(config_path), "%s%s", path, config_file);
            writeFileConfig(&M, config_path, &status);
        }
        if(status){
            printf("Berhasil menyimpan data di folder %s\n", folder_name);
        }
    }
}
