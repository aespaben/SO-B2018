/**
 * @file server.c
 * 
 * @brief Programa servidor. Se encarga de sincronizar y aceptar las peticiones de acceso de los 
 * procesos al área compartida.
 * 
 * @author Angel España.
 * @author Adriana Daboin.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include "message_q.h"


/**
 * @brief Imprime por consola la manera de usar el programa.
 *
 * @param arg Cadena de caracteres con el nombre del programa
 */
void usage(char* arg);


/**
 * @brief Señal que se activa al interrumpir la ejecución del programa con ctrl+c
 *
 * @param signum Número de la señal.
 */
void exit_signal(int signum);


/**
 * @brief Muestra la cantidad de autos en cada vía y la cantidad de autos totales.
 *
 * @param arg Arreglo con la cantidad de autos por vía.
 *
 * @return NULL.
 */
void* show_cars(void* arg);


/**
 * @brief Función principal.
 *
 * @param argc Cantidad de argumentos (no se especifica).
 * @param argv Vector de argumentos.
 *
 * @return 0 al salir exitosamente, -1 en caso de error.
 */
int main(int argc, char* argv[])
{
	/* Decalaración y definición de señales y variables. */

	signal(SIGINT, exit_signal);

	key_t key[4] = {0, 0, 0, 0};
	int msgid[4] = {0, 0, 0, 0};
	long q_type[4] = {1, 2, 3, 4};
	int cars[4] = {0, 0, 0, 0};
	pthread_t show_cars_thread;
	
	msgbuf msg;
	size_t msgsize = sizeof(msg) - sizeof(long);
	
	/* Obtención de la llave. */

	key[0] = get_key(SHARED_FILE, SHARED_NUM_1);
	key[1] = get_key(SHARED_FILE, SHARED_NUM_2);
	key[2] = get_key(SHARED_FILE, SHARED_NUM_3);
	key[3] = get_key(SHARED_FILE, SHARED_NUM_4);

	
	/* Creando la cola de mensajes y obteniendo el id. */

	msgid[0] = create_message_q(key[0], 1);
	msgid[1] = create_message_q(key[1], 1);
	msgid[2] = create_message_q(key[2], 1);
	msgid[3] = create_message_q(key[3], 1);

	/* Creando hilo. */

	if(pthread_create(&show_cars_thread, NULL, show_cars, (void*) &cars))
	{
		handle_error("pthread_create");
	}

	msg.car = 0;
	do
	{
		/* Recepción de mensajes con la información de los vehículos procedentes de cada vía. */

		/* Recibe un mensaje de tipo 1. */
		msgrcv(msgid[0], (void*) &msg, msgsize, q_type[0], IPC_NOWAIT);

		/* Si hay un auto, aumenta el contador de autos, continua recibiendo los demás autos y envía cada uno a la cola (via) opuesta. */
		if(msg.car)
		{
			++cars[0];
			while(msg.car)
			{
				if(msgrcv(msgid[0], (void*) &msg, msgsize, q_type[0], 0) < 0) 
				{ 
					handle_error("msgrcv 1"); 
				}

				if(msg.car)
				{
					++cars[0];
				}

				if(msgsnd(msgid[2], (void*) &msg, msgsize, 0) < 0) 
				{ 
					handle_error("msgsnd 3"); 
				}
			}

			msg.car = 0;
		}
		
		msgrcv(msgid[1], (void*) &msg, msgsize, q_type[1], IPC_NOWAIT);

		if(msg.car)
		{
			++cars[1];
			while(msg.car)
			{
				if(msgrcv(msgid[1], (void*) &msg, msgsize, q_type[1], 0) < 0) 
				{ 
					handle_error("msgrcv 2"); 
				}

				if(msg.car)
				{
					++cars[1];
				}

				if(msgsnd(msgid[3], (void*) &msg, msgsize, 0) < 0) 
				{ 
					handle_error("msgsnd 4"); 
				}
			}

			msg.car = 0;
		}


		msgrcv(msgid[2], (void*) &msg, msgsize, q_type[2], IPC_NOWAIT);

		if(msg.car)
		{
			++cars[2];
			while(msg.car)
			{
				if(msgrcv(msgid[2], (void*) &msg, msgsize, q_type[2], 0) < 0) 
				{ 
					handle_error("msgrcv 3"); 
				}

				if(msg.car)
				{
					++cars[2];
				}

				if(msgsnd(msgid[0], (void*) &msg, msgsize, 0) < 0) 
				{ 
					handle_error("msgsnd 1"); 
				}
			}

			msg.car = 0;
		}

		msgrcv(msgid[3], (void*) &msg, msgsize, q_type[3], IPC_NOWAIT);

		if(msg.car)
		{
			++cars[3];
			while(msg.car)
			{
				if(msgrcv(msgid[3], (void*) &msg, msgsize, q_type[3], 0) < 0) 
				{ 
					handle_error("msgrcv 4"); 
				}

				if(msg.car)
				{
					++cars[3];
				}

				if(msgsnd(msgid[1], (void*) &msg, msgsize, 0) < 0) 
				{ 
					handle_error("msgsnd 2"); 
				}
			}

			msg.car = 0;
		}

		
	} while(1);


	/* Liberación de la cola de mensajes. */
	
	destroy_message_q(msgid[0]);
	destroy_message_q(msgid[1]);
	destroy_message_q(msgid[2]);
	destroy_message_q(msgid[3]);

	return 0;
}


void usage(char* arg)
{
	printf("%c[1m", 0x1B);
	printf("\n\tuso: ");
	printf("%c[0m", 0x1B);
	printf("\n\t  %s <times>\n", arg);

	printf("%c[1m", 0x1B);
	printf("\n\ttimes:\n");
	printf("%c[0m", 0x1B);
	printf("\t  Número de repeticiones.\n");
}

void exit_signal(int signum)
{
	key_t key[4] = {0, 0, 0, 0};
	int msgid[4] = {0, 0, 0, 0};

	key[0] = get_key(SHARED_FILE, SHARED_NUM_1);
	key[1] = get_key(SHARED_FILE, SHARED_NUM_2);
	key[2] = get_key(SHARED_FILE, SHARED_NUM_3);
	key[3] = get_key(SHARED_FILE, SHARED_NUM_4);

	msgid[0] = create_message_q(key[0], 0);
	msgid[1] = create_message_q(key[1], 0);
	msgid[2] = create_message_q(key[2], 0);
	msgid[3] = create_message_q(key[3], 0);

	destroy_message_q(msgid[0]);
	destroy_message_q(msgid[1]);
	destroy_message_q(msgid[2]);
	destroy_message_q(msgid[3]);
}

void* show_cars(void* arg)
{
	int* cars = (int*) arg;
	int total_cars;

	while(1)
	{	
		total_cars = cars[0] + cars[1] + cars[2] + cars[3];
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("%c[1;1f", 0x1B);
		printf("\n\tAutos");
		printf("\n\t\tvía #1: %d", cars[0]);
		printf("\n\t\tvía #2: %d", cars[1]);
		printf("\n\t\tvía #3: %d", cars[2]);
		printf("\n\t\tvía #4: %d", cars[3]);
		printf("\n\n\tTotal: %d\n", total_cars);
	
		fflush(stdout);
	
		usleep(300000);
	}
	return NULL;
}