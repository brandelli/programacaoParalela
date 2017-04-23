#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 10
#define COLUMNS 10

int compare(const void* a, const void* b);

void main (int argc, const char* argv[]){
  clock_t start, end;
  double total_time;
  start = clock();
  int **vet = malloc(ROWS * sizeof (int *));
  for (int i = 0; i < ROWS; i++){
    vet[i] = malloc(COLUMNS * sizeof(int));
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
  free(vet);
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("%f segundos\n",cpu_time_used);
}

int compare (const void* a, const void* b){
  return *((const int*) a) - *((const int*) b);
}