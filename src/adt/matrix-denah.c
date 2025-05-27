#include <stdio.h>
#include "matrix-denah.h"

void createRuangan(Ruangan *R, int capacityDalam, int capacityLuar){
    R->kapasitas = capacityDalam;
    R->kapasitasAntrian = capacityLuar;
    R->idDoktor = MARK_INT;
    createQueue(&R->antriPasien);
}

/* Konstruktor */
void createMatrix(int rows, int cols, Matrix *M, int capacityDalam, int capacityLuar){
    M->rows = rows;
    M->cols = cols;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            createRuangan(&M->data[i][j], capacityDalam, capacityLuar);
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