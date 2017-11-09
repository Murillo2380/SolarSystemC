#ifndef TEXTURE_GUARD_H
	#ifdef _WIN32
		#include <windows.h>
	#endif
	#include "texture.h"
	#include <assert.h>
	#include <GL/glut.h>
	#include <stdio.h>
#endif

/**
 * <p>Código referente ao exemplo de texturas no pacote opengl disponível na página pessoal do Prof. Ionildo.
 * Carrega uma textura BMP seguindo as seguintes especificações:</p>
 * <p>offset    size    Descrição</p>
 * <p> 0        2       Assinatura do arquivo, deve ser 0x4D42 </p>
 * <p> 2        4       Tamanho do arquivo BMP em bytes (não confiável)</p>
 * <p> 6        2       Reservado, deve ser 0</p>
 * <p> 8        2       Reservado, deve ser 0</p>
 * <p>10        4       Offset para o início dos dados da imagem em bytes</p>
 * <p>14        4       Tamanho da estrutura BITMAPINFOHEADER, deve ser 40</p>
 * <p>18        4       Comprimento da imagem em pixels</p>
 * <p>22        4       Altura da imagem em pixels</p>
 * <p>26        2       Número de planos na imagem, deve ser 1</p>
 * <p>28        2       Número de bits por pixel (1, 3, 8 ou 24)</p>
 * <p>30        4       Tipo de compressão (0 = nenhum, 1 = RLE-8, 2 = RLE-4</p>
 * <p>34        4       Tamanho de imagem em bytes (incluindo padding)</p>
 * <p>38        4       Resolução horizontal em pixels por metro (não confiável)</p>
 * <p>42        4       Resolução vertical em pixels por metro (não confiável)</p>
 * <p>46        4       Número de cores na imagem ou zero</p>
 * <p>50        4       Núumero de cores importates</p>
 * @param path Nome Caminho para o arquivo .bmp. Não pode ser NULL.
 * @return -1 caso o arquivo não seja bmp ou as informações especificadas anteriormente não seja obedecida, 1 caso contrário.
 */
int loadBMP(char *path){

	assert(path != NULL);
	
	#define RETURN(a) {fclose(a); return -1;}
	#define CTOI(C) (*(int*)&C)
	 
	GLubyte     *image;
	GLubyte     Header[0x54]; 
	GLuint      DataPos, imageSize;
	GLsizei     Width,Height;
	int retorno = 0;
	int nb = 0;
	int t = 0;
	int i = 0;
	    
	    
	// Abre o arquivo e efetua a leitura do Header do arquivo BMP
	FILE * fp_arquivo = fopen(path,"rb");
	if (fp_arquivo == NULL) 
	    return -1;
	if (fread(Header,1,0x36,fp_arquivo)!=0x36) 
	    RETURN(fp_arquivo);
	if (Header[0]!='B' || Header[1]!='M')   
	    RETURN(fp_arquivo);
	if (CTOI(Header[0x1E])!=0)              
	    RETURN(fp_arquivo);
	if (CTOI(Header[0x1C])!=24)             
	    RETURN(fp_arquivo);
	    
	// Recupera a informação dos atributos de 
	// altura e largura da imagem

	Width   = CTOI(Header[0x12]);
	Height  = CTOI(Header[0x16]);
	( CTOI(Header[0x0A]) == 0 ) ? ( DataPos=0x36 ) : ( DataPos = CTOI(Header[0x0A]) );
	 
	imageSize=Width*Height*3;
	    
	// Efetua a Carga da Imagem
	image = malloc(imageSize);
	assert(image != NULL);

	retorno = fread(image,1,imageSize,fp_arquivo);
	    
	if (retorno !=imageSize){
	   free (image);
	   RETURN(fp_arquivo);
	}

	// Inverte os valores de R e B

	    
	for ( i = 0; i < imageSize; i += 3 ){
	    t = image[i];
	    image[i] = image[i+2];
	    image[i+2] = t;
	} 

	// Tratamento da textura para o OpenGL

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	   
	// Faz a geraçao da textura na memória
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		                   
	free (image);
	fclose (fp_arquivo);
	return 1;

}
