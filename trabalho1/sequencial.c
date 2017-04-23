#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 1000
#define COLUMNS 100000

//declaração da função utilizada pelo qsort
int comp(const void* a, const void* b);

void main (int argc, const char* argv[]){
  clock_t start, end;
  double total_time;
  //faz a alocação da matriz
  int **vetor = malloc(ROWS * sizeof(int *));
  //popula a matriz com arrays com valores aleatorios
  for (int i = 0; i < ROWS; i++){
    vetor[i] = malloc(COLUMNS * sizeof(int));
    for (int j = 0; j < COLUMNS; j++){
      vetor[i][j] = rand()%COLUMNS;
    }
  }
  start = clock();
  //faz a ordenação dos vetores
  for (int i = 0; i < ROWS; i++){
    qsort(vetor[i], COLUMNS, sizeof(int), comp);
  }
  end = clock();
  total_time = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("%f segundos\n",total_time);
}

int comp (const void* a, const void* b){
  return *((const int*) a) - *((const int*) b);
}