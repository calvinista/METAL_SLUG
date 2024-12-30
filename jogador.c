#include "gerenciador_header.h"
#include "gerenciador_func.h"
#define GROUNDED 0
#define MAX_PROJETEIS 100

//=========================================================================================
/* Pulo: Jogador_t* -> void
  Função para gerenciar o pulo do jogador.

Parâmetros:
  - jogador (Jogador_t*): Ponteiro para a estrutura do jogador.
Descrição:
  A função verifica se a tecla de pulo (espaço) foi pressionada e se o jogador não
  está pulando atualmente, aplicando a física de pulo. Também atualiza a rotação
  do jogador durante o pulo.
*/
//=========================================================================================
void Pulo(Jogador_t *jogador){
    if(IsKeyDown(KEY_X) && !jogador->pulando)
    {
        jogador->pulando = 1;
        jogador->velocidade.y = -22.0f;
    }

    if(jogador->pulando)
    {
        jogador->velocidade.y += jogador->gravidade.y;
    }
    else if(jogador->velocidade.y >= GROUNDED)
    {
        jogador->pulando = 0;
    }
}
//=========================================================================================
/*Agachar: Jogador_T *jogador -> void

    Verifica se o jogador está agachado ou não.

    Parâmetros:
    - jogador (Jogador_t*): ponteiro p/ a estrutura jogador;

    Descrição: Função encarregada de verificar se o jogador está agachado ou não;
*/
//=========================================================================================
void Agachar(Jogador_t *jogador)
{
    // Altura do jogador
    static int tamanhoOriginalY = 0;

    if(IsKeyDown(KEY_DOWN))
    {
        if(!jogador->agachado)
        {
            jogador->agachado = 1;
            jogador->tamanho.y /= 2;
            jogador->posicao.y += jogador->tamanho.y;
        }
        else if(jogador->agachado)
        {
            jogador->posicao.y -= jogador->tamanho.y;
            jogador->tamanho.y *= 2;
            jogador->agachado = 0;
        }
    }
}
//=========================================================================================
/* Mira: Jogador_t *jogador -> int

    Função que verifica as teclas pressionadas p/ definir a direção vertical da mira

    Parâmetros:

    - jogador (Jogador_t*): Ponteiro p/ estrutura do jogador.

    Descrição: Função responsável por verificar as teclas direcionais (P/ CIMA e P/ BAIXO) pressionadas a fim de definir a direção da mira.
*/
//=========================================================================================
void Mirar(Jogador_t *jogador)
{
    if(IsKeyDown(KEY_UP))
    {
        jogador->mirando = 2;
    }
    else if(IsKeyDown(KEY_DOWN))
    {
        jogador->mirando = 3;
    }
}
//=========================================================================================
/* Atira: Jogador_t *jogador, PROJETIL *projetil,  int *numProjeteis -> void

    Função para gerenciar os disparos efetuados pelo jogador.

    Parâmetros:

  - jogador (Jogador_t*): Ponteiro p/ estrutura do jogador.
  - projetil (Projetil_t*): Ponteiro p/ a estrutura do Disparo
  - numProjeteis (int*): Contador de projeteis, que mantêm o número de projéteis ativo,
    que é incrementado cada vez que um novo é efetuado.

    Descrição:

    A função verifica se a tecla de disparo (S) foi pressionada e se o jogador não
    está disparando atualmente, aplicando a física de disparo. Também atualizanado a posição
    do projétil durante a ação.
*/
//=========================================================================================
void Atira(Jogador_t *jogador, Projetil_t *projetil,  int *numProjeteis)
{
    //Se jogador já tiver efetuado um disparo, não faz nada
    if(jogador->atirando == 1)
    {
        return;
    }

    if(IsKeyPressed(KEY_S))
    {
        if(jogador->andando == 1)
        {
            //DISPARO P/ DIREITA:

            //Posição inicial do projétil
            projetil[*numProjeteis].posicao = jogador->posicao;
            //Ajuste posicional do projétil
            projetil[*numProjeteis].posicao.x += jogador->tamanho.x/2;
            //Velocidade horizontal do projétil
            projetil[*numProjeteis].velocidade = (Vector2)
            {
                5.0f, 0.0f
            };
        }
        else if(jogador->andando == -1)
        {
            //DISPARO P/ ESQUERDA:

            //Posição inicial do projétil
            projetil[*numProjeteis].posicao = jogador->posicao;
            //Ajuste posicional do projétil
            projetil[*numProjeteis].posicao.x -= jogador->tamanho.x/2;
            //Velocidade horizontal do projétil
            projetil[*numProjeteis].velocidade = (Vector2)
            {
                -5.0f, 0.0f
                };
        }
        else if(jogador->mirando == 2)
        {
            projetil[*numProjeteis].posicao = jogador->posicao;
            projetil[*numProjeteis].posicao.y -= jogador->tamanho.y/2;
            projetil[*numProjeteis].velocidade = (Vector2)
            {
                0.0f, -5.0f
            };
        }
        else if(jogador->mirando == 3)
        {
            projetil[*numProjeteis].posicao = jogador->posicao;
            projetil[*numProjeteis].posicao.y += jogador->tamanho.y/2;
            projetil[*numProjeteis].velocidade = (Vector2)
            {
                0.0f, 5.0f
            };
        }
        // Flag p/ indicar a ativação do projétil
        projetil[*numProjeteis].ativo = 1;

        // Incrementador de projeteis
        (*numProjeteis)++;

        // Cooldown do jogador (tempo entre de disparos)
        jogador->cd = 30;
    }
}
//=========================================================================================
/*AtualizaProjetil: Projetil_t* projetil, int *numProjeteis, TELA *tela -> void

    Função p/ atualizar a posição e estado  dos projéteis durante a ação.

    Parâmetros:

    - jgador (Jogador_t*): Ponteiro p/ a estrutura jogador.
    - projetil (Projetil_t*): Ponteiro p/ a estrutura projetil que será atualizada.
    - numProjeteis (int*): Contador de projeteis, que mantêm o número de projéteis ativo,
    que é incrementado cada vez que um novo é efetuado.
    - tela (*Tela_t): Ponteiro p/ a estrutura tela.

    Descrição: A função faz o gerenciamento dos disparos efetuados pelo jogador e inimigos durante o jogo, incluindo velocidade
*/
//=========================================================================================
void AtualizarDisparo(Jogador_t *jogador,Projetil_t *projetil, int *numProjeteis, Tela_t *tela)
{

    int i;

    if(jogador->cd > 0)
    {
        jogador->cd--;
    }

    if(IsKeyPressed(KEY_S) && jogador->cd == 0)
    {
        if(*numProjeteis < MAX_PROJETEIS)
        {
            Projetil_t *novoProjetil = &projetil[*numProjeteis];

            novoProjetil->posicao = jogador->posicao;

            novoProjetil->posicao.x += jogador->tamanho.x/2;
            novoProjetil->posicao.y += jogador->tamanho.y/2;

            if(jogador->andando == 1)
            {
                novoProjetil->velocidade = (Vector2)
                {
                    5.0f, 0.0f
                };
            }
            else if(jogador->andando == -1)
            {
                novoProjetil->velocidade = (Vector2)
                {
                    -5.0f, 0.0f
                    };
            }
            else if(jogador->mirando == 2)
            {
                novoProjetil->velocidade = (Vector2)
                {
                    0.0f, -5.0f
                };
            }
            else if(jogador->mirando == 3)
            {
                novoProjetil->velocidade = (Vector2)
                {
                    0.0f, 5.0f
                };
            }

            novoProjetil->ativo = 1;

            jogador->cd = 30;
        }
    }

    //Desativação dos projeteis, caso ultrapassem os limites da tela
    for(i=0; i<*numProjeteis; i++)
    {
        Projetil_t *projtl = &projetil[i];

        //
        if(projtl->posicao.x < 0 || projtl->posicao.x > GetScreenWidth() ||
                projtl->posicao.y < 0 || projtl->posicao.y > GetScreenHeight())
        {
            projtl->ativo = 0;
        }
    }

}
//=========================================================================================
/*BulletCollision: Projetil_t *projeteis, int numProjeteis, Inimigos_t *inimigos, int numInimigos,
  Bloco_t *blocos, int numBlocos, int *pontuacao -> void

    Função encarregada de verificar a colisão dos projéteis com os inimigos e obstaculos da fase durante o jogo

    Perâmetros:

    - projeteis (Projetil_t*): Ponteiro p/ a estrutura projétil.
    - numProjeteis (int):  Número máximo de projéteis.
    - inimigos (Inimigos_t*): Ponteiro p/ a estrutura inimigo.
    - numInimigos (int): Número máximo de inimigos por fase.
    - blocos (Blocos_t*): Ponteiro p/ a estrutura bloco.

    Descrição: Gerencia a colisão de projéteis do jogador com os inimigos e elementos do cenário
*/
//=========================================================================================
void BulletCollision(Projetil_t *projetil, int numProjeteis, Inimigos_t *inimigo, int numInimigos, Fase_t mapa, Jogador_t *jogador)
{
    int i;
    int j;
    int lin;
    int col;


    for(i=0; i<numProjeteis; i++)
    {
        if(projetil[i].ativo)
        {
            Rectangle projetilRect =
            {
                projetil[i].posicao.x,
                projetil[i].posicao.y,
                mapa.tamBloco,
                mapa.tamBloco
            };

            for(j=0; j<numInimigos; j++)
            {
                Rectangle inimigoRect =
                {
                    inimigo[j].posicao.x,
                    inimigo[j].posicao.y,
                    inimigo[j].tamanho.x,
                    inimigo[j].tamanho.y
                };

                if(CheckCollisionRecs(projetilRect, inimigoRect))
                {
                    projetil[i].ativo = 0;
                    inimigo[j].tamanho.x = 0;
                    inimigo[j].tamanho.y = 0;
                    jogador->pts += 100;
                    break;
                }
            }

            for(col=0; col<mapa.columnSize; col++)
            {
                for(lin=0; lin<mapa.lineSize; lin++)
                {
                    char blocoAtual = mapa.mapa[lin][col];

                    if(blocoAtual=='O' || blocoAtual == 'S')
                    {
                        Vector2 blocoPos = {col*mapa.tamBloco, lin*mapa.tamBloco};

                        Rectangle blocoRect =
                        {
                            blocoPos.x,
                            blocoPos.y,
                            mapa.tamBloco,
                            mapa.tamBloco
                        };

                        if(CheckCollisionRecs(projetilRect, blocoRect))
                        {
                            projetil[i].ativo = 0;
                            break;
                        }
                    }
                }
            }
        }
    }
}
//=========================================================================================
/* SideCollision: Fase_t, Vector2 -> int
  Função para detectar colisões laterais do jogador com o mapa.

Parâmetros:
  - mapa (Fase_t): Estrutura contendo o mapa da fase atual.
  - jogadorPos (Vector2): Posição atual do jogador.
Retorno:
  - int: Um valor inteiro que indica o resultado da colisão:
    - 1: colisão c/ inimigo.
    - 2: colisão c/ projétil inimigo.
    - 3: O jogador coletou um item.
    - 0: Nenhuma colisão relevante.
Descrição:
  A função verifica se o jogador colidiu com obstáculos ou objetos especiais no mapa,
  determinando o efeito dessa colisão (morte, término da fase ou coleta de item).
*/
//=========================================================================================
int JogadorCollision(Jogador_t *jogador, Inimigos_t *inimigo, int numInimigos, Projetil_t *projeteisInimigos, int numProjeteisInimigos, Fase_t mapa)
{
    Rectangle jogadorRect =
    {
        jogador->posicao.x,
        jogador->posicao.y,
        jogador->tamanho.x,
        jogador->tamanho.y
    };

    // Verifica colisão com inimigos
    for (int i = 0; i < numInimigos; i++)
    {
        Rectangle inimigoRect =
        {
            inimigo[i].posicao.x,
            inimigo[i].posicao.y,
            inimigo[i].tamanho.x,
            inimigo[i].tamanho.y
        };

        if (inimigo[i].tamanho.x > 0 && inimigo[i].tamanho.y > 0 && CheckCollisionRecs(jogadorRect, inimigoRect)) {
            return 1;
        }
    }

    //Verifica colisão com projétil inimigo
    for (int i = 0; i < numProjeteisInimigos; i++)
    {
        if (projeteisInimigos[i].ativo)
        {
            Rectangle projetilRect =
            {
                projeteisInimigos[i].posicao.x,
                projeteisInimigos[i].posicao.y,
                mapa.tamBloco,
                mapa.tamBloco
            };

            if (CheckCollisionRecs(jogadorRect, projetilRect))
            {
                projeteisInimigos[i].ativo = 0;
                return 2;
            }
        }
    }

    // Verifica colisão com elementos do cenário
    for (int col = 0; col < mapa.columnSize; col++)
    {
        for (int lin = 0; lin < mapa.lineSize; lin++)
        {
            char blocoAtual = mapa.mapa[lin][col];

            if (blocoAtual == 'O' || blocoAtual == 'W')
            {
                Vector2 blocoPos = { col * mapa.tamBloco, lin * mapa.tamBloco };
                Rectangle blocoRect =
                {
                    blocoPos.x,
                    blocoPos.y,
                    mapa.tamBloco,
                    mapa.tamBloco
                };

                if (CheckCollisionRecs(jogadorRect, blocoRect))
                {
                    return 3;
                }
            }
        }
    }

    return 0;
}
//=========================================================================================
/* ProcuraJogador: Fase_t, int -> Vector2
   Função para localizar a posição inicial do jogador em um mapa.

    Parâmetros:
   - mapa (Fase_t): Estrutura que representa a fase, contendo o mapa do jogo.
   - tamBloco (int): Tamanho de cada bloco do mapa, usado para calcular a posição em pixels.

    Objetivo:
    Procura a posição do jogador (representado pelo caractere 'P') no mapa e retorna a posição correspondente em pixels.

    Retorno:
   - Vector2: Estrutura contendo as coordenadas x e y da posição do jogador em pixels.
*/
//=========================================================================================
Vector2 ProcuraJogador(Fase_t mapa, int tamBloco)
{
	Vector2 position = { 0 };
	for(int i = 0; i < mapa.lineSize; i++)
	{
		for(int j = 0; j < mapa.columnSize; j++)
		{
			if(mapa.mapa[i][j] == 'P')
			{
				position.x = j * tamBloco;
				position.y = i * tamBloco;
			}
		}
	}
	return position;
}
//=========================================================================================
/* UpdatePlayer: Jogador_t*, Fase_t -> void
  Função para atualizar a posição e estado do jogador durante o jogo.

Parâmetros:
  - jogador (Jogador_t*): Ponteiro para a estrutura do jogador que será atualizada.
  - mapa (Fase_t): Estrutura contendo o mapa da fase atual.

Descrição:
  A função gerencia a movimentação do jogador, incluindo física de pulo e gravidade,
  colisão com obstáculos no mapa e coleta de itens. Também atualiza o estado do jogador
  conforme ele avança na fase ou morre.
*/
//=========================================================================================
void UpdatePlayer(Jogador_t *jogador, Fase_t mapa, Inimigos_t *inimigos, int numInimigos, Projetil_t *projeteisInimigos, int numProjeteisInimigos)
 {
    Vector2 oldPos = jogador->posicao;

    // Gerencia o estado do pulo
    Pulo(jogador);

    // Gerencia a gravidade com base no estado do pulo
    if (jogador->pulando)
    {
        jogador->gravidade.y = 1.8f;
    } else {
        jogador->gravidade.y = 0.5f;
    }
    jogador->velocidade.y += jogador->gravidade.y;

    // Define a velocidade horizontal
    jogador->velocidade.x = 5.0f;

    // Atualiza a posição horizontal do jogador
    jogador->posicao.x += jogador->velocidade.x;

    // Verifica colisões horizontais
    int collisionResult = JogadorCollision(jogador, inimigos, numInimigos, projeteisInimigos, numProjeteisInimigos, mapa);
    if (collisionResult == 1)
    {
        jogador->posicao = ProcuraJogador(mapa, mapa.tamBloco); // Reseta posição inicial
        jogador->tentativas++; // Incrementa tentativas
    } else if (collisionResult == 2)
    {
        jogador->posicao = ProcuraJogador(mapa, mapa.tamBloco); // Reseta posição inicial
        jogador->tentativas--; // Decrementa tentativas
    } else if (collisionResult == 3)
    {
        jogador->posicao = oldPos; // Impede movimento em direção ao elemento
        jogador->velocidade.x = 0; // Para o movimento horizontal
    }

    // Atualiza a posição vertical do jogador
    jogador->posicao.y += jogador->velocidade.y;

    // Verifica colisões verticais com elementos do cenário (ex: chão 'G')
    int isGrounded = 0;
    for (int col = 0; col < mapa.columnSize; col++)
    {
        for (int lin = 0; lin < mapa.lineSize; lin++)
        {
            if (mapa.mapa[lin][col] == 'G')
            {
                Vector2 blocoPos = { col * mapa.tamBloco, lin * mapa.tamBloco };
                Rectangle blocoRect =
                {
                    blocoPos.x, blocoPos.y, mapa.tamBloco, mapa.tamBloco
                };

                Rectangle jogadorRect =
                {
                    jogador->posicao.x, jogador->posicao.y, jogador->tamanho.x, jogador->tamanho.y
                };

                if (CheckCollisionRecs(jogadorRect, blocoRect))
                {
                    // Colisão com o chão
                    jogador->posicao.y = oldPos.y; // Reseta a posição vertical para a posição antiga
                    jogador->velocidade.y = 0;    // Interrompe o movimento vertical
                    jogador->pulando = 0;         // Reseta o estado de pulo
                    isGrounded = 1;               // Indica que o jogador está no chão
                    break;
                }
            }
        }
    }

    // Aplica gravidade adicional se o jogador não estiver no chão
    if (!isGrounded)
    {
        jogador->velocidade.y += jogador->gravidade.y;
    }

    // Atualiza o cooldown de coleta de itens
    if (jogador->cd > 0)
    {
        jogador->cd--;
    }
}
//=========================================================================================
/* InicializaJogador: Jogador_t*, int -> void
  Função para inicializar os dados do jogador no início de uma fase.

Parâmetros:
  - jogador (Jogador_t*): Ponteiro para a estrutura do jogador.
  - fase (int): ID da fase atual.
Objetivo:
  A função reinicia os dados do jogador, como a flag de pulo, o cooldown (coleta de item), e o número
  de tentativas, preparando para iniciar uma nova fase.
*/
//=========================================================================================
void InicializaJogador(Jogador_t *jogador, int fase)
{
    jogador->faseCompleta = 0;
    jogador->idFase = fase;
    jogador->andando = 0;
    jogador->pulando = 0;
    jogador->mirando = 1;
    jogador->atirando = 0;
    jogador->cd = 0;
    jogador->tentativas = 0;
    jogador->pts = 0;
}
