
#ifndef SPACE_DEF_GUARD_H

	#ifdef _WIN32
		#include <windows.h>
	#endif

	#include"spacedef.h"
	#include"mathHelp.h"
	#include"texture.h"

	#define SPACE_NUM_STARS 800000

	/**
	 * Coordenada mínima de aparição das estrelas em função da origem.
	 */
	#define STAR_MIN_RANGE -10.5
	
	/**
	 * Coordenada mínima de aparição das estrelas em função da origem.
	 */
	#define STAR_MAX_RANGE 60.5

	/**
	 * Velocidade mínima das estrelas
	 */
	#define STAR_MIN_SPEED .01

	/**
	 * Velocidade máxima das estrelas
	 */
	#define STAR_MAX_SPEED .02

	typedef struct star_s{
		coord_t coord;
		color_t color;
		GLdouble speed;
	}star_t;

#endif

static star_t G_stars[SPACE_NUM_STARS];

static GLdouble G_daysPerFrame = SPACE_DAYS_PER_FRAME;

static GLdouble G_sizeScale = SPACE_SIZE_SCALE;

static GLdouble G_distanceScale = SPACE_DISTANCE_SCALE;

/**
 * Desenha uma esfera. Esta função não colore, rotaciona ou translada a esfera.
 * @param radius Raio da esfera
 */
static void spaceDrawSphere(GLdouble radius){

	GLUquadricObj *q = gluNewQuadric();
	assert(q != NULL);

	gluQuadricDrawStyle(q, GLU_FILL);
	gluQuadricNormals(q, GLU_SMOOTH);
	gluQuadricTexture(q, GL_TRUE);
	gluSphere(q, radius, SPACE_SPHERE_DETAIL, SPACE_SPHERE_DETAIL);
	gluDeleteQuadric(q);

}


/**
 * Realiza as transformações no objeto, como translação, rotação, desenhar na tela, etc. As cores 
 * @param object Objeto a ser movido. Não pode ser NULL.
 */
void spaceTransformObject(object_t *object){

	assert(object != NULL);

	object -> currentSelfRotation += object -> selfRotationAngularSpeed * G_daysPerFrame;
	BOUND_GLDOUBLE_ANGLE(object -> currentSelfRotation);

	object -> currentRotation += object -> angularSpeed * G_daysPerFrame;
	BOUND_GLDOUBLE_ANGLE(object -> currentRotation);
	 
	
	glPushMatrix();

	glTranslated(0., 0., 0.);

	if(object -> centerOfRotation != NULL){
	
	/*	
		GLdouble difX = object -> centerOfRotation -> x - object -> coord.x;
		GLdouble difY = object -> centerOfRotation -> y - object -> coord.y;
		GLdouble euclidianDistance = sqrt(difX * difX + difY * difY);
		object -> coord.x = euclidianDistance * sin(object -> currentRotation * M_PI / 180.);
		object -> coord.y = euclidianDistance * cos(object -> currentRotation * M_PI / 180.);
	*/
		glTranslated(object -> centerOfRotation -> x * G_distanceScale, 
		object -> centerOfRotation -> y * G_distanceScale, 
		object -> centerOfRotation -> z * G_distanceScale);
		glRotated(object -> currentRotation, .0, .0, 1.0);
		glTranslated(-object -> centerOfRotation -> x * G_distanceScale,
		-object -> centerOfRotation -> y * G_distanceScale, 
		-object -> centerOfRotation -> z * G_distanceScale);

	}

	glRotated(object -> currentSelfRotation, 0.0, 0.0, 1.0); // rotaciona o objeto em torno de si mesmo
	glTranslated(object -> coord.x * G_distanceScale, 
	object -> coord.y * G_distanceScale, 
	object -> coord.z * G_distanceScale);

	if(object -> texture.hasTexture){
		glEnable(GL_TEXTURE_2D);
		glBindTexture(object -> texture.target, object -> texture.textureId);
	}

	else
		glDisable(GL_TEXTURE_2D);

	glColor4ub(object -> color.r, object -> color.g, object -> color.b, object -> color.a);
	spaceDrawSphere(object -> radius * G_sizeScale);

	glPopMatrix(); 

}

/**
 * Atribui as cores ao objeto;
 * @param object a receber as cores.
 * @param r Cor vermelha de 0 a 255.
 * @param g Cor verde de 0 a 255.
 * @param b Cor azul de 0 a 255.
 * @param a Transparência de 0 a 255.
 */
void spaceObjectSetColor(object_t *object, GLubyte r, GLubyte g, GLubyte b, GLubyte a){

	assert(object != NULL);

	object -> color.r = r;
	object -> color.g = g;
	object -> color.b = b;
	object -> color.a = a;

}

/**
 * Libera da memória todos os recursos deste objeto. 	
 * @param object Objeto a ser liberado. Não pode ser NULL.
 * @return Sempre NULL.
 */
object_t *spaceFreeObject(object_t *object){

	assert(object != NULL);
	free(object);
	return NULL;

}

/**
 * Atribui uma cor para este objeto emitir.
 * @param object Objecto a receber o atributo. Não pode ser NULL.
 * @param isLightSource {@code 0} se não for um emissor de luz, {@code 1} caso contrário.
 * @param r Tonalidade vermelha de emissão.
 * @param g Tonalidade verde de emissão.
 * @param b Tonalidade azul de emissão.
 * @param radius Raio de alcance da luz.
 */ 
