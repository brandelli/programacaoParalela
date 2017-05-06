#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 40      // trabalho final com o valores 10.000, 100.000, 1.000.000

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

int main(){
    int vetor[ARRAY_SIZE];

    for(int i = 0 ; i<ARRAY_SIZE; i++){
        vetor[i] = ARRAY_SIZE-i;
    }

    bubbleSort(ARRAY_SIZE, vetor);
    return 0;
}