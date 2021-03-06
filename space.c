#ifdef _WIN32
	#include <windows.h>
#endif

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "spacedef.h"
#include "cameradef.h"
#include "texture.h"

#define NUM_PLANETS 9

#define ARG_ENABLE_PATH "-ep"
#define ARG_NO_STAR "-ns"
#define ARG_DAY_PER_FRAME "-dpf="
#define ARG_SIZE_SCALE "-ss="
#define ARG_DISTANCE_SCALE "-ds="

static int G_mouseButtonClicked = SPACE_IGNORE_MOUSE;

/**
 * Rotação em torno do eixo Z
 */
static GLfloat G_cameraRotationX;

/**
 * Rotação em torno do eixo Y
 */
static GLfloat G_cameraRotationY;

/**
 * Rotação da câmera em torno do eixo z
 */
static GLfloat G_cameraRotationZ;

/**
 * Rotação da camera em degraus
 */
static GLfloat G_cameraRotationDegrees;

/**
 * Centro X da janela de visualização
 */
static int G_windowCenterX;

/**
 * Centro Y da janela de visualização
 */
static int G_windowCenterY;

static int G_lastMouseX;

static int G_lastMouseY;

static camera_t G_eyeCamera;

static object_t G_planets[NUM_PLANETS];

static object_t G_sun;

static GLfloat G_sunLightPosition[] = {0.0f, 0.0f, 0.0f, 1.0f};

static char G_pathEnabled;

static char G_starDisabled;

void frame(int value){

	glutPostRedisplay();
	glutTimerFunc(SPACE_FRAME_TIME_MS, frame, value);

}

void updateCameraRotation(){

	switch(G_mouseButtonClicked){
		
		case GLUT_LEFT_BUTTON:

			if(abs(G_lastMouseX) > SPACE_CAMERA_ROTATION_TOLERANCE){
				G_cameraRotationX += SPACE_CAMERA_ROTATION_FACTOR * ( (GLfloat) G_lastMouseX ) / (GLfloat) G_windowCenterX; // cosseno
		
				if(G_cameraRotationX >= 360.f) 
					G_cameraRotationX -= 360.f;

				if(G_cameraRotationX < 0) 
					G_cameraRotationX = 360.f - G_cameraRotationX;
			}
	
			if(abs(G_lastMouseY) > SPACE_CAMERA_ROTATION_TOLERANCE){
		
				G_cameraRotationY += SPACE_CAMERA_ROTATION_FACTOR * ( (GLfloat) G_lastMouseY ) / (GLfloat) G_windowCenterY; // seno
	
				if(G_cameraRotationY >= 360.f) 
					G_cameraRotationY -= 360.f;

				if(G_cameraRotationY < 0) 
					G_cameraRotationY = 360.f - G_cameraRotationY;

			}

			break;
	
		case GLUT_RIGHT_BUTTON:

			if(abs(G_lastMouseY) > SPACE_CAMERA_ROTATION_TOLERANCE){
				G_cameraRotationZ += SPACE_CAMERA_ROTATION_FACTOR * ( (GLfloat) G_lastMouseY ) / (GLfloat) G_windowCenterY; // seno

				if(G_cameraRotationZ >= 360.f) 
					G_cameraRotationZ -= 360.f;

				if(G_cameraRotationZ < 0) 
					G_cameraRotationZ = 360.f - G_cameraRotationZ;
			}

	}

}

void display(void){ 
	size_t i;
	size_t j;
	GLUquadric *disk;

	glLoadIdentity(); 

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);

	glDisable(GL_LIGHTING);
	glDisable(GL_FOG);

	glRotatef(G_cameraRotationY, 1.0f, 0.0f, 0.0f);
	glRotatef(G_cameraRotationX, 0.0f, 1.0f, 0.0f);
	glRotatef(G_cameraRotationZ, 0.0f, 0.0f, 1.0f);
	gluLookAt(LOAD_CAMERA(G_eyeCamera));

	spaceTransformObject(&G_sun);

	glColor3f(1.f, 0.f, 0.f);
	glEnable(GL_FOG);	

	if(G_pathEnabled){
		for(i = 0; i < NUM_PLANETS; i++){

			glBegin(GL_LINE_LOOP);
			for(j = 0; j < 360; j++){
				glVertex3d(G_planets[i].coord.x * spaceGetDistanceScale() * cos(M_PI / 180. * (GLdouble) j),
				G_planets[i].coord.x * spaceGetDistanceScale() * sin(M_PI / 180. * (GLdouble) j),
				G_planets[i].coord.z * spaceGetDistanceScale() );
			}
			glEnd();

		}
	}

	glDisable(GL_TEXTURE_2D);

	if(!G_starDisabled)
		spaceDrawStars();

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, G_sunLightPosition);	
	for(i = 0; i < NUM_PLANETS; i++)
		spaceTransformObject(&G_planets[i]);
	
	glutSwapBuffers();
	
}

void reshape(int w, int h){

	G_windowCenterX = w / 2;
	G_windowCenterY = h / 2;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60., 1. * (GLdouble) w / (GLdouble) h, .01, 50.);
	glMatrixMode(GL_MODELVIEW);

}


