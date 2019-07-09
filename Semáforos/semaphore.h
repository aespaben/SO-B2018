/**
 * @file semaphore.h
 * 
 * @brief Funciones para la creación y destrucción de semáforos.
 * 
 * @author Angel J. España B.
 * @author Adriana P. Daboin M.
 */

#include <sys/sem.h>
#include "error_handler.h"

static struct sembuf p = { 0, -1, SEM_UNDO };
static struct sembuf v = { 0, 1, SEM_UNDO };

/**
 * @brief Crea un semáforo (si no existe).
 *
 * @param key Llave obtenida con 'get_key()'.
 * @param flg Bandera. 0 para obtener solo el id del semáforo, cualquier otro valor entero para crear el semáforo.
 *
 * @return semid id del semáforo.
 */
int create_sem(key_t key, int flg)
{
	int semid;

	if(flg)
	{
		semid = semget(key, 1, 0777 | IPC_CREAT);
	}
	else
	{
		semid = semget(key, 1, 0777);
	}

	if(semid < 0)
	{
		handle_error("semget");
	}

	return semid;
}

/**
 * @brief Configura el valor inicial del semáforo.
 * 
 * @param semid id del semáforo.
 * @param value Valor de inicialización del semáforo.
 */
void set_sem(int semid, int value)
{
	if(semctl(semid, 0, SETVAL, value) < 0)
	{
		handle_error("semctl");
	}
}

/**
 * @brief Coloca el semáforo en rojo.
 *
 * @param semid id del semáforo.
 */
void sem_red(int semid)
{
	if(semop(semid, &p, 1) < 0)
	{
		handle_error("sem_red");
	}
}

/**
 * @brief Coloca el semáforo en rojo.
 *
 * @param semid id del semáforo.
 */
void sem_green(int semid)
{
	if(semop(semid, &v, 1) < 0)
	{
		handle_error("sem_green");
	}
}

/**
 * @brief Elimina el semáforo.
 *
 * @param semid id del semáforo.
 */
void destroy_sem(int semid)
{
	if(semctl(semid, 0, IPC_RMID) < 0)
	{
		handle_error("semctl");
	}
}