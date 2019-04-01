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
    double array[3];
    double array2[3];
    double array3[3];
    
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
    
    array[0] = a;
    array[1] = b;
      
	MPI_Scatter(array, 1, MPI_DOUBLE, &array2, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
			
	// El mensaje seré enviado para confirmar que los datos se recibieron
	printf("Los siguientes datos fueron recuperados: %f por el proceso %d\n", array2[0], world_rank);
			
	MPI_Gather(&array2, 1, MPI_DOUBLE, array3, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    w = (double)(array3[1] * array3[0]) / n;
    suma = 0,0;

    for(i = 1; i <= n; i++) 
    {
		x = (double) array3[0] + (i-1) * w;
		suma = (double) suma +(w * (x * x * x));
    }
   
    if(world_rank == 0)
    {
		printf("Resultado: %f\n", suma);
	}
	
	// Finaliza reloj
	fin = clock();
	t_cpu = ((double) (fin-inicio)) / CLOCKS_PER_SEC;
	printf("Tiempo invertido = %lf \n",t_cpu);
	
    MPI_Finalize();
}
