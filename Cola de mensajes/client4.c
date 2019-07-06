/**
 * @file client4.c
 * 
 * @brief Envía peticiones (autos) de forma aleatoria al servidor.
 * 
 * @author Angel J. España B.
 * @author Adriana P. Daboin M.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include "message_q.h"
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
 * @brief Recibe los autos de la vía opuesta.
 *
 * @param arg Arreglo con la cantidad de autos que entran y salen.
 *
 * @return NULL.
 */
void* rcv_cars(void* arg);

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
	int cars = 0;
	int total_cars[2] = {0, 0};
	int ranges_row_size = 0;
	key_t key = 0;
	int msgid = 0;
	pthread_t show_cars_thread;
	pthread_t rcv_cars_thread;

	/* Tipo de mensaje que se envía a la cola. */
	long mtype_snd = 4;

	

	/* 'ranges' funciona como una matriz con memoria dinámica para almacenar los interavlos de probabilidad. */
	double **ranges;

	msgbuf msg;
	size_t msgsize = sizeof(msg) - sizeof(long);
	
	/* Si el valor de 'lambda' no es válido, se toma 1 por defecto. */
	if(lambda <= 0)
	{
		printf("\n\tNo se encontró un valor válido para lambda.\n");
		printf("\n\tlambda = 1 (por defecto)\n");
		fflush(stdout);

		lambda = 1;
	}

	/* Obteniendo el tamaño de 'ranges' y calculando a su vez los intervalos de probalidad para 'lambda'. */
	ranges_row_size = ranges_poisson(lambda, &ranges);

	key = get_key(SHARED_FILE, SHARED_NUM_4);
	msgid = create_message_q(key, 0);

	/* Creando hilos. */

	if(pthread_create(&show_cars_thread, NULL, show_cars, (void*) &total_cars))
	{
		handle_error("pthread_create");
	}

	if(pthread_create(&rcv_cars_thread, NULL, rcv_cars, (void*) &total_cars))
	{
		handle_error("pthread_create");
	}

	do
	{
		msg.mtype = mtype_snd;

		if((cars = get_random_poisson(ranges)) > 0)
		{
			msg.car = 1;
			for(int i = 0; i < cars; i++)
			{
				sleep(rand() % 4 + 1);
				if(msgsnd(msgid, (void*) &msg, msgsize, 0) < 0)
				{
					handle_error("msgsnd");
				}

				++total_cars[0];
			}
		}

		msg.car = 0;

		if(msgsnd(msgid, (void*) &msg, msgsize, 0) < 0)
		{
			handle_error("msgsnd");
		}

	} while(1);


	 /* Liberando la memoria asignada a 'ranges'. */
	for(int i = 0; i < ranges_row_size; i++)
	{
		free(ranges[i]);
	}

	free(ranges);

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
	int* total_cars = (int*) arg;

	while(1)
	{	
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("%c[1;1f", 0x1B);
		printf("%c[1m", 0x1B);
		printf("\n\tVía 4\n");
		printf("%c[0m", 0x1B);
		printf("\n\tTotal de autos entrantes (Vía 2): %d\n", total_cars[1]);
		printf("\n\tTotal de autos salientes: %d\n", total_cars[0]);
	
		fflush(stdout);
	
		usleep(300000);
	}
	return NULL;
}

void* rcv_cars(void* arg)
{
	int *total_cars = (int*) arg;
	int key = get_key(SHARED_FILE, SHARED_NUM_4);
	int msgid = create_message_q(key, 0);
	msgbuf msg;
	size_t msgsize = sizeof(msg) - sizeof(long);

	/* Tipo de mensaje que se recibe de la cola. */
	long mtype_rcv = 2;

	while(1)
	{	
		if(msgrcv(msgid, (void*) &msg, msgsize, mtype_rcv, 0) < 0)
		{
			handle_error("msgrcv");
		}

		if(msg.car)
		{
			++total_cars[1];			
		}
	}
	return NULL;
}