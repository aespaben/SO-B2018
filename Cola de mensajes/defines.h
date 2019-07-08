/**
 * @file defines.h
 * 
 * @brief Definición de constantes, manejo de errores y estructuras para memoria compartida.
 * 
 * @author Angel J. España B.
 * @author Adriana P. Daboin M.
 * 
 */

#define SHARED_FILE "/bin/ls"
#define SHARED_NUM 111
#define PROCESS_MAX 4

#define handle_error(msg) \
		perror(msg); \
		exit(EXIT_FAILURE);


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

	unsigned short process_counter;
} membuf;
