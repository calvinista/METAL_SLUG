#ifndef GERENCIADOR_HEADER_H_INCLUDED
#define GERENCIADOR_HEADER_H_INCLUDED
//===================================================
// BIBLIOTECAS UTILIZADAS
//===================================================
#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//===================================================
// PROPRIEDADES DA JANELA
//===================================================
#define SCREEN_WIDTH 1200 // Largura da tela
#define SCREEN_HEIGHT 600 // Altura da tela
#define TITLE "Cyber Inf 2077" // T�tulo da janela
#define FPS 60 // Frames por segundo
//===================================================
// DEFINES DO JOGO
//===================================================
#define STRING_MAX_SIZE 64 // Quantidade de caracteres que podem estar nas op��es do menu
#define OPCOES_MENU 3 // Quantidade de op��es no menu inicial
#define LINHAS 10 // Quantidade de linhas na matriz do mapa
#define COLUNAS 200 // Quantidade de colunas na matriz do mapa
#define NOME_TAM_MAX 15 // Tamanho limite do nome do jogador.
#define TAM 5 //5 melhores pontua��es
//===================================================
// DEFINI��O DE APELIDO
//===================================================
typedef struct JOGADOR Jogador_t;
typedef struct INIMIGOS Inimigos_t;
typedef struct BLOCO Bloco_t;
typedef struct CENA Cena_t;
typedef struct TELA Tela_t;
typedef struct FASE Fase_t;
typedef struct LEADERBOARD Scores_t;
typedef struct NOME Nome_t;
//typedef struct RECORD Record;
typedef struct LEVELDATA LevelData;
typedef enum GERENCIADOR_CENA Gerenciador_e;
//===================================================
// DEFINI��O DE ESTRUTURAS
//===================================================
/* RECORD
- Armazena informa��es de recordes de jogadores para fases espec�ficas.

Campos:
  - level_id (int): Identifica a fase � qual o recorde pertence.
  - name (char*): Nome do jogador que alcan�ou o recorde.
  - tries (int): N�mero de tentativas necess�rias para alcan�ar o recorde.
//=========================================================================================
Defini��o:
*/
typedef struct Record
{
    int level_id;
    char name[NOME_TAM_MAX];
    int pts;
}RECORD;
/* LEVELDATA
- Armazena os dados de recordes de uma fase espec�fica.

Campos:
  - level_id (int): Identifica a fase.
  - top5 (Record[5]): Lista dos 5 melhores recordes da fase.
=========================================================================================
Defini��o:
*/
struct LEVELDATA
{
    int level_id;
    RECORD top5[TAM];
};
/* LEADERBOARD
- Gerencia o placar e a interface de usu�rio para exibi��o dos recordes.

Campos:
  - retorno (Rectangle): �rea do bot�o de retorno na tela de placar.
  - reset (Rectangle): �rea do bot�o de reset na tela de placar.
  - fases (LevelData[TAM]): Dados dos recordes das 5 fases dispon�veis.
  - desenhaScore (int): Flag para indicar se o placar deve ser desenhado.
  - pagina (int): P�gina atual do placar sendo exibida.
=========================================================================================
Defini��o:
*/
struct LEADERBOARD
{
    Rectangle retorno;
    Rectangle reset;
    LevelData fases[TAM];
    int desenhaScore;
    int pagina;
};
/* NOME
- Gerencia a entrada e exibi��o do nome do jogador.

Campos:
  - nome (char[NOME_TAM_MAX]): Nome do jogador sendo inserido.
  - contaLetras (int): N�mero de letras j� inseridas no nome.
  - contaFrame (int): Contador de frames para anima��o da inser��o de texto.
  - caixaTexto (Rectangle): �rea da caixa de texto na interface.
  - mouseSobreCaixa (int): Flag para indicar se o mouse est� sobre a caixa de texto.
=========================================================================================
Defini��o:
*/
struct NOME
{
  char nome[NOME_TAM_MAX];
  int contaLetras;
  int contaFrame;
  Rectangle caixaTexto;
  int mouseSobreCaixa;
};
/* CENA
- Gerencia a exibi��o das cenas do jogo, como o menu principal.

Campos:
  - texTitle (Texture2D): Textura do t�tulo do jogo.
  - background (Texture2D): Textura do fundo da cena.
  - string (char[OPCOES_MENU][STRING_MAX_SIZE]): Textos das op��es de menu.
  - fontSize (int): Tamanho da fonte para os textos do menu.
  - encerrarJogo (int): Flag para encerrar o jogo.
  - menuLock (int): Flag para bloquear a navega��o no menu.
  - flagNome (int): Flag para indicar se a entrada de nome est� ativa.
  - hover (int[OPCOES_MENU]): Indica quais bot�es do menu est�o sendo "sobrepostos" pelo mouse.
  - botoes (Rectangle[OPCOES_MENU]): �reas dos bot�es do menu.
  - textColor (Color[OPCOES_MENU]): Cores dos textos dos bot�es do menu.
  - scores (Scores_t): Dados do placar (LeaderBoards).
  - nome (Nome_t): Dados referente a Cena de input de nome.
=========================================================================================
Defini��o:
*/
struct CENA
{
  Texture2D texTitle;
  Texture2D background;
  char string[OPCOES_MENU][STRING_MAX_SIZE];
  int fontSize;
  int encerrarJogo;
  int menuLock;
  int flagNome;
  int hover[OPCOES_MENU];
  Rectangle botoes[OPCOES_MENU];
  Color textColor[OPCOES_MENU];
  Scores_t scores;
  Nome_t nome;
};
/* FASE
- Representa uma fase do jogo, incluindo o layout do mapa.

Campos:
  - mapa (char[LINHAS][COLUNAS]): Matriz que representa o layout do mapa da fase.
  - lineSize (int): N�mero de linhas no mapa.
  - columnSize (int): N�mero de colunas no mapa.
  - tamBloco (int): Tamanho de cada bloco no mapa.
  - indice (int): �ndice da fase.
=========================================================================================
Defini��o:
*/
struct FASE
{
  char mapa[LINHAS][COLUNAS];
  int lineSize;
  int columnSize;
  int tamBloco;
  int indice;
  Texture2D background;
};

