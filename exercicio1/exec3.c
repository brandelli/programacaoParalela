#include <stdio.h>
#include "mpi.h"
 
main(int argc, char** argv)
{
int my_rank;  /* Identificador do processo */
int proc_n;   /* Número de processos */
int source;   /* Identificador do proc.origem */
int dest;     /* Identificador do proc. destino */
int tag = 50; /* Tag para as mensagens */
 
int numero;
MPI_Status status; /* Status de retorno */
 
MPI_Init (&argc , & argv);
 
MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
MPI_Comm_size(MPI_COMM_WORLD, &proc_n);
 
if (my_rank != 0)
   {
   MPI_Recv (numero, 100, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
   dest = my_rank+1;
   if(my_rank+1 != proc_n)
      MPI_Send (numero, 100, MPI_INT,dest, tag, MPI_COMM_WORLD);
   }else{
      printf("%d",numero);
   }
else
   {
      {
        MPI_Send (numero, 100, MPI_INT,1, tag, MPI_COMM_WORLD);
      }
   
MPI_Finalize();
}
