#include "gerenciador_header.h"
#include "gerenciador_func.h"
#define GROUNDED 0
//=========================================================================================
/* AtualizarJogador: Jogador_t*, Fase_t -> void
  Fun��o para atualizar a posi��o e estado do jogador durante o jogo.

Par�metros:
  - jogador (Jogador_t*): Ponteiro para a estrutura do jogador que ser� atualizada.
  - mapa (Fase_t): Estrutura contendo o mapa da fase atual.

Descri��o:
  A fun��o gerencia a movimenta��o do jogador, incluindo f�sica de pulo e gravidade,
  colis�o com obst�culos no mapa e coleta de itens. Tamb�m atualiza o estado do jogador
  conforme ele avan�a na fase ou morre.
*/
//=========================================================================================
void UpdatePlayer(Jogador_t *jogador, Fase_t mapa)
{
    Vector2 oldPos = jogador ->posicao;
    Vector2 auxPos;

    Pulo(jogador);

    if(jogador->pulando)
    {
        jogador->gravidade.y = 1.8f;
    }

    if(jogador.->velocidade.y>0)
    {
        jogador.gravidade.y = 0.5f;
    }else
    {
        jogador.gravidade.y = 0.5f;
    }

    jogador ->velocidade.y += jogador->gravidade.y;
    jogador->velocidade.x = 5.0f;

    //ATUALIZA POSI��O
    jogador->posicao.x += jogador->velocidade.x;
    switch(SideCollision(mapa, jogador->posicao))
    {
        case 1:
            jogador->posicao = ProcuraJogador(mapa, mapa.tamBloco);
            jogador->tentativas++;
            break;
        case 2:
            jogador.faseCompleta = 1;
            break;
        case 3:
            if(!(jogador->cd))
            {
                jogador->pts += 100;
                jogador->cd = 120;
            }
    }
}
