#include <stdio.h>
#include <stdlib.h>

#define BAG_SIZE 10      // trabalho final com o valores 10.000, 100.000, 1.000.000
#define ARRAY_SIZE 10

void bubbleSort(int n, int * vetor){
    int c=0, d, troca, trocou =1;

    while (c < (n-1) & trocou ){
        trocou = 0;
        for (d = 0 ; d < n - c - 1; d++){
            if (vetor[d] > vetor[d+1]){
                troca      = vetor[d];
                vetor[d]   = vetor[d+1];
                vetor[d+1] = troca;
                trocou = 1;
            }
        }
        c++;
    }
}

void printArray(int * vetor){
    int index = 0;
    for(int i = 0 ; i < BAG_SIZE; i++){
        for(int j = 0; j < ARRAY_SIZE; j++){
            printf("%d",vetor[index]);
            index++;
        }
        printf("\n");
    }
}

int main(){
    int vetor[BAG_SIZE][ARRAY_SIZE];

    for(int i = 0 ; i < BAG_SIZE; i++){
        for(int j = 0; j < ARRAY_SIZE; j++){
            vetor[i][j] = ARRAY_SIZE - j;
        }
    }

    printArray(vetor[0]);

    for(int i = 0;i < BAG_SIZE; i++){
        bubbleSort(ARRAY_SIZE, vetor[i]);
    }

    printArray(vetor[0]);

    return 0;
}