
#ifndef CAMERADEF_GUARD_H

	#include <assert.h>
	#include "spacedef.h"

	#define CAMERADEF_GUARD_H

	/**
	 * Quanto a câmera deve se mover (de maneira devagar)
	 */
	#define CAMERA_SLOW_MOVE .05

	/**
	 * Quanto a câmera deve se mover (de maneira rápida)
	 */
	#define CAMERA_FAST_MOVE .4

	/**
	 * Tecla para mover a câmera para frente (devagar)
	 */
	#define CAMERA_SLOW_MOVE_FOWARD 'w'
	
	/**
	 * Tecla para mover a câmera para trás (devagar)
	 */
	#define CAMERA_SLOW_MOVE_BACKWARD 's'

	/**
	 * Tecla para mover a câmera para esquerda (devagar)
	 */
	#define CAMERA_SLOW_MOVE_LEFT 'a'
	
	/**
	 * Tecla para mover a câmera para a direita (devagar)
	 */
	#define CAMERA_SLOW_MOVE_RIGHT 'd'

	/**
	 * Tecla para mover a câmera para cima (devagar)
	 */
	#define CAMERA_SLOW_MOVE_UP 'q'

	/**
	 * Tecla para mover a câmera para baixo (devagar)
	 */
	#define CAMERA_SLOW_MOVE_DOWN 'e'

	/**
	 * Tecla para mover a câmera para frente (rapido)
	 */
	#define CAMERA_FAST_MOVE_FOWARD 'W'
	
	/**
	 * Tecla para mover a câmera para trás (rapido)
	 */
	#define CAMERA_FAST_MOVE_BACKWARD 'S'

	/**
	 * Tecla para mover a câmera para esquerda (rapido)
	 */
	#define CAMERA_FAST_MOVE_LEFT 'A'
	
	/**
	 * Tecla para mover a câmera para a direita (rapido)
	 */
	#define CAMERA_FAST_MOVE_RIGHT 'D'

	/**
	 * Tecla para mover a câmera para cima (rapido)
	 */
	#define CAMERA_FAST_MOVE_UP 'Q'

	/**
	 * Tecla para mover a câmera para baixo (rapido)
	 */
	#define CAMERA_FAST_MOVE_DOWN 'E'

	/**
	 * Definição para os argumentos da função gluLookAt
	 */
	#define LOAD_CAMERA(camera) camera.cameraCoord.x, camera.cameraCoord.y, \
	camera.cameraCoord.z, camera.targetCoord.x,\
	camera.targetCoord.y, camera.targetCoord.z, 0.0, 0.0, 1.0

	

	typedef struct camera_s{
		coord_t targetCoord; // coordenada do ponto alvo, para onde a câmera está "olhando".
		coord_t cameraCoord; // coordenada da câmera/observador.
	}camera_t;

	/**
	 * Move a câmera de acordo com o botão pressionado
	 * @param button Botão pressionado.
	 * @see #CAMERA_SLOW_MOVE_FOWARD	
	 * @see #CAMERA_SLOW_MOVE_BACKWARD
	 * @see #CAMERA_SLOW_MOVE_LEFT 
	 * @see #CAMERA_SLOW_MOVE_RIGHT
	 * @see #CAMERA_SLOW_MOVE_UP 
	 * @see #CAMERA_SLOW_MOVE_DOWN
	 * @see #CAMERA_FAST_MOVE_FOWARD
	 * @see #CAMERA_FAST_MOVE_BACKWARD
	 * @see #CAMERA_FAST_MOVE_LEFT 
	 * @see #CAMERA_FAST_MOVE_RIGHT
	 * @see #CAMERA_FAST_MOVE_UP 
	 * @see #CAMERA_FAST_MOVE_DOWN 
	 */
	void moveCamera(camera_t *camera, unsigned char button);


#endif






