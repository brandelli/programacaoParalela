#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 1000
#define COLUMNS 100000

int comp(const void* a, const void* b);

void main (int argc, const char* argv[]){
  clock_t start, end;
  double total_time;
  int **vet = malloc(ROWS * sizeof(int *));
  for (int i = 0; i < ROWS; i++){
    vet[i] = malloc(COLUMNS * sizeof(int));
    for (int j = 0; j < COLUMNS; j++){
      vet[i][j] = rand()%COLUMNS;
    }
  }

  for (int i = 0; i < ROWS; i++){
    qsort(vet[i], COLUMNS, sizeof(int), comp);
  }
  free(vet);
  end = clock();
  total_time = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("%f segundos\n",total_time);
}

int comp (const void* a, const void* b){
  return *((const int*) a) - *((const int*) b);
}