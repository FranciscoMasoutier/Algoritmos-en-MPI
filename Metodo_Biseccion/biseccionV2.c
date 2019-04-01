#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
 
#define RAIZ(x) ((x) * (x) * (x) + 23 * (x) - 100) // Definimos la funcion de la que se busca la raiz
#define TAM_RESULTADO 5

double default_xi = 500;
double default_xu = -500;

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


	if (world_size < 2) 
    	{
		fprintf(stderr, "Debido a que esta implementacion es uno-uno, el World size debe ser mayor que %d\n", world_rank);
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	double xi, xu, xr, xa, ea;
	int iteraciones;
	double resultados[TAM_RESULTADO];

	//printf("Limite superior de la raiz: ");
	//scanf("%f", &xi);
	xi = default_xi;
	//printf("Limite inferior de la raiz: ");
	//scanf("%f", &xu);
	xu = default_xu;
	 
	iteraciones = 0;
	xa = 0.0;
	ea = 0;


	do{
		iteraciones++;
		if(world_rank == 0)
		{	 
			xr = (xi + xu) / 2;
			if(iteraciones >= 2) {
				ea = ((xr - xa) / xr) * 100; // Calculamos el error aproximado a partir de la segunda iteración
			}

			ea = fabs(ea); // Calculamos el valor absoluto del número
		
			resultados[0] = (double) iteraciones;
			resultados[1] = (double) xi;
			resultados[2] = (double) xu;
			resultados[3] = (double) xr;
			resultados[4] = (double) ea;

			// Envía al segundo proceso los resultados
			MPI_Send(
			/* data         = */ &resultados, 
			/* count        = */ TAM_RESULTADO, 
			/* datatype     = */ MPI_DOUBLE, 
			/* destination  = */ 1, 
			/* tag          = */ 0, 
			/* communicator = */ MPI_COMM_WORLD);

			xa = xr;
			if(RAIZ(xr) > 0) {
				xi = xr;
			} else{
				xu = xr;
			}

		} else if(world_rank == 1)
		{
			// Recibe el resultado enviado por el primer proceso
			MPI_Recv(
			/* data         = */ &resultados, 
			/* count        = */ TAM_RESULTADO, 
			/* datatype     = */ MPI_DOUBLE, 
			/* source       = */ 0, 
			/* tag          = */ 0, 
			/* communicator = */ MPI_COMM_WORLD, 
			/* status       = */ MPI_STATUS_IGNORE);
			
			iteraciones = (int) resultados[0];
			xr = resultados[3];
			ea = resultados[4];

			if(iteraciones == 1)
			{
				printf("%12s %10s %10s %10s %10s\n", "Iteracion", "Xi", "Xu", "Xr", "Ea");
			}

			printf("%12d %10f %10f %10f %10f\n", iteraciones, resultados[1], resultados[2], xr, ea);		
		}
	 
	} while(ea > 0.01 || (ea == 0.00 && iteraciones == 1));

	if(world_rank == 1)
	{
		printf("\n\nLa raiz de f(x) = x^3 + 23x - 100; es: %f\n", xr);
		printf("Iteraciones: %d | Error: %f\n\n", iteraciones, ea);
	}
	 
	// Finalizamos MPI
    	MPI_Finalize();

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Tiempo invertido = %lf \n",cpu_time_used);
}
