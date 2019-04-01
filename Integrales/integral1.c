#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char *argv[]) 
{
   clock_t inicio, fin;
   double t_cpu;
   // Inicia reloj
   inicio = clock();
   
   // Declaracion de Variables.
   double a, b, w, suma, x;
   int i, n;
    
   // Inicialice el entorno MPI
   MPI_Init(&argc,&argv);

   // Tamaño y Rango
   int world_size;
   MPI_Comm_size(MPI_COMM_WORLD, &world_size);
   int world_rank;
   MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

   a = 1,0;
   b = 4,0;
   n = 400;

   w = (double)(b*a)/n;
   suma = 0,0;

   for(i = 1; i <= n; i++) 
   {
		x = (double) a + (i-1) * w;
		suma = (double) suma +(w * (x * x * x));
   }
   
   printf("Resultado: %f\n", suma);
	
   // Finaliza reloj
   fin = clock();
   t_cpu = ((double) (fin-inicio)) / CLOCKS_PER_SEC;
   printf("Tiempo invertido = %lf \n",t_cpu);
   	
   MPI_Finalize();
}
