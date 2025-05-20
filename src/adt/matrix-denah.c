#include <stdio.h>
#include "matrix-denah.h"

void createRuangan(Ruangan *R, int capacity){
    R->kapasitas = capacity;
    R->idDoktor = MARK_INT;
    createQueue(&R->antriPasien);
}

/* Konstruktor */
void createMatrix(int rows, int cols, Matrix *M, int capacity){
    M->rows = rows;
    M->cols = cols;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            createRuangan(&M->data[i][j], capacity);
        }
    }
}

/* Selektor */
Ruangan *getElement(Matrix *M, int row, int col){
    if(row < M->rows && col < M->cols && row >= 0 && col >= 0){
        return &(M->data[row][col]);
    } else return NULL;
}

/* Mutator */
boolean setElement(Matrix *M, int row, int col, Ruangan value){
    if(row < M->rows && col < M->cols && row >= 0 && col >= 0){
        M->data[row][col] = value;
        return true;
    } else return false;
}

boolean isRoomValid (Matrix M, char* ruangan){
  int row,col;
  char rowf;
  sscanf(ruangan, "%c%d", &rowf,&col);
  row = rowf - 'A';
  col -= 1;
  if (row < M.rows && col < M.cols && row >= 0 && col >= 0){
    return true;
  }
  return false;
}

boolean isDoctorAssigned (Matrix M, int id){
    for (int i=0;i<M.rows;i++){
        for (int j=0;j<M.cols;j++){
            if ((M.data[i][j].idDoktor) == id) return true;
        }
    }
    return false;
}

char* getRoomByDoctor (Matrix M, int id){
    char *result = malloc (sizeof (char) * 2);
    if (isDoctorAssigned(M,id)){
      for (int i=0;i<M.rows;i++){
          for (int j=0;j<M.cols;j++){
              if ((M.data[i][j].idDoktor) == id) {
                char abjad = 'A' + i;
                sprintf (result, "%c%d", abjad, j+1);
                return result;
              }
          }
      }
    }
    return "NOPE";
}

boolean isRoomAssigned (Matrix M, char* ruangan){
  int row,col;
  char rowf;
  sscanf(ruangan, "%c%d", &rowf,&col);
  row = rowf - 'A';
  col -= 1;
  if (M.data[row][col].idDoktor != MARK_INT){
    return true;
  }
  return false;
}

char* getDoctorByRoom (Matrix M,char* ruangan, ListUser L){
  if (isRoomAssigned(M,ruangan)){
    int row,col;
    char rowf;
    sscanf(ruangan, "%c%d", &rowf,&col);
    row = rowf - 'A';
    col -= 1;
    if (M.data[row][col].idDoktor != MARK_INT){
      return getUsernameByID(L, M.data[row][col].idDoktor);
    }
  }
  return "KOSONG";
}


/* Output dari denah */
void printDenah(Matrix M){
  printf("   ");
  for(int i = 0; i < M.cols; i++) printf("   %d  ", i+1);
  printf("\n");
  for(int i = 0; i < M.rows; i++){
    if(i == 0){
      printf("   +");
      for(int j = 1; j < M.cols; j++) printf("=====+");
      if(M.cols > 0) printf("=====+\n");
    }
    printf(" %c ", i + 65);
    for(int j = 0; j < M.cols; j++) printf("| %c%d  ", i + 65, j + 1);
    if(M.cols > 0) printf("|\n");
    if(i == 5 - 1){
      printf("   +");
      for(int j = 1; j < M.cols; j++) printf("=====+");
      if(M.cols > 0) printf("=====+\n");
    } 
    else{
      printf("   +");
      for(int j = 1; j < M.cols; j++) printf("=====+");
      if(M.cols > 0) printf("=====+\n");
    }
  }
}

void printRuangan(Matrix M, char * ruangan, ListUser dataUser){
    int i = ruangan[0] - 65;
    int j = ruangan[1] - 49;
    printf("--- Detail Ruangan %s ---\n", ruangan);
    printf("Kapasitas: %d\n", M.data[i][j].kapasitas);
    printf("Doktor   : ");
    if(M.data[i][j].idDoktor > 0) printf("%s\n", getUsernameByID(dataUser, M.data[i][j].idDoktor)); // dataUser == placeholder list user
    else printf(" -\n");
    printf("Pasien di dalam ruangan:\n");
    if(queueLength(M.data[i][j].antriPasien) != 0){
      int k = 1;
      Address temp = M.data[i][j].antriPasien.head;
      while(temp != M.data[i][j].antriPasien.tail){
        printf("   %d. %s\n", k, getUsernameByID(dataUser, temp->info));
        k++;
        temp = temp->next;
      } printf("   %d. %s\n", k, getUsernameByID(dataUser, temp->info)); // print tail queue
    } else printf("   Tidak ada pasien di dalam ruangan saat ini\n");
}