void init(){
	size_t i;
	char buffer[16];
	char texturePathBuffer[128];

	spaceInitStars();

	GLfloat lightAmbient[] = {.02f, .02f, .02f, 0.f};
	GLfloat lightDiffuse[] = {1.f, 1.f, 1.f, 1.0f};
	GLfloat lightSpecular[] = {1.f, 1.f, 1.f, 1.0f};
	GLfloat fogFar[] = {8.f};

	GLuint textureId[NUM_PLANETS + 1];

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // black
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL); 
	glEnable(GL_BLEND);
	glEnable(GL_LIGHT0);
	glEnable(GL_LINE_SMOOTH);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightAmbient);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_END, fogFar);
	
	GLfloat mat[] = {1.0f, 0.0f, 0.0f, 1.f};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
	//glMaterialfv(GL_FRONT, GL_SHININNES, mat);

	glEnable(GL_TEXTURE_2D);
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
	glGenTextures ( NUM_PLANETS + 1, textureId );
	
	for(i = 0; i < NUM_PLANETS + 1; i++){
		memset(buffer, 0, sizeof buffer / sizeof *buffer );
		memset(buffer, 0, sizeof texturePathBuffer / sizeof *texturePathBuffer );
		sprintf(buffer, "%zu", i);
		strcat(buffer, ".bmp");
		strcpy(texturePathBuffer, "res/texture"); 
		strcat(texturePathBuffer, buffer);
		glBindTexture(GL_TEXTURE_2D, textureId[i]);
		loadBMP(texturePathBuffer);
	}

	G_eyeCamera.cameraCoord.x = 2.0;
	G_eyeCamera.cameraCoord.y = 6.0;
	G_eyeCamera.cameraCoord.z = 5.0;
	G_eyeCamera.targetCoord.x = 2.0;
	G_eyeCamera.targetCoord.y = 0.0;
	G_eyeCamera.targetCoord.z = 0.0;

	G_sun.radius = 6.957;
	G_sun.selfRotationAngularSpeed = .1;
	spaceObjectSetCoord(&G_sun, 0.0, 0.0, 0.0);
//	spaceObjectSetColor(&G_sun, 0xF1, 0xC1, 0x07, 0xFF);
	spaceObjectSetColor(&G_sun, 0xFF, 0xFF, 0xFF, 0xFF);
	spaceObjectSetTexture(&G_sun, GL_TEXTURE_2D, 10);

	G_planets[0].radius = .488;
	spaceObjectSetCoord(&G_planets[0], 5.79, 0., 0.);
	spaceObjectSetColor(&G_planets[0], 0xFF, 0xFF, 0xFF, 0xFF);
	G_planets[0].centerOfRotation = &G_sun.coord;
	G_planets[0].angularSpeed = 360. / 87.;
	G_planets[0].selfRotationAngularSpeed = .2;
	spaceObjectSetTexture(&G_planets[0], GL_TEXTURE_2D, 1);
	
	G_planets[1].radius = 1.2104;
	spaceObjectSetCoord(&G_planets[1], 10.88, 0., 0.);
	spaceObjectSetColor(&G_planets[1], 0xFF, 0xFF, 0xFF, 0xFF);
	G_planets[1].centerOfRotation = &G_sun.coord;
	G_planets[1].angularSpeed = 360. / 224.;
	G_planets[1].selfRotationAngularSpeed = .2;
	spaceObjectSetTexture(&G_planets[1], GL_TEXTURE_2D, 2);

	G_planets[2].radius = 1.2756;
	spaceObjectSetCoord(&G_planets[2], 14.96, 0., 0.);
	spaceObjectSetColor(&G_planets[2], 0xFF, 0xFF, 0xFF, 0xFF);
	G_planets[2].centerOfRotation = &G_sun.coord;
	G_planets[2].angularSpeed = 360. / 365.;
	G_planets[2].selfRotationAngularSpeed = .2;
	spaceObjectSetTexture(&G_planets[2], GL_TEXTURE_2D, 3);

	G_planets[3].radius = 0.6794;
	spaceObjectSetCoord(&G_planets[3], 22.79, 0., 0.);
	spaceObjectSetColor(&G_planets[3], 0xFF, 0xFF, 0xFF, 0xFF);
	G_planets[3].centerOfRotation = &G_sun.coord;
	G_planets[3].angularSpeed = 360. / 687.;
	G_planets[3].selfRotationAngularSpeed = .2;
	spaceObjectSetTexture(&G_planets[3], GL_TEXTURE_2D, 4);
	
	G_planets[4].radius = 14.3;
	spaceObjectSetCoord(&G_planets[4], 77.83, 0., 0.);
	spaceObjectSetColor(&G_planets[4], 0xFF, 0xFF, 0xFF, 0xFF);
	G_planets[4].centerOfRotation = &G_sun.coord;
	G_planets[4].angularSpeed = 360. / (GLdouble)(12 * 365);
	G_planets[4].selfRotationAngularSpeed = 0.2;
	spaceObjectSetTexture(&G_planets[4], GL_TEXTURE_2D, 5);
	
	G_planets[5].radius = 12.0;
	spaceObjectSetCoord(&G_planets[5], 143., 0., 0.);
	spaceObjectSetColor(&G_planets[5], 0xFF, 0xFF, 0xFF, 0xFF);
	G_planets[5].centerOfRotation = &G_sun.coord;
	G_planets[5].angularSpeed = 360. / (GLdouble)(29.5 * 365.);
	G_planets[5].selfRotationAngularSpeed = .2;
	spaceObjectSetTexture(&G_planets[5], GL_TEXTURE_2D, 6);

	G_planets[6].radius = 5.1;
	spaceObjectSetCoord(&G_planets[6], 287., 0., 0.);
	spaceObjectSetColor(&G_planets[6], 0xFF, 0xFF, 0xFF, 0xFF);
	G_planets[6].centerOfRotation = &G_sun.coord;
	G_planets[6].angularSpeed = 360. / (GLdouble)(84 * 365);
	G_planets[6].selfRotationAngularSpeed = .2;
	spaceObjectNoTexture(&G_planets[6]);

	G_planets[7].radius = 4.95;
	spaceObjectSetCoord(&G_planets[7], 450., 0., 0.);
	spaceObjectSetColor(&G_planets[7], 0xFF, 0xFF, 0xFF, 0xFF);
	G_planets[7].centerOfRotation = &G_sun.coord;
	G_planets[7].angularSpeed = 360. / (GLdouble)(164 * 365);
	G_planets[7].selfRotationAngularSpeed = .2;
	spaceObjectSetTexture(&G_planets[7], GL_TEXTURE_2D, 8);

	G_planets[8].radius = .2374;
	spaceObjectSetCoord(&G_planets[8], 591.3, 0., 0.);
	spaceObjectSetColor(&G_planets[8], 0xFF, 0xFF, 0xFF, 0xFF);
	G_planets[8].centerOfRotation = &G_sun.coord;
	G_planets[8].angularSpeed = 360. / (GLdouble)(248 * 365);
	G_planets[8].selfRotationAngularSpeed = .2;
	spaceObjectNoTexture(&G_planets[8]);

}

