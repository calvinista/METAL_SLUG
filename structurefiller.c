#include "gerenciador_header.h"
#include "gerenciador_func.h"
//=========================================================================================
/* PreencheMenuInicial: Cena_t*, Tela_t -> void
   Fun��o para inicializar e configurar os elementos do menu principal de um jogo.

Par�metros:
   - cena (Cena_t*): Ponteiro para a estrutura 'Cena_t' que armazena os dados da cena atual, incluindo strings do menu, bot�es e par�metros de texto.
   - param (Tela_t): Estrutura 'Tela_t' que cont�m as dimens�es da tela (largura e altura), utilizada para centralizar e posicionar os elementos do menu.
Objetivo:
   Inicializa as strings do menu, posiciona e dimensiona os bot�es e outros elementos visuais.
Detalhes:
   - As op��es do menu ("Play", "LeaderBoard", "Quit") s�o centralizadas horizontalmente e espa�adas verticalmente com base no tamanho da fonte e no espa�amento definido.
   - O bot�o de retorno da tela de 'LeaderBoards' e o bot�o de 'Reiniciar' tamb�m s�o configurados com base nas dimens�es da tela.
   - A caixa de texto para entrada de nome � dimensionada e posicionada adequadamente na tela.
*/
//=========================================================================================
void PreencheMenuInicial(Cena_t *cena, Tela_t param)
{

    char *string[3] =
    {
        "Play",
        "LeaderBoard",
        "Quit"
    };
    float verticalSpacing = 10; // Dado de front-end para design.

    // Define um tamanho de fonte.
    cena->fontSize = 45;

    for(int i = 0; i < OPCOES_MENU; i++)
    {
        // Copia as strings para a estrutura base.
        strncpy(cena->string[i], string[i], STRING_MAX_SIZE - 1);
        cena->string[i][STRING_MAX_SIZE - 1] = '\0';

        // Preenche os dados dos ret�ngulos conforme o tamanho das strings de entrada.
        float rectWidth = MeasureText(cena->string[i], cena->fontSize);

        cena->botoes[i].width = rectWidth;
        cena->botoes[i].height = cena->fontSize;
        cena->botoes[i].x = (param.largura - rectWidth) / 2;  // Centraliza horizontalmente
        cena->botoes[i].y = (param.altura / 1.5f) - ((OPCOES_MENU * (cena->fontSize) + (OPCOES_MENU - 1) * verticalSpacing) / 2)
                            + i * (cena->fontSize + verticalSpacing);  // Posiciona verticalmente com espa�amento

        // Defini��o de cores
        cena->textColor[i] = YELLOW;

        // Defini��o do bot�o de retorno da tela de LeaderBoards;
        cena->scores.retorno = (Rectangle)
        {
            param.largura - MeasureText("Voltar", 30) - 20, param.altura - 60, MeasureText("Voltar", 30)+ 4, 34
        };
        cena->scores.reset = (Rectangle)
        {
            20, param.altura - 60, MeasureText("Reiniciar", 30)+4, 34
        };

        cena->nome.caixaTexto = (Rectangle)
        {
            param.largura/2.0f - (param.largura * 0.3f), 180, param.largura * 0.6f, 50
        };
        cena->nome.nome[NOME_TAM_MAX] = '\0';
    }
}
