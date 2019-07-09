/**
 * @file ftok.h
 * 
 * @brief Contiene las especificaciones para generar una llave.
 * 
 * @author Angel J. España B.
 * @author Adriana P. Daboin M.
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include "error_handler.h"

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