
#ifndef SPACE_DEF_GUARD_H

	#ifdef _WIN32
		#include <windows.h>
	#endif

	#include <assert.h>
	#include <GL/glut.h>
	#include <math.h>

	#define SPACE_DEF_GUARD_H 

	/**
	 * Visible window width
	 */
	#define SPACE_WINDOW_WIDTH 800

	/**
	 * Visible window height
	 */
	#define SPACE_WINDOW_HEIGHT 800
	
	#define SPACE_WINDOW_INITIAL_X 0

	#define SPACE_WINDOW_INITIAL_Y 0

	#define SPACE_WINDOW_TITLE "Space test"

	/**
	 * Quantos dias se passam a cada frame. 
	 */
	#define SPACE_DAYS_PER_FRAME 1.  

	/**
	 * Escala da distância que será aplicada sobre as coordenadas de todos os planetas.
	 */
	#ifndef SPACE_DISTANCE_SCALE
		#define SPACE_DISTANCE_SCALE .1
	#endif

	#ifndef SPACE_SIZE_SCALE
		#define SPACE_SIZE_SCALE .04
	#endif
	
	/**
	 * Quantos graus de rotação deverá ser aplicado caso o mouse esteja no extremo da tela
	 */
	#define SPACE_CAMERA_ROTATION_FACTOR 2.0f

	/**
	 * Define a quantidade de pixels de tolerância em relação ao centro da tela.
	 */
	#define SPACE_CAMERA_ROTATION_TOLERANCE 30

	/**
	 * Flag para ignorar o mouse no cálculo da rotação da cena.
	 */
	#define SPACE_IGNORE_MOUSE -127

	#define SPACE_FRAME_TIME_MS 33

	/**
	 * Limita o ângulo x entre 0.0 e 360.0
	 */
	#define BOUND_GLDOUBLE_ANGLE(x) do{x = x >= 360. ? x - 360. : x < 0. ? 360. + x : x;}while(0)

	/**
	 * Número de faces para a esfera, que será usado como o segundo e terceiro parâmetro para a função
	 * @code{glutSolidSphere}
	 */
	#define SPACE_SPHERE_DETAIL 40

	typedef struct color_s{

		GLubyte r; // vermelho
		GLubyte g; // verde
		GLubyte b; // azul
		GLubyte a; // trasnparência (alpha)

	}color_t;

	typedef struct coord_s{
		GLdouble x;
		GLdouble y;
		GLdouble z;
	}coord_t;

	typedef struct light_s{
		GLbyte isLightSource; // 0 se o objeto emitir luz.
		color_t lightColor; // cor da luz
		GLdouble radius; // raio de alcance.
	}light_t;

	typedef struct texture_s{
		GLenum target;
		GLuint textureId; // parâmetros para a função glBindTexture
		char hasTexture; // define se a textura existe ou se deve ser ignorada
	}texture_t;

	typedef struct object_s{

		GLdouble radius; // raio do objeto
		GLdouble angularSpeed; // velocidade orbital em graus / unidade de tempo
		GLdouble selfRotationAngularSpeed; // velocidade de rotação em torno de si mesmo em graus / dia
		GLdouble currentSelfRotation; // Grau de rotação atual em torno de si mesmo;
		GLdouble currentRotation; // Grau rotação atual em torno do centro de rotação
		texture_t texture;
		light_t light; // luz deste objeto
		coord_t coord; // coordenada do objeto
		color_t color; // cor do objeto
		coord_t *centerOfRotation;

	}object_t;

	/**
	 * Realiza as transformações no objeto, como translação, rotação, desenhar na tela, etc.
	 * @param object Objeto a ser movido. Não pode ser NULL.
	 */
	void spaceTransformObject(object_t *object);

	/**
	 * Atribui as cores ao objeto;
	 * @param object a receber as cores.
	 * @param r Cor vermelha de 0 a 255.
	 * @param g Cor verde de 0 a 255.
	 * @param b Cor azul de 0 a 255.
	 * @param a Transparência de 0 a 255.
	 */
	void spaceObjectSetColor(object_t *object, GLubyte r, GLubyte g, GLubyte b, GLubyte a);

	/**
	 * Atribui uma cor para este objeto emitir.
	 * @param object Objecto a receber o atributo. Não pode ser NULL.
	 * @param isLightSource {@code 0} se não for um emissor de luz, {@code 1} caso contrário.
	 * @param r Tonalidade vermelha de emissão.
	 * @param g Tonalidade verde de emissão.
	 * @param b Tonalidade azul de emissão.
	 * @param radius Raio de alcance da luz.
	 */ 
	void spaceObjectSetLightSource(object_t *object, GLbyte isLightSource, GLubyte r, GLubyte g, GLubyte b, GLdouble radius);
	
	/**
	 * @param object Objeto a ser posicionado.
	 * @param x Posição X deste objeto.
	 * @param y Posição Y deste objeto.
	 * @param z Posição Z deste objeto.
	 */
	void spaceObjectSetCoord(object_t *object, GLdouble x, GLdouble y, GLdouble z);

	/**
	 * Libera da memória todos os recursos deste objeto. 
	 * @param object Objeto a ser liberado. Não pode ser NULL.
	 * @return Sempre NULL.
	 */
	object_t *spaceFreeObject(object_t *object);

	/**
	 * Desenha estrelas próximo a câmera do espectador
	 */
	void spaceDrawStars();

	/**
	 * Inicializa todas as estrelas
	 */
	void spaceInitStars();

	/**
	 * Atribui uma textura para o objeto especificado. O que de fato acontecerá é a chamada da função
	 * {@code glBindTexture()}, portanto a textura já deve ter sido preparada antes de chamar a função
	 * {@link #spaceTransformObject(object_t *)}
	 */
	void spaceObjectSetTexture(object_t *object, GLenum target, GLuint texture);

	/**
	* Configura o objeto para que tenha a textura ignorada, tendo ou não uma textura.
	* @param object Objeto que não terá textura. Não pode ser NULL.
	*/
	void spaceObjectNoTexture(object_t *object);

	/**
	 * Altera a escala de distância entre os planetas
	 * @param sizeScale Escala que multiplicará a distância dos objetos.
	 */
	void spaceSetDistanceScale(GLdouble distanceScale);

	/**
	 * Altera a escala de tamanho entre os planetas
	 * @param sizeScale Escala que multiplicará o tamanho dos objetos.
	 */
	void spaceSetSizeScale(GLdouble sizeScale);


	/**
	 * Quantos dias deve passar para cada frame renderizado. Valores maiores representará movimentos maiores.
	 * @param daysPerFrame Escala que multiplicará o tamanho dos objetos.
	 */
	void spaceSetDaysPerFrame(GLdouble daysPerFrame);

	/**
	 * Retorna a escala de distância atual.
	 * @return Escala multiplicadora das distâncias dos objetos.	
	 * @see #spaceSetDistanceScale(GLdouble)
	 */
	GLdouble spaceGetDistanceScale();

#endif
