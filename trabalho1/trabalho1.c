#include <stdio.h>
#include "mpi.h"

main(int argc, char** argv){
	int my_rank;  // Identificador do processo
	int proc_n;   // Número de processos
	int work = 20; //numero vetores para ordenar
	int sending = 20;
	int receiving;

	MPI_Init (&argc , & argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_n);
	MPI_Status status; // Status de retorno
	
	
	if (my_rank != 0){
		//escravo
		while(1){
			MPI_Recv(receiving, 0, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

			if(0){ //acho que aqui vamos usar o status ou mandar alguma coisa para sinalizar o termino
				return 1;
			}

			//faz o qsort
			sending--;
			MPI_Send(receiving, 0, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}
	}else{
		
	    //mestre
		//manda a primeira leva de trabalho 
		for (int slave = 1; slave < proc_n; slave++){
			MPI_Send(sending, 0, MPI_INT, slave, 1, MPI_COMM_WORLD);
			sending++;
			work--;
		}

		//fica mandando trabalho conforme recebe a devolucao
		while(work > 0){
			MPI_Recv(receiving, 0, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			MPI_Send(sending, 0, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);
			work--;
		}

		while(sending > 0){
			MPI_Recv(receiving, 0, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			MPI_Send(sending, 0, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);
			printf("%d",receiving);
		}

		//verificar a chegada da ultima carga de trabalho


		//matar escravos

	}
	MPI_Finalize();
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