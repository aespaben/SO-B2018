/**
 * @file defines.h
 * 
 * @brief Definición de constantes, manejo de errores y estructuras para colas de mensajes.
 * 
 * @author Angel J. España B.
 * @author Adriana P. Daboin M.
 * 
 */

#define SHARED_FILE "/bin/ls"
#define SHARED_NUM_1 33
#define SHARED_NUM_2 34
#define SHARED_NUM_3 35
#define SHARED_NUM_4 36

#define handle_error(msg) \
		perror(msg); \
		exit(EXIT_FAILURE);


/**
 * @struct msgbuf
 * 
 * @brief Contiene información del número de autos que pasan por una vía.
 */
typedef struct 
{
	long mtype;
	unsigned short car;
} msgbuf;

/**
 * @struct msgsig
 * 
 * @brief Indica la vía que tiene permiso para continuar.
 */
typedef struct 
{
	long mtype;
	unsigned short proceed;
} msgsig;