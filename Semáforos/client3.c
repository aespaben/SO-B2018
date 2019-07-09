/**
 * @file client3.c
 * 
 * @brief Genera autos de forma aleatoria según la distribución lambda. Se comunica con otros clientes, les envía autos y a su vez los recibe.
 * 
 * @author Angel J. España B.
 * @author Adriana P. Daboin M.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include "ftok.h"
#include "shared_mem.h"
#include "semaphore.h"
#include "rand_poisson.h"

/**
 * @brief Muestra el uso del programa.
 *
 * @param arg Nombre del programa.
 */
void usage(char* arg);

/**
 * @brief Muestra los autos que salen y entran de la vía.
 *
 * @param arg Arreglo con la cantidad de autos que entran y salen.
 *
 * @return NULL.
 */
void* show_cars(void* arg);


/**
 * @brief Programa principal.
 *
 * @param argc Cantidad de argumentos.
 * @param argv Vector de argumentos.
 *
 * @return 0 si la ejecución finalizó exitosamente, -1 en caso de error.
 */
int main(int argc, char* argv[])
{
	/* Validando argumentos. */
	if(argc != 2) 
	{ 
		usage(argv[0]);
		printf("%c[31;1m", 0x1B);
		printf("\n\tError: Número incorrecto de argumentos.\n\n");
		printf("%c[0m", 0x1B);
		return -1;
	}

	/* Generando semilla en base al tiempo. */
	srand(time(NULL));

	/* Declaraciones de variables. */
	int lambda = atoi(argv[1]);
	int ranges_row_size = 0;
	pthread_t show_cars_thread;
	key_t key = get_key(SHARED_FILE, SHARED_NUM);
	int shmid = create_mem(key, 0);

	membuf *mem;

	if((mem = (membuf*) shmat(shmid, 0, 0)) < 0)
	{
		handle_error("shmat");
	}


	if(mem->process_counter >= PROCESS_MAX)
	{
		printf("\n\tHa superado el límite de procesos simultáneos.\n");
		fflush(stdout);
		return -1;
	}

	++mem->process_counter;

	int semid = create_sem(key, 0);
	

	/* Si el valor de 'lambda' no es válido, se toma 1 por defecto. */
	if(lambda <= 0)
	{
		printf("\n\tNo se encontró un valor válido para lambda.\n");
		printf("\n\tlambda = 1 (por defecto)\n");
		fflush(stdout);

		lambda = 1;
	}

	
	/* 'ranges' funciona como una matriz con memoria dinámica para almacenar los interavlos de probabilidad. */
	double **ranges;

	/* Obteniendo el tamaño de 'ranges' y calculando a su vez los intervalos de probalidad para 'lambda'. */
	ranges_row_size = ranges_poisson(lambda, &ranges);

	/* Creando hilos. */
	if(pthread_create(&show_cars_thread, NULL, show_cars, NULL))
	{
		handle_error("pthread_create");
	}

	do
	{
		sem_red(semid);

		mem->cars_3 = get_random_poisson(ranges);

		while(mem->cars_1)
		{
			--mem->cars_1;
			++mem->total_cars_1;
			sleep(1);
		}


		sem_green(semid);

	} while(!mem->stop);


	 /* Liberando la memoria asignada a 'ranges'. */
	for(int i = 0; i < ranges_row_size; i++)
	{
		free(ranges[i]);
	}

	free(ranges);

	--mem->process_counter;

	return 0;
}

void usage(char* arg)
{
	printf("%c[1m", 0x1B);
	printf("\n\tuso: ");
	printf("%c[0m", 0x1B);
	printf("\n\t  %s <l>\n", arg);

	printf("%c[1m", 0x1B);
	printf("\n\tl:\n");
	printf("%c[0m", 0x1B);
	printf("\t  Promedio de autos por minuto.\n");
}

void* show_cars(void* arg)
{
	/* Obteniendo llave. */
	key_t key = get_key(SHARED_FILE, SHARED_NUM);

	/* Creando memoria compartida. */
	int shmid = create_mem(key, 0);

	membuf *mem;

	if((mem = (membuf*) shmat(shmid, 0, 0)) < 0)
	{
		handle_error("membuf");
	}

	while(!mem->stop)
	{	
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("%c[1;1f", 0x1B);
		printf("%c[1m", 0x1B);
		printf("\n\tVía 3\n");
		printf("%c[0m", 0x1B);
		printf("\n\tTotal de autos entrantes (Vía 1): %d\n", mem->total_cars_1);
		printf("\n\tTotal de autos salientes: %d\n", mem->total_cars_3);
	
		fflush(stdout);
	
		usleep(300000);
	}

	return NULL;
}