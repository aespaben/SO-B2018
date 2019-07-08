/**
 * @file semaphore.h
 * 
 * @brief Funciones para la creación y destrucción de semáforos.
 * 
 * @author Angel J. España B.
 * @author Adriana P. Daboin M.
 */

#include <sys/sem.h>
#include "defines.h"

/**
 * @brief Usa la función 'ftok()' para obtener una llave válida.
 *
 * @param f Cadena de caracteres con la ruta del archivo.
 * @param n Número entero para generar la llave.
 *
 * @return La llave creada.
 */
key_t get_key(char *f, int n)
{
	key_t key = ftok(f, n);

	if(key < 0)
	{
		handle_error("ftok");
	}

	return key;
}

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