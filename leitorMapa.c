#include "gerenciador_header.h"
#include "gerenciador_func.h"
//=========================================================================================
/* ReadFileDataEx: const char*, Fase_t* -> int
   Função para ler os dados de um arquivo e carregar o mapa em uma estrutura Fase_t.

    Parâmetros:
    - path (const char*): Caminho do arquivo que contém o mapa.
    - mapa (Fase_t*): Ponteiro para a estrutura onde o mapa será armazenado.

    Objetivo:
    Lê o conteúdo de um arquivo de texto, linha por linha, e armazena o mapa lido na estrutura Fase_t.

    Retorno:
    - int: Retorna 0 em caso de sucesso e -1 em caso de erro ao abrir o arquivo.
*/
//=========================================================================================
int ReadFileDataEx(const char *path, Fase_t *mapa)
{
	FILE *arquivo;
	char string[302];
	int i = 0;

	// Attempt to open the file
	if(!(arquivo = fopen(path, "r"))){
		mapa->indice = 0; // Error loading the map
		return -1;
	} else {
		mapa->indice = 1;

		while(fgets(string, 302, arquivo) && i < 10){
			//puts(string);
			string[strcspn(string, "\r")] = 0; // Linux
			string[strcspn(string, "\n")] = 0; // Windows
			strcpy(mapa->mapa[i], string);
			i++;
		}
	}

	fclose(arquivo);

	mapa->lineSize = LINHAS;
	mapa->columnSize = COLUNAS;
	mapa->tamBloco = 60;
	return 0;
}