void mouseFunc(int button, int state, int x, int y){

	if(state == GLUT_UP)
		G_mouseButtonClicked = SPACE_IGNORE_MOUSE;

	else 
		G_mouseButtonClicked = button;

}

void mouseMotionFunc(int x, int y){

	if(x < 0) 
		x = 0;

	else if(x > SPACE_WINDOW_WIDTH) 
		x = SPACE_WINDOW_WIDTH;	// verifica se o mouse não está fora da tela

	if(y < 0) 
		y = 0;

	else if(y > SPACE_WINDOW_WIDTH)
		y = SPACE_WINDOW_WIDTH;

	x -= G_windowCenterX;
	y -= G_windowCenterY;
	
	if(x > G_windowCenterX && x < G_lastMouseX)
		x = G_windowCenterX;

	else if(x < G_windowCenterX && x > G_lastMouseX)
		x = G_windowCenterX;	

	if(y > G_windowCenterY && y < G_lastMouseY)
		y = G_windowCenterY;

	else if(y < G_windowCenterY && y > G_lastMouseY)
		y = G_windowCenterY;

	G_lastMouseX = x;
	G_lastMouseY = y;

	updateCameraRotation();

}

void keyboardFunc(unsigned char key, int x, int y){
	
	moveCamera(&G_eyeCamera, key);

}

int main(int argc, char **argv){

	size_t i;
	for(i = 0; i < argc; i++){ // leitura de argumentos 

		if(strcmp(argv[i], ARG_ENABLE_PATH) == 0)
			G_pathEnabled = 1;

		else if(strcmp(argv[i], ARG_NO_STAR) == 0)
			G_starDisabled = 1;

		else if(strncmp(argv[i], ARG_DAY_PER_FRAME, strlen(ARG_DAY_PER_FRAME)) == 0){
			spaceSetDaysPerFrame(strtod(&argv[i][strlen(ARG_DAY_PER_FRAME)], NULL));
		}

		else if(strncmp(argv[i], ARG_SIZE_SCALE, strlen(ARG_SIZE_SCALE)) == 0){
			spaceSetSizeScale(strtod(&argv[i][strlen(ARG_SIZE_SCALE)], NULL));
		}
		
		else if(strncmp(argv[i], ARG_DISTANCE_SCALE, strlen(ARG_DISTANCE_SCALE)) == 0){
			spaceSetDistanceScale(strtod(&argv[i][strlen(ARG_DISTANCE_SCALE)], NULL));
		}

	}


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA);
	glutInitWindowSize(SPACE_WINDOW_WIDTH, SPACE_WINDOW_HEIGHT);
	glutInitWindowPosition(SPACE_WINDOW_INITIAL_X, SPACE_WINDOW_INITIAL_Y);
	glutCreateWindow(SPACE_WINDOW_TITLE);
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardFunc);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(mouseMotionFunc);
	glutTimerFunc(SPACE_FRAME_TIME_MS, frame, 0);
	glutMainLoop();	
	return 0;
}



