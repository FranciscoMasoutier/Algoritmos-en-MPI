#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char** argv) 
{
	clock_t inicio, fin;
    double t_cpu;
    // Inicia reloj
    inicio = clock();
	
   // Inicialice el entorno MPI
   MPI_Init(NULL, NULL);

   // Tamaño y Rango
   int world_rank;
   MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
   int world_size;
   MPI_Comm_size(MPI_COMM_WORLD, &world_size);

   // Estamos asumiendo al menos 2 procesos para esta tarea.
   if (world_size < 2) 
   {
		fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
		MPI_Abort(MPI_COMM_WORLD, 1);
   }
   
  // Declaracion de Variables.
  double a, b, w, suma, x;
  int i, n;
  
  a = 1,0;
  b = 4,0;
  n = 400;

  if (world_rank == 0) 
  {
   
    w = (double)(b*a)/n;

    MPI_Send(
      /* data         = */ &w, 
      /* count        = */ 1, 
      /* datatype     = */ MPI_DOUBLE, 
      /* destination  = */ 1, 
      /* tag          = */ 0, 
      /* communicator = */ MPI_COMM_WORLD);

  } else if (world_rank == 1) {

    MPI_Recv(
      /* data         = */ &w, 
      /* count        = */ 1, 
      /* datatype     = */ MPI_DOUBLE, 
      /* source       = */ 0, 
      /* tag          = */ 0, 
      /* communicator = */ MPI_COMM_WORLD, 
      /* status       = */ MPI_STATUS_IGNORE);

     suma = 0,0;

     for(i = 1; i <= n; i++) 
     {
		x = (double) a + (i-1) * w;
		suma = (double) suma +(w * (x * x * x));
     }
     
     printf("Resultado: %f\n", suma);
  }
  // Finaliza reloj
  fin = clock();
  t_cpu = ((double) (fin-inicio)) / CLOCKS_PER_SEC;
  printf("Tiempo invertido = %lf \n",t_cpu);

  MPI_Finalize();
}
 