void spaceObjectSetLightSource(object_t *object, GLbyte isLightSource, GLubyte r, GLubyte g, GLubyte b, GLdouble radius){

	assert(object != NULL);

	object -> light.isLightSource = isLightSource;
	object -> light.lightColor.r = r;
	object -> light.lightColor.g = g;
	object -> light.lightColor.b = b;
	object -> light.radius = radius;

}

/**
 * @param object Objeto a ser posicionado.
 * @param x Posição X deste objeto.
 * @param y Posição Y deste objeto.
 * @param z Posição Z deste objeto.
 */
void spaceObjectSetCoord(object_t *object, GLdouble x, GLdouble y, GLdouble z){

	assert(object != NULL);
	object -> coord.x = x;
	object -> coord.y = y;
	object -> coord.z = z;

}

/**
 * Inicializa uma estrela.
 * @param i estrela a ser inicializada
 */
static void initStar(size_t i){
	
	G_stars[i].coord.x = STAR_MIN_RANGE + (rand() % (GLint) (STAR_MAX_RANGE * 100.)) / 100.;
	G_stars[i].coord.y = STAR_MIN_RANGE + (rand() % (GLint) (STAR_MAX_RANGE * 100.)) / 100.;
	G_stars[i].coord.z = STAR_MIN_RANGE + (rand() % (GLint) (STAR_MAX_RANGE * 100.)) / 100.;
	G_stars[i].color.r = 200 + rand() % 56;
	G_stars[i].color.g = 200 + rand() % 56;
	G_stars[i].color.b = 200 + rand() % 56;
	G_stars[i].color.a = 200 + rand() % 56;
	G_stars[i].speed = STAR_MIN_SPEED + rand() % (GLint)(STAR_MAX_SPEED * 100.) / 100.;

}

/**
 * Inicializa todas as estrelas
 */
void spaceInitStars(){

	size_t i;
	for(i = 0; i < SPACE_NUM_STARS; i++)
		initStar(i);

}

/**
 * Desenha estrelas próximo a câmera do espectador
 */
void spaceDrawStars(){

	size_t i;

	glPushMatrix();

	glPointSize(1.);
	glBegin(GL_POINTS);

	for(i = 0; i < SPACE_NUM_STARS; i++){

		if(G_stars[i].coord.x < STAR_MIN_RANGE || G_stars[i].coord.y < STAR_MIN_RANGE || G_stars[i].coord.z < STAR_MIN_RANGE ||
		G_stars[i].coord.x > STAR_MAX_RANGE || G_stars[i].coord.y > STAR_MAX_RANGE || G_stars[i].coord.z > STAR_MAX_RANGE )
			initStar(i);
		

		G_stars[i].coord.y += G_stars[i].speed / 10.; 
		glColor4ub(G_stars[i].color.r, G_stars[i].color.g, G_stars[i].color.b, G_stars[i].color.a);	
		glVertex3d(G_stars[i].coord.x, G_stars[i].coord.y, G_stars[i].coord.z);

	}

	glEnd();
	glPopMatrix();
	

}

/**
 * Atribui uma textura para o objeto especificado. O que de fato acontecerá é a chamada da função
 * {@code glBindTexture()}, portanto a textura já deve ter sido preparada antes de chamar a função
 * {@link #spaceTransformObject(object_t *)}
 * @param object Objeto que vai receber a textura. Não pode ser NULL.
 * @para target Primeiro argumento da função {@code glBindTexture()}.
 * @param textureId Segundo argumento da função {@code glBindTexture()}.
 */
void spaceObjectSetTexture(object_t *object, GLenum target, GLuint textureId){

	assert(object != NULL);
	object -> texture.target = target;
	object -> texture.textureId = textureId;
	object -> texture.hasTexture = 1;

}

/**
* Configura o objeto para que tenha a textura ignorada, tendo ou não uma textura.
* @param object Objeto que não terá textura. Não pode ser NULL.
*/
void spaceObjectNoTexture(object_t *object){
	assert(object != NULL);
	object -> texture.hasTexture = 0;
}

/**
 * Altera a escala de distância entre os planetas
 * @param sizeScale Escala que multiplicará a distância dos objetos.
 */
void spaceSetDistanceScale(GLdouble distanceScale){
	G_distanceScale = distanceScale;
}

/**
 * Altera a escala de tamanho entre os planetas
 * @param sizeScale Escala que multiplicará o tamanho dos objetos.
 */
void spaceSetSizeScale(GLdouble sizeScale){
	G_sizeScale = sizeScale;
}


/**
 * Quantos dias deve passar para cada frame renderizado. Valores maiores representará movimentos maiores.
 * @param daysPerFrame Escala que multiplicará o tamanho dos objetos.
 */
void spaceSetDaysPerFrame(GLdouble daysPerFrame){
	G_daysPerFrame = daysPerFrame;
}

/**
 * Retorna a escala de distância atual.
 * @return Escala multiplicadora das distâncias dos objetos.	
 * @see #spaceSetDistanceScale(GLdouble)
 */
GLdouble spaceGetDistanceScale(){
	return G_distanceScale;
}







