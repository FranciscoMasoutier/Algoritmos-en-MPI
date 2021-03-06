#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
 
#define RAIZ(x) ((x) * (x) * (x) + 23 * (x) - 100) // Definimos la funcion de la que se busca la raiz
float default_xi = 500;
float default_xu = -500;

int main(int argc, char *argv[]) {
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	// Initialize the MPI environment
	MPI_Init(NULL, NULL);
	// Find out rank, size
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);


	if (world_size < 1) 
    	{
		fprintf(stderr, "Debido a que esta implementacion es secuencial, el World size debe ser mayor que %d\n", world_rank);
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	float xi, xu, xr, xa, ea;
	int iteraciones;

	//printf("Limite superior de la raiz: ");
	//scanf("%f", &xi);
	xi = default_xi;
	//printf("Limite inferior de la raiz: ");
	//scanf("%f", &xu);
	xu = default_xu;
	 
	iteraciones = 0;
	xa = 0.0;
	ea = 0;
	printf("%12s %10s %10s %10s %10s %10s\n", "Iteraciones", "Xi", "Xu", "Xr", "Ea", "Rank");
	 
	do{
		iteraciones++;
		xr = (xi + xu) / 2;
		if(iteraciones >= 2) {
			ea = ((xr - xa) / xr) * 100; // Calculamos el error aproximado a partir de la segunda iteración
		}
		ea = fabs(ea); // Calculamos el valor absoluto del número
		printf("%12d %10f %10f %10f %10f %10d\n", iteraciones, xi, xu, xr, ea, world_rank);
		xa = xr;
		if(RAIZ(xr) > 0) {
			xi = xr;
		} else{
			xu = xr;
		}
	 
	} while(ea > 0.01 || (ea == 0.0 && iteraciones == 1));
	 

	if(world_rank == 0)
	{
		printf("\n\nLa raiz de f(x) = x^3 + 23x - 100; es: %f\n", xr);
		printf("Iteraciones: %d | Error: %f | Rank: %d\n\n", iteraciones, ea, world_rank);
	}
	 
	// Finalizamos MPI
    	MPI_Finalize();

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Tiempo invertido = %lf \n",cpu_time_used);
}
