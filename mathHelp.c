#ifndef MATH_HELP_GUARD_H
	#include "mathHelp.h"
	#include <time.h>
#endif

#define MEMOIZATION_TABLE 360

static GLdouble sinTable[MEMOIZATION_TABLE];

static GLdouble cosTable[MEMOIZATION_TABLE];

static char wasInitialized;

/**
 * Inicia o processo de memoization para os valores de seno e cosseno
 */
static void initializeMemoization(void){

	wasInitialized = 1;
	time_t t;
	srand((unsigned int) time(&t));

	size_t i;
	GLdouble division = M_PI / 180.;

	for(i = 0; i < MEMOIZATION_TABLE; i++){
		sinTable[i] = sin(division * (GLdouble) i);
		cosTable[i] = cos(division * (GLdouble) i);
	}

}

/**
 * Consulta o valor do seno para o ângulo especificado.
 * @param degrees Ângulo em graus a ser consultado.
 * @return Valor do seno.
 */
GLdouble consultSin(GLuint degrees){

	if(!wasInitialized)
		initializeMemoization();

	return sinTable[degrees % MEMOIZATION_TABLE];
}

/**
 * Consulta o valor do cosseno para o ângulo especificado.
 * @param degrees Ângulo em graus a ser consultado.
 * @return Valor do cosseno.
 */
GLdouble consultCos(GLuint degrees){

	if(!wasInitialized)
			initializeMemoization();

	return cosTable[degrees % MEMOIZATION_TABLE];

}

