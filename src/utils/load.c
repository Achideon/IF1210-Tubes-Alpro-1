#include "load.h"

int isFolderExist(char *path){
    struct stat st;
    if(stat(*path, &st) == 0 && S_ISDIR(st.st_mode)){
        return 1;
    }return 0;
}

void load(Matrix *M, ListUser *l, ListInventory *li, ListPerut *lp, boolean *status, char *folder_name){
    char path[50];
    char user_path[100];
    char config_path[100];
    const char *base_path = "/data/";
    const char *user_file = "user.csv";
    const char *config_file = "config.txt";

    snprintf(path, sizeof(path), "%s%s", base_path, folder_name);
    
    if(!strcmp(path, base_path) || !isFolderExist(&path)){
        if(!isFolderExist(&path)){
            printf("folder %s tidak ditemukan", folder_name);
        }else if(!strcmp(path, base_path)){
            printf("Tidak ada nama folder yang diberikan!");
            printf("Usage : ./final_program <<nama_folder>>");
        }
        *status = false;
    }
    if(isFolderExist(&path)){
        snprintf(user_path, sizeof(user_path), "%s%s", path, user_file);
        readFileUser(l, &user_path);
        snprintf(config_path, sizeof(config_path), "%s%s", path, config_file);
        readConfig(M, li, lp, &config_path);
    }
}
