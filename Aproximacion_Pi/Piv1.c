#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



#define INTERVAL 1000

int main(int argc, char *argv[]) 
{
    	clock_t inicio, fin;
    	double t_cpu;
    	// Inicia reloj
    	inicio = clock();
    	
    	// Initialize the MPI environment
		MPI_Init(NULL, NULL);
		// Find out rank, size
		int world_rank;
		MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
		int world_size;
		MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    	
    	if (world_size < 2) 
    	{
			fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
			MPI_Abort(MPI_COMM_WORLD, 1);
		}
		
		// Valores de entrada de la función
		int interval, i;
		double x, y, d, pi;
		int puntos_circulo=0, puntos_cuadrado=0;
		
		// Se inicializa en srand
		srand(time(NULL)); 
		
		for(i=0; i < INTERVAL;i++)
		{
			// Se generan los valores aleatorios de X y Y entre 0 y 1
			x = (double) (rand() % (INTERVAL+1)) / INTERVAL;
			y = (double) (rand() % (INTERVAL+1)) / INTERVAL;
			
			// Distancia de (x,y) del origen
			d = (x * x) + (y * y);
			
			if(d <= 1)
			{
				puntos_circulo++;
			}
			// Total de puntos generados
			puntos_cuadrado++;
			
			// Calculo estimado de Pi.
			pi = (double) (4 * puntos_circulo) / puntos_cuadrado;
			
			// Imprimimos el valor de Pi de cada estimación
			
			if(world_rank == 0)
			{
				printf("Valor X = %f Valor Y = %f Valor Estimado de Pi = %f\n", x, y, pi);
			}	
		}
		
		if(world_rank == 0)
		{
			printf("Puntos dentro del círculo = %d Puntos dentro del Cuadrado = %d Valor Final Estimado de Pi = %f\n", puntos_circulo, puntos_cuadrado, pi);
		}
		
		// Finaliza reloj
		fin = clock();
		t_cpu = ((double) (fin-inicio)) / CLOCKS_PER_SEC;
		printf("Tiempo invertido = %lf \n",t_cpu);
		
		// Finalizamos MPI
    	MPI_Finalize();
}
