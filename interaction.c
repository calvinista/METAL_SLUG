#include "gerenciador_header.h"
#include "gerenciador_func.h"
//=========================================================================================
/* MenuInteraction: Cena_t, Vector2 -> int
  Dada uma Cena e um Vetor2D, retorna um inteiro.
  Considerando a posi��o do vetor, verifica se o mesmo est� colidindo atr�ves da flag de "hover"
se sim e o bot�o esquerdo do mouse for clicado, retorna um valor especifico para cada �ndice.
  Utilizado como controlador do menu principal.
*/
//=========================================================================================
int MenuInteraction(Cena_t menu, Vector2 mousePos){
  for(int i = 0; i < OPCOES_MENU; i++){
    if(menu.hover[i]){
      if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        switch(i){
        case 0:
          return 1; // Iniciar jogo
          break;
        case 1:
          return 2; // Abrir leaderboard
          break;
        case 2:
          return 3; // Fechar o jogo
          break;
        default:
          break;
        }
      }
    }
  }
  return 0; // Retorno padr�o
}

//=========================================================================================
/* ParallaxCounterControl: Vector2*, Tela_t -> void
  Dado um vetor de duas posi��es (x,y) e os par�metros da tela, atualiza o vetor com valores
  espec�ficos.
  Utilizado para controlar o sistema de Parallax durante o jogo.
*/
//=========================================================================================
void ParallaxCounterControl(Vector2 *counter, Tela_t param){
	counter->x -= 0.5f;
	counter->y -= 0.5f;
	if(counter->x <= -param.largura) counter->x = param.largura;
	if(counter->y <= -param.largura*2) counter->y = 0;
}
