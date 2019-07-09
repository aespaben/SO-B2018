/**
 * @file server.c
 * 
 * @brief Programa servidor. Se encarga de inicializar la memoria compartida y el semáforo.
 * 
 * @author Angel J. España B.
 * @author Adriana P. Daboin M.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "ftok.h"
#include "shared_mem.h"
#include "semaphore.h"


/**
 * @brief Señal de salida. Elimina la memoria compartida y el semáforo, y cierra el programa.
 *
 * @param signum Número de señal.
 */
void exit_signal(int signum);


/**
 * @brief Función principal.
 *
 * @return 0 al salir exitosamente, -1 en caso de error.
 */
int main()
{
	/* Creando señal. */
	signal(SIGINT, exit_signal);


	/* Obteniendo llave. */
	key_t key = get_key(SHARED_FILE, SHARED_NUM);


	/* Creando memoria compartida. */
	int shmid = create_mem(key, 1);

	membuf *mem;

	if((mem = (membuf*) shmat(shmid, 0, 0)) < 0)
	{
		handle_error("membuf");
	}


	/* Inicializando memoria. */
	mem->cars_1 = 0;
	mem->cars_2 = 0;
	mem->cars_3 = 0;
	mem->cars_4 = 0;

	mem->total_cars_1 = 0;
	mem->total_cars_2 = 0;
	mem->total_cars_3 = 0;
	mem->total_cars_4 = 0;
	

	mem->stop = 0;
	mem->process_counter = 0;


	/* Creando e inicializando el semáforo. */
	int semid = create_sem(key, 1);

	set_sem(semid, 1);

	/* Iniciando bucle del servidor. */
	while(1);

	return 0;
}


void exit_signal(int signum)
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

	mem->stop = 1;

	while(mem->process_counter);

	shmdt(mem);
	destroy_mem(shmid);

	exit(0);
}