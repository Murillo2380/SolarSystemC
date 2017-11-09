#ifndef MATH_HELP_GUARD_H

	#define MATH_HELP_GUARD_H
	
	#include <GL/glut.h>
	#include <math.h>

	/**
	 * Consulta o valor do seno para o ângulo especificado.
	 * @param degrees Ângulo em graus a ser consultado.
	 * @return Valor do seno.
	 */
	GLdouble consultSin(GLuint degrees);

	/**
	 * Consulta o valor do cosseno para o ângulo especificado.
	 * @param degrees Ângulo em graus a ser consultado.
	 * @return Valor do cosseno.
	 */
	GLdouble consultCos(GLuint degrees);

#endif
