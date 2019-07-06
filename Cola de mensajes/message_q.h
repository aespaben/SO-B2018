/**
 * @file message_q.h
 * 
 * @brief Funciones para el manejo de cola de mensajes.
 * 
 * @author Angel J. España B.
 * @author Adriana P. Daboin M.
 */

#include <sys/msg.h>
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
 * @brief Crea una cola de mensaje (si no existe).
 *
 * @param key Llave obtenida con 'get_key()'.
 * @param flg Bandera. 0 para obtener solo el id de la cola de mensajes, cualquier otro valor entero para crear la cola de mensajes.
 *
 * @return msgid id de la cola de mensajes.
 */
int create_message_q(key_t key, int flg)
{
	int msgid;

	if(flg)
	{
		msgid = msgget(key, 0777 | IPC_CREAT);
	}
	else
	{
		msgid = msgget(key, 0777);
	}

	if(msgid < 0)
	{
		handle_error("msgget");
	}

	return msgid;
}

/**
 * @brief Elimina la cola de mensajes.
 *
 * @param msgid id de la cola de mensajes.
 */
void destroy_message_q(int msgid)
{
	if(msgctl(msgid, IPC_RMID, 0) < 0)
	{
		handle_error("msgctl");
	}
}