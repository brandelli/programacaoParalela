#include <stdio.h>
#include "mpi.h"
#define ROWS 1000
#define COLUMNS 100000

int comp(const void* a, const void* b);

void main(int argc, char** argv){

    int my_rank;  // Identificador do processo
    int proc_n;   // Número de processos
    int sent = 0; //numero de vetores enviados para os escravos
    int **vet = malloc(ROWS * sizeof(int *));
    double start, end;
    MPI_Init (&argc , & argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_n);
    MPI_Status status; // Status de retorno

    //tratamento dos escravos
    if (my_rank != 0){
        while(1){
            //aloca espaço para o vetor que será recebido
            int *aux_vet = malloc(COLUMNS * sizeof(int));
            MPI_Recv(aux_vet, 0, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            //caso seja recebida uma MPI_TAG = 1 significa que ele recebeu trabalho
            if(status.MPI_TAG){
                qsort(aux_vet, COLUMNS, sizeof(int), comp);
                MPI_Send(aux_vet, 0, MPI_INT, 0, 0, MPI_COMM_WORLD);
            }else{
                //suicidio do escravo
                break; 
            }
        }
    }else{
        //tratamento do mestre
        //faz o preenchimento dos vetores com numeros aleatórios
        for (int i = 0; i < ROWS; i++){
            vet[i] = malloc(COLUMNS * sizeof(int));
            for (int j = 0; j < COLUMNS; j++){
                vet[i][j] = rand() % COLUMNS;
            }
        }
        start = MPI_Wtime();
        //manda a primeira leva de trabalho 
        for (int slave = 1; slave < proc_n; slave++){
            MPI_Send(vet[slave], 0, MPI_INT, slave, 1, MPI_COMM_WORLD);
            sent++;
        }

        //fica mandando trabalho para os escravos conforme recebe a devolucao
        while(sent < ROWS){
            MPI_Recv(vet, 0, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            MPI_Send(vet[sent], 0, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);
            sent++;
        }
        
        int proc = 1;
        //recebe os ultimos vetores ordenados pelos escravos
        while(proc < proc_n){
            MPI_Recv(0, 0, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            proc++;
        }
        //manda a tag com 0 para matar os escravos
        for (int slave = 1; slave < proc_n; slave++){
            MPI_Send(0, 0, MPI_INT, slave, 0, MPI_COMM_WORLD);
        }

        end = MPI_Wtime();

        printf("%f segundos \n", end-start);
    }
    MPI_Finalize();
}

int comp (const void* a, const void* b){
  return *((const int*) a) - *((const int*) b);
}
