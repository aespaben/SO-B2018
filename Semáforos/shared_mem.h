/**
 * @file shared_mem.h
 * 
 * @brief Funciones para la creación y destrucción de memoria compartida.
 * 
 * @author Angel J. España B.
 * @author Adriana P. Daboin M.
 */

#include <sys/shm.h>
#include "error_handler.h"
#include "defines.h"


/**
 * @struct membuf
 * 
 * @brief Contiene información del número de autos que pasan por una vía, además de contar la cantidad de procesos activos.
 */
typedef struct 
{
	unsigned short cars_1;
	unsigned short cars_2;
	unsigned short cars_3;
	unsigned short cars_4;

	unsigned short total_cars_1;
	unsigned short total_cars_2;
	unsigned short total_cars_3;
	unsigned short total_cars_4;

	unsigned short stop;
	unsigned short process_counter;
} membuf;

/**
 * @brief Crea la memoria compartida (si no existe).
 *
 * @param key Llave obtenida con 'get_key()'.
 * @param flg Bandera. 0 para obtener solo el id de la memoria compartida, cualquier otro valor entero para crearla.
 *
 * @return shmid id de la memoria compartida.
 */
int create_mem(key_t key, int flg)
{
	int shmid;

	if(flg)
	{
		shmid = shmget(key, sizeof(membuf), 0777 | IPC_CREAT);
	}
	else
	{
		shmid = shmget(key, sizeof(membuf), 0777);
	}

	if(shmid < 0)
	{
		handle_error("shmget");
	}

	return shmid;
}

/**
 * @brief Elimina la memoria compartida.
 *
 * @param shmid id de la memoria compartida.
 */
void destroy_mem(int shmid)
{
	if(shmctl(shmid, IPC_RMID, NULL) < 0)
	{
		handle_error("shmctl");
	}
}