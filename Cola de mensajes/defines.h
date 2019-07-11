/**
 * @file defines.h
 * 
 * @brief Definición de constantes, manejo de errores y estructuras para cola de mensajes.
 * 
 * @author Angel J. España B.
 * @author Adriana P. Daboin M.
 * 
 */

#define SHARED_FILE "/bin/ls"
#define SHARED_NUM_1 34
#define SHARED_NUM_2 35
#define SHARED_NUM_3 36
#define SHARED_NUM_4 37

#define handle_error(msg) \
		perror(msg); \
		exit(EXIT_FAILURE);


/**
 * @struct membuf
 * 
 * @brief 
 */
typedef struct 
{
	long mtype;
	int car;
} msgbuf;