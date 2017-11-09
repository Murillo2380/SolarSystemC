#ifndef CAMERADEF_GUARD_H
	#include "cameradef.h"
#endif

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
void moveCamera(camera_t *camera, unsigned char button){

	assert(camera != NULL);

	switch(button){

		case CAMERA_SLOW_MOVE_FOWARD:
			camera -> cameraCoord.y -= CAMERA_SLOW_MOVE;
			camera -> targetCoord.y -= CAMERA_SLOW_MOVE;												
			break;

		case CAMERA_SLOW_MOVE_BACKWARD:
			camera -> cameraCoord.y += CAMERA_SLOW_MOVE;
			camera -> targetCoord.y += CAMERA_SLOW_MOVE;
			break;

		case CAMERA_SLOW_MOVE_LEFT:
			camera -> cameraCoord.x += CAMERA_SLOW_MOVE;
			camera -> targetCoord.x += CAMERA_SLOW_MOVE;
			break;

		case CAMERA_SLOW_MOVE_RIGHT:
			camera -> cameraCoord.x -= CAMERA_SLOW_MOVE;
			camera -> targetCoord.x -= CAMERA_SLOW_MOVE;
			break;

		case CAMERA_SLOW_MOVE_UP:
			camera -> cameraCoord.z += CAMERA_SLOW_MOVE;
			camera -> targetCoord.z += CAMERA_SLOW_MOVE;
			break;

		case CAMERA_SLOW_MOVE_DOWN:
			camera -> cameraCoord.z -= CAMERA_SLOW_MOVE;
			camera -> targetCoord.z -= CAMERA_SLOW_MOVE;
			break;

		case CAMERA_FAST_MOVE_FOWARD:
			camera -> cameraCoord.y -= CAMERA_FAST_MOVE;
			camera -> targetCoord.y -= CAMERA_FAST_MOVE;
			break;

		case CAMERA_FAST_MOVE_BACKWARD:
			camera -> cameraCoord.y += CAMERA_FAST_MOVE;
			camera -> targetCoord.y += CAMERA_FAST_MOVE;
			break;

		case CAMERA_FAST_MOVE_LEFT:
			camera -> cameraCoord.x += CAMERA_FAST_MOVE;
			camera -> targetCoord.x += CAMERA_FAST_MOVE;
			break;

		case CAMERA_FAST_MOVE_RIGHT:
			camera -> cameraCoord.x -= CAMERA_FAST_MOVE;
			camera -> targetCoord.x -= CAMERA_FAST_MOVE;
			break;

		case CAMERA_FAST_MOVE_UP:
			camera -> cameraCoord.z += CAMERA_FAST_MOVE;
			camera -> targetCoord.z += CAMERA_FAST_MOVE;
			break;

		case CAMERA_FAST_MOVE_DOWN:
			camera -> cameraCoord.z -= CAMERA_FAST_MOVE;
			camera -> targetCoord.z -= CAMERA_FAST_MOVE;
			break;
	
	}

}


