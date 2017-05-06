#include <stdio.h>
#include "mpi.h"
#define ARRAY_SIZE 10000
#define DELTA 100

void bubbleSort(int size, int *array); //metodo que faz o ordenamento
int * interleaving(int size,int *array); //metodo que faz a intercalação dos arrays vindos dos filhos
void initializeArray(int size, int *array); // metodo que inicializa o array na ordem inversa
int leftChild(int proc); // metodo que retorna o numero do processo filho a esquerda
int rightChild(int proc); // metodo que retorna o numero do processo filho a direita

void main(int argc, char** argv){
    int my_rank;  // Identificador do processo
    int proc_n;   // Número de processos
    int a_size;   //guarda o tamanho do array dentro do processo
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_n);
    MPI_Status status; // Status de retorno
    MPI_Init();
    my_rank = MPI_Comm_rank();  // pega pega o numero do processo atual (rank)

    if (my_rank != 0){
       MPI_Recv (array, pai);                       // não sou a raiz, tenho pai
       MPI_Get_count(&status, MPI_INT, &v_size);  // descubro tamanho da mensagem recebida
    }else{
       v_size = ARRAY_SIZE;               // defino tamanho inicial do array
       initializeArray(array, v_size);    // sou a raiz e portanto gero o array - ordem reversa
    }
    // dividir ou conquistar?
    if(v_size <= DELTA){
       bubbleSort(array);  // conquisto
    }else{
        // dividir
        // quebrar em duas partes e mandar para os filhos
        MPI_Send (&array[0], filho esquerda, v_size/2);  // mando metade inicial do array
        MPI_Send (&array[v_size/2], filho direita , v_size/2);  // mando metade final
        // receber dos filhos
        MPI_Recv (&array[0], filho esquerda);            
        MPI_Recv (&array[v_size/2], filho direita);   
        // intercalo array inteiro     
        interleaving(array,size);
    }
    // mando para o pai
    if (my_rank != 0)
       MPI_Send (array, pai, v_size);  // tenho pai, retorno array ordenado pra ele
    else
       Mostra (array);                    // sou o raiz, mostro array

    MPI_Finalize();
}

void bubbleSort(int n, int *array){
    int c=0, d, troca, trocou =1;

    while (c < (n-1) & trocou){
        trocou = 0;
        for (d = 0 ; d < n - c - 1; d++){
            if (array[d] > array[d+1]){
                troca      = array[d];
                array[d]   = array[d+1];
                array[d+1] = troca;
                trocou = 1;
            }
        }
        c++;
    }
}

int * interleaving(int tam,int *array){
    int *array_auxiliar;
    int i1, i2, i_aux;

    array_auxiliar = (int *)malloc(sizeof(int) * tam);

    i1 = 0;
    i2 = tam / 2;

    for (i_aux = 0; i_aux < tam; i_aux++) {
        if (((array[i1] <= array[i2]) && (i1 < (tam / 2)))
            || (i2 == tam))
            array_auxiliar[i_aux] = array[i1++];
        else
            array_auxiliar[i_aux] = array[i2++];
    }
    return array_auxiliar;
}

void initializeArray(int size, int *array){
    for(int i = 0 ; i < size; i++){
        array[i] = size-i;
    }
}

int leftChild(int proc){
    return proc * 2 + 1;
}

int rightChild(int proc){
    return proc * 2 + 2;
}