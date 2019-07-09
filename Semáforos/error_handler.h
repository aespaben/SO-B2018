/**
 * @file error_handler.h
 * 
 * @brief Manejador de errores (preprocesador).
 *
 * @param msg Sujeto del error.
 * 
 * @author Angel J. España B.
 * @author Adriana P. Daboin M.
 */

#ifndef ERROR_HANDLER_H

#define ERROR_HANDLER_H


#define handle_error(msg) \
		perror(msg); \
		exit(EXIT_FAILURE);

#endif