/* TELA
- Armazena as dimens�es da tela do jogo.

Campos:
  - largura (int): Largura da tela.
  - altura (int): Altura da tela.
=========================================================================================
Defini��o:
*/
struct TELA
{
  int largura;
  int altura;
};

/* JOGADOR
- Gerencia os dados do jogador, incluindo f�sica e estado no jogo.

Campos:
  - tex (Texture2D): Textura do jogador.
  - velocidade (Vector2): Vetor de velocidade do jogador.
  - gravidade (Vector2): Vetor de gravidade que afeta o jogador.
  - posicao (Vector2): Posi��o do jogador na tela.
  - tamanho (Vector2): Tamanho do jogador.
  - pulando (int): Flag para indicar se o jogador est� pulando.
  - andando (int): Flag para indicar se o jogador est� andando.
  - atirando (int): Flag para indicar se o jogador est� atirando.
  - tentativas (int): N�mero de tentativas realizadas pelo jogador.
  - pts (int): Pontos acumulados pelo jogador.
  - cd (int): Cooldown (tempo de espera) para a��es.
  - faseCompleta (int): Flag para indicar se a fase foi completada.
  - idFase (int): ID da fase atual.
=========================================================================================
Defini��o:
*/
struct JOGADOR
{
  Texture2D tex;
  Vector2 velocidade;
  Vector2 gravidade;
  Vector2 posicao;
  Vector2 tamanho;
  int pulando;
  int andando;
  int atirando;
  int tentativas;
  int pts;
  int cd;
  int faseCompleta;
  int idFase;
};
/* INIMIGOS:
- Representa um inimigo na fase, assim como sua posi��o na fase e velocidade vertical

Campos:
    - tex(Texture2D): Textura do inimigo.
    - posicao(Vector2): Posi��o do inimigo na tela.
    - tamanho(Vector2D): Tamanho do inimigo.
    - velocidade(Vector2): Vetor de velocidade do inimigo.
    - cd(int): Cooldown, (tempo de espera) para a��es.
    - idFase(int): ID da fase atual.
=========================================================================================
Defini��es:*/
struct INIMIGOS
{
    Texture2D tex;
    Vector2 posicao;
    Vector2 tamanho;
    Vector2 velocidade;
    int cd;
    int idFase;
};
/* GERENCIADOR_CENA
- Enumera as diferentes cenas/estados do jogo.

Valores:
  - MENU (1): Menu principal.
  - SELECAO (2): Sele��o de fases.
  - JOGO (3): Fase do jogo em andamento.
  - FIM (4): Tela de fim de jogo.
=========================================================================================
Defini��o:
*/
enum GERENCIADOR_CENA{
  MENU = 1,
  SELECAO = 2,
  JOGO = 3,
  FIM = 4
};
#endif // GERENCIADOR_HEADER_H_INCLUDED
