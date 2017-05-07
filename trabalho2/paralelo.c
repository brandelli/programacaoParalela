#include <stdio.h>
#include "mpi.h"
#define ARRAY_SIZE 100

void bubbleSort(int size, int *array); //metodo que faz o ordenamento
void initializeArray(int size, int *array); // metodo que inicializa o array na ordem inversa
void showArray(int *array);
int * interleaving(int size,int *array); //metodo que faz a intercalação dos arrays vindos dos filhos
int father(int proc);
int leftChild(int proc); // metodo que retorna o numero do processo filho a esquerda
int rightChild(int proc); // metodo que retorna o numero do processo filho a direita
int calculateDelta(int size, int proc_n);

//int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag,MPI_Comm comm, MPI_Status *status)


//int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag,MPI_Comm comm)

void main(int argc, char** argv){
    int* aux;
    int array[ARRAY_SIZE];
    int count;
    int my_rank;  // Identificador do processo
    int proc_n;   // Número de processos
    int a_size;   //guarda o tamanho do array dentro do processo
    int delta;
    int a_left;
    int a_right;
    MPI_Init(&argc, &argv);
    MPI_Status status; // Status de retorno
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_n);

    if (my_rank != 0){
       delta = calculateDelta(ARRAY_SIZE,proc_n);
       printf("Meu processo %d \n",my_rank );
       MPI_Recv(array,ARRAY_SIZE,MPI_Init,father(my_rank),MPI_ANY_TAG, MPI_COMM_WORLD, &status);
       MPI_Get_count(&status, MPI_INT, &count)
       a_size = count;
       printf("meu tamanho processo filho %d \n",a_size);
    }else{
       a_size = ARRAY_SIZE;               // defino tamanho inicial do array
       initializeArray(a_size,array);    // sou a raiz e portanto gero o array - ordem reversa
       delta = calculateDelta(ARRAY_SIZE,proc_n);
       printf("Meu processo %d \n",my_rank );
       printf("Meu delta %d \n",delta);
       printf("meu tamanho %d \n",a_size);
       printf("numero de processo %d \n",proc_n);
    }
    // dividir ou conquistar?
    if(a_size <= delta){
       printf("fez o bubble \n");
       bubbleSort(a_size,array);  // conquisto
       MPI_Send(array,a_size,MPI_INT,father(my_rank), 1, MPI_COMM_WORLD);
    }else{
        // dividir
        // quebrar em duas partes e mandar para os filhos
        MPI_Send (&array[0],(a_size/2),MPI_INT,leftChild(my_rank), 1, MPI_COMM_WORLD);  // mando metade inicial do array
        printf("sent to %d \n",leftChild(my_rank));
        MPI_Send (&array[a_size/2],(a_size/2),MPI_INT,rightChild(my_rank),1, MPI_COMM_WORLD);  // mando metade final
        printf("sent to %d \n",rightChild(my_rank));
        // receber dos filhos
        MPI_Recv (&array[0],a_size,MPI_INT,leftChild(my_rank),MPI_ANY_TAG, MPI_COMM_WORLD, &status);            
        MPI_Recv (&array[a_size/2],a_size,MPI_INT,rightChild(my_rank),MPI_ANY_TAG, MPI_COMM_WORLD, &status);   
        // intercalo array inteiro     
        aux = interleaving(a_size,array);
        if (my_rank != 0)
           MPI_Send(aux,a_size,MPI_INT,father(my_rank), 1, MPI_COMM_WORLD);
    }
    if(my_rank == 0){    
       showArray(aux);                    // sou o raiz, mostro array
    }

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

void showArray(int *array){
    for(int i = 0 ; i<ARRAY_SIZE; i++){
        printf("%d\n",array[i]);
    }
}

int father(int proc){
    return (proc-1)/2;
}

int leftChild(int proc){
    return proc * 2 + 1;
}

int rightChild(int proc){
    return proc * 2 + 2;
}

int calculateDelta(int size, int proc_n){
    return size/((proc_n + 1)/2);
}