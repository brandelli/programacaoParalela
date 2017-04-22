#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 10
#define COLUMNS 10

int vet[ROWS][COLUMNS];
int compare(const void* a, const void* b);

void main (int argc, const char* argv[]){
  for (int i = 0; i < ROWS; i++){
    for (int j = 0; j < COLUMNS; j++){
      vet[i][j] = rand()%10;
    }
  }

  for (int i = 0; i < ROWS; i++){
    printf("Não ordenado \n");
    printf("Vetor: %d -> ",i);
    for (int j = 0; j < COLUMNS; j++){
      printf("%d ",vet[i][j] );
    }
    printf("\n");
    qsort(vet[i], COLUMNS, sizeof(int), compare);
    printf("Ordenado \n");
    printf("Vetor: %d -> ",i);
    for (int j = 0; j < COLUMNS; j++){
      printf("%d ",vet[i][j] );
    }
    printf("\n");
  }
}

int compare (const void* a, const void* b){
  return *((const int*) a) - *((const int*) b);
}