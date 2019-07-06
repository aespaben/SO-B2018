/**
 * @file rand_poisson.h
 * 
 * @brief Funciones especializadas para el cálculo de la probabilidad acumulada, intervalos de probabilidad y generación de números aleatorios de la distribución Poisson.
 * 
 * @author Angel J. España B.
 * @author Adriana P. Daboin M.
 */

#include <math.h>
#include <stdlib.h>
/* Variale global estática que almacena el tamaño óptimo del arreglo con la función de distribución acumulada de Poisson. */
static int opt_size;


/**
 * @brief Calcula la función de densidad acumulada para lambda.
 *
 * @param lambda Valor de la media de Poisson.
 * @param acc Puntero a arreglo declarado usando memoria dinámica.
 *
 * @return Tamaño óptimo del arreglo.
 */
int acc_poisson(double lambda, double **acc)
{
	int acc_size;
	double p1 = 0; 
	double p2 = 0;
	double prob = 0;
	double *aux = NULL;
	int fact;
		
	acc_size = lambda * 2;
	p1 = pow(lambda, 0);
	p2 = exp(-lambda);
	fact = 1;

	/* Se le asigna el tamaño de memoria 'acc_size' a 'aux'. */
	aux = (double*) realloc(*acc, acc_size * sizeof(double));

	/* 'acc' apunta al nuevo espacio de memoria. */
	*acc = aux;

	(*acc)[0] = p1 * p2;
	p1 = pow(lambda, 1);
	(*acc)[1] = (p1 * p2) + (*acc)[0];

	for(int i = 2; i < acc_size; ++i)
	{
		p1 = pow(lambda, i);
		fact *= i;
		prob = ((p1 * p2) / fact) + (*acc)[i-1];

		/* Si la probabilidad acumulada es >= 1, se reasigna la memoria para ocupar solo el espacio necesario y se retorna el tamaño óptimo del arreglo. */
		if(prob >= 1.000)
		{
			aux = (double*) realloc(*acc, i * sizeof(double));
			*acc = aux;

			opt_size = i;

			return i;
		}

		(*acc)[i] = prob;
	}

	opt_size = acc_size;

	return acc_size;
}

/**
 * @brief Calcula los intervalos de probabilidad acumulada de la distribución Poisson.
 *
 * @param Valor de la media de Poisson.
 * @param acc Puntero a matriz declarada usando memoria dinámica.
 * 
 * @return Tamaño óptimo del arreglo.
 */
int ranges_poisson(double lambda, double ***ranges)
{
	double *acc = NULL;
	acc_poisson(lambda, &acc);

	*ranges = (double**) malloc(opt_size * sizeof(double*));

	for(int i = 0; i < opt_size; i++)
	{
		(*ranges)[i] = (double*) malloc(2 * sizeof(double));
	}

	(*ranges)[0][0] = 0;
	(*ranges)[0][1] = acc[0];

	for(int i = 1; i < opt_size; ++i)
	{
		(*ranges)[i][0] = acc[i-1];
		(*ranges)[i][1] = acc[i];
	}


	return opt_size;
}

/**
 * @brief Genera un número aleatorio según la distribución Poisson.
 *
 * @param ranges Matriz (llena) que contiene los intervalos de probabilidad de Poisson.
 *
 * @return Valor aleatorio según la distribución de Poisson.
 */
int get_random_poisson(double **ranges)
{
	double random_num = (double) (rand() % 1000) / 1000;

	for(int i = 0; i < opt_size; ++i)
	{
		if(random_num >= ranges[i][0] && random_num < ranges[i][1])
		{
			return i;
		}
	}

	return opt_size;
}