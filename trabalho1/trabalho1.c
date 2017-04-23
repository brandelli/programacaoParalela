#include <stdio.h>
#include "mpi.h"

#define ROWS 1000
#define COLUMNS 100000

int comp(const void* a, const void* b);
int main(int argc, char** argv){
	int my_rank;  // Identificador do processo
	int proc_n;   // Número de processos
	int work = 0; //numero vetores para ordenar
	int sending = ROWS;
	int **vet = malloc(ROWS * sizeof(int *));
	double t1, t2;

	MPI_Init (&argc , & argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_n);
	MPI_Status status; // Status de retorno
	t1 = MPI_Wtime();
	
	if (my_rank != 0){
		//escravo
		while(1){
			MPI_Recv(vet, 0, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

			if(!status.MPI_TAG){ //acho que aqui vamos usar o status ou mandar alguma coisa para sinalizar o termino
				return 1;
			}

			qsort(vet, COLUMNS, sizeof(int), comp);
			sending--;
			MPI_Send(vet, 0, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}
	}else{
	    //mestre
	    //faz o preenchimento dos vetores com numeros aleatórios
	    for (int i = 0; i < ROWS; i++){
	      vet[i] = malloc(COLUMNS * sizeof(int));
	      for (int j = 0; j < COLUMNS; j++){
	        vet[i][j] = rand() % COLUMNS;
	      }
	    }

		//manda a primeira leva de trabalho 
		for (int slave = 1; slave < proc_n; slave++){
			MPI_Send(vet[i], 0, MPI_INT, slave, 1, MPI_COMM_WORLD);
			work++;
		}

		//fica mandando trabalho conforme recebe a devolucao
		while(work < ROWS){
			MPI_Recv(vet, 0, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			MPI_Send(vet[i], 0, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);
			work++;
		}

		while(sending > 0){
			MPI_Recv(vet, 0, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		}

		//matar escravos
		for (int slave = 1; slave < proc_n; slave++){
			MPI_Send(0, 0, MPI_INT, slave, 0, MPI_COMM_WORLD);
		}



	}
	t2 = MPI_Wtime();
	printf("%f segundos \n", t2-t1);
	MPI_Finalize();
}

int comp (const void* a, const void* b){
  return *((const int*) a) - *((const int*) b);
}

/*
MPI_Send(
    void* data,
    int count,
    MPI_Datatype datatype,
    int destination,
    int tag,
    MPI_Comm communicator)
*/

/*
MPI_Recv(
    void* data,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm communicator,
    MPI_Status* status)
*/