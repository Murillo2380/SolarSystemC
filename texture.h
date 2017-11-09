#ifndef SPACE_TEXTURE_GUARD_H

	#define SPACE_TEXTURE_GUARD_H

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
	 * @param path Nome Caminho para o arquivo .bmp
	 * @return -1 caso o arquivo não seja bmp ou as informações especificadas anteriormente não seja obedecida, 1 caso contrário.
 	 */
	int loadBMP(char *path);

#endif

