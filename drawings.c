#include "gerenciador_header.h"
#include "gerenciador_func.h"

//=========================================================================================
/* DesenhaMenu: Cena_t, int -> void
  Função para desenhar o menu na tela.

Parâmetros:
  - cena (Cena_t): Estrutura contendo os dados da cena, como texturas e botões.
  - n (int): Número de botões a serem desenhados.
Objetivo:
  Desenha o background, o título e os botões do menu na tela.
*/
//=========================================================================================
void DesenhaMenu(Cena_t cena, int n)
{
    DrawTexture(cena.background, 0, 0, WHITE);
    DrawTexture(cena.texTitle, SCREEN_WIDTH/2 - cena.texTitle.width/2, SCREEN_HEIGHT*0.01f, WHITE);
    for(int i=0; i<n; i++)
    {
        DrawRectangleRec(cena.botoes[i], (Color)
        {
            0,0,0,0
        });
        DrawText(cena.string[i], cena.botoes[i].x, cena.botoes[i].y, cena.fontSize, cena.textColor[i]);
    }
}
//=========================================================================================
/* DesenhaFase: Fase_t, int -> void
  Função para desenhar a fase do jogo na tela.

Parâmetros:
  - fase (Fase_t): Estrutura contendo os dados da fase, como mapa e tamanho dos blocos.
  - cooldown (int): Flag para indicar se o cooldown está ativo.
Objetivo:
  Desenha os blocos da fase, incluindo obstáculos, pontos de início e fim, e moedas (dependendo do cooldown).
*/
//=========================================================================================
/*void DesenhaFase(Fase_t fase, int cooldown)
{
    for(int i=0; i< fase.lineSize; i++)
    {
        for(int j=0; j<fase.columnSize; j++)
        {
            Rectangle rect = {j*fase.tamBloco, i*fase.tamBloco, fase.tamBloco, fase.tamBloco};
            if(fase.mapa[i][j] = 'B')
            {
                DrawRectangleRec(rect, BLANK);
                DrawRectangleLinesEx(rect, 2, DARKGRAY);
            }
            if(fase.mapa[i][j]=='')

        }
    }
}*/

//=========================================================================================
/* DesenhaTelaInput: Nome_t, Tela_t -> void
  Função para desenhar a tela de entrada de nome na tela.

Parâmetros:
  - dados (Nome_t): Estrutura contendo os dados de entrada do nome.
  - param (Tela_t): Estrutura contendo os parâmetros da tela, como largura e altura.
Objetivo:
  Desenha as instruções para o usuário, a caixa de texto para inserção do nome, e mensagens de confirmação ou aviso.
*/
//=========================================================================================
void DesenhaTelaInput(Nome_t dados, Tela_t param)
{
    const char *congrats = "Parabéns soldado(a)! Você entrou no Top 5 da fase!";
    const char *inst = "Coloque o mouse sobre barra de texto";
    const char *confirm = "Pressione ENTER para enviar seu recorde!";
    const char *warning = "Pressione BACKSPACE para deletar letras...";

    DrawText(congrats, param.largura/2 - MeasureText(congrats, 20)/2, param.altura * 0.2f, 20, GREEN);
    DrawText(inst, param.largura / 2 - MeasureText(inst, 20)/2, param.altura * 0.2f + 20, 20, GRAY);
    DrawRectangleRec(dados.caixaTexto, LIGHTGRAY);
    DrawText(
        TextFormat("Quantidade de Caracteres: %i/%i", dados.contaLetras, NOME_TAM_MAX),
        param.largura / 2 - MeasureText(TextFormat("Quantidade de Caracteres: %i/%i", dados.contaLetras, NOME_TAM_MAX), 20)/2,
        dados.caixaTexto.y + (dados.caixaTexto.height * 2),
        20,
        DARKGRAY
    );
    if(dados.mouseSobreCaixa)
    {
        DrawRectangleLines(
            (int)dados.caixaTexto.x,
            (int)dados.caixaTexto.y,
            (int)dados.caixaTexto.width,
            (int)dados.caixaTexto.height,
            DARKGREEN);
    }
    else
    {
        DrawRectangleLines(
            (int)dados.caixaTexto.x,
            (int)dados.caixaTexto.y,
            (int)dados.caixaTexto.width,
            (int)dados.caixaTexto.height,
            DARKGRAY);
    }

    if(dados.contaLetras > 0)
    {
        DrawText(dados.nome, (int)dados.caixaTexto.x + 5, (int)dados.caixaTexto.y + 8, 40, MAROON);
        DrawText(confirm, param.largura/2 - MeasureText(confirm, 20)/2, param.altura * 0.08f, 20, GRAY);
    }

    if(dados.mouseSobreCaixa)
    {
        if(dados.contaLetras < NOME_TAM_MAX)
        {
            if(((dados.contaFrame/20)%2)==0)
            {
                DrawText("_", dados.caixaTexto.x + 8 + MeasureText(dados.nome, 40), (int)dados.caixaTexto.y + 12, 40, MAROON);
            }
            else
            {
                DrawText(warning, param.largura/2 - MeasureText(warning, 20)/2, param.altura - 20, 20, GRAY);
            }
        }
    }
}
//=========================================================================================
/* DesenhaScores: Scores_t, int -> void
  Função para desenhar os scores na tela.

Parâmetros:
  - leaderboards (Scores_t): Estrutura contendo os dados do leaderboard.
  - i (int): Índice do nível que está sendo exibido.
Objetivo:
  Desenha a lista de melhores scores para o nível selecionado, junto com os botões de retorno e reset.
*/
//=========================================================================================
void DesenhaScores(Scores_t leaderboards, int i)
{
    if(leaderboards.desenhaScore)
    {
        //PRÉ-ALINHAMENTO NO CENTRO DA TELA
        int y = SCREEN_HEIGHT / 4 + 80;
        int fontSize = 40;

        DrawRectangleRec((Rectangle)
        {
            0, y, SCREEN_WIDTH, SCREEN_HEIGHT - y
        }, BLACK);

        // FASES E PONTUAÇÃO
        char levelText[50];
        snprintf(levelText, sizeof(levelText), "Level %d", leaderboards.fases[i].level_id);
        int textWidth = MeasureText(levelText, fontSize);
        DrawText(levelText, SCREEN_WIDTH / 2 - textWidth / 2, y, fontSize, GREEN);
        y += 100;

        for(int j = 0; j < 5; j++)
        {
            char scoreText[100];
            snprintf(scoreText, sizeof(scoreText), "%s -> Tentativas: %d",
                     leaderboards.fases[i].top5[j].name,
                     leaderboards.fases[i].top5[j].pts);

            int scoreTextWidth = MeasureText(scoreText, fontSize);
            DrawText(scoreText, SCREEN_WIDTH / 2 - scoreTextWidth / 2, y, fontSize, GREEN);
            y += 50;
        }


        DrawRectangleRec(leaderboards.retorno, RED);
        DrawRectangleLinesEx(leaderboards.retorno, 1, MAROON);
        DrawText(TextFormat("Voltar"), leaderboards.retorno.x+2, leaderboards.retorno.y, 30, GREEN);

        DrawRectangleRec(leaderboards.reset, RED);
        DrawRectangleLinesEx(leaderboards.reset, 1, MAROON);
        DrawText(TextFormat("Reiniciar"), leaderboards.reset.x+2, leaderboards.reset.y, 30, GREEN);
    }
}
//=========================================================================================
/* AnimationMenu: Cena_t*, Vector2 -> void
  Função para animar os elementos do menu.

Parâmetros:
  - cena (Cena_t*): Ponteiro para a estrutura contendo os dados da cena.
  - mousePos (Vector2): Posição atual do mouse.
Objetivo:
  Atualiza a cor dos textos e o estado de hover dos botões com base na posição do mouse.
*/
//=========================================================================================
void AnimationMenu(Cena_t *cena, Vector2 mousePos)
{
    if(!cena->menuLock)
    {
        for(int i = 0; i < OPCOES_MENU; i++)
        {
            if(CheckCollisionPointRec(mousePos, cena->botoes[i]))
            {
                cena->hover[i] = 1;
            }
            else
            {
                cena->hover[i] = 0;
            }

            if(cena->hover[i])
            {
                cena->textColor[i] = GREEN;
            }
            else
            {
                cena->textColor[i] = DARKGREEN;
            }
        }
    }


    if(cena->scores.desenhaScore)
    {
        //RETORNA AO MENU E E REMOVE O LOCK
        if(CheckCollisionPointRec(mousePos, cena->scores.retorno))
        {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                cena->menuLock = 0;
                cena->scores.desenhaScore = 0;
                cena->hover[1] = 0;
            }
        }
        // RESETA OS DADOS DO LEADERBOARD.
        if(CheckCollisionPointRec(mousePos, cena->scores.reset))
        {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                CreateBinaryFile("records.bin");
            }
        }
        //   PaginationControl(&cena->scores);
    }
}
//=========================================================================================
/* DesenhaSeletorFase: int*, Tela_t, Gerenciador_e* -> void
  Função para desenhar o seletor de nível na tela.

Parâmetros:
  - selectedLevel (int*): Ponteiro para a variável que armazena o nível selecionado.
  - param (Tela_t): Estrutura contendo os parâmetros da tela, como largura e altura.
  - gerenciador (Gerenciador_e*): Ponteiro para a variável que gerencia o estado atual do jogo.
Objetivo:
  Desenha os botões de seleção de nível na tela e permite o jogador selecionar um nível ou voltar ao menu principal.
*/
//=========================================================================================
void DesenhaSeletorFase(int *selectedLevel, Tela_t param, Gerenciador_e *gerenciador)
{
    const int numFase = 3;

    Rectangle levelButtons[numFase];
    Rectangle backButton;

    int buttonWidth = 200;
    int buttonHeight = 60;
    int spacing = 20;
    //CALCULO POSICIONAL E DE ESPAÇAMENTO DOS BOTÕES HORIZONTALMENTE
    int totalWidth = numFase*(buttonWidth+spacing) - spacing;
    int startX = (param.largura - totalWidth);
    int buttonY = param.altura / 2 - buttonHeight / 2;

    //SELETORES DE FASE
    for(int i=0; i<numFase; i++)
    {
        levelButtons[i].x = startX + i*(buttonWidth+spacing);
        levelButtons[i].y = buttonY;
        levelButtons[i].width = buttonWidth;
        levelButtons[i].height = buttonHeight;
    }

    //RETORNO
    backButton.x = (param.largura - buttonWidth)/2;
    backButton.y = param.altura - buttonHeight - spacing;
    backButton.width = buttonWidth;
    backButton.height = buttonHeight;

    DrawRectangleRec((Rectangle)
    {
        0, 0, param.largura, param.altura
    }, (Color)
    {
        0, 0, 0, 64
    });

    for(int i=0; i<numFase; i++)
    {
        if(CheckCollisionPointRec(GetMousePosition(), levelButtons[i]))
        {
            DrawRectangleRec(levelButtons[i], DARKBLUE);
            DrawRectangleLinesEx(levelButtons[i], 2, BLUE);

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                *selectedLevel = i+1;
            }
            else
            {
                DrawRectangleRec(levelButtons[i], DARKGRAY);
            }

            DrawText(TextFormat("Mission %d", i+1),
                     levelButtons[i].x + buttonWidth / 2 - MeasureText(TextFormat("Mission %d", i+1), 20)/2,
                     levelButtons[i].y + buttonHeight / 2 -10, 20, RAYWHITE);
        }

        if(CheckCollisionPointRec(GetMousePosition(), backButton))
        {
            DrawRectangleRec(backButton, DARKBLUE);
            DrawRectangleLinesEx(backButton, 2, BLUE);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                // VOLTA PRO MENU
                *gerenciador = MENU;
            }
        }
        else
        {
            DrawRectangleRec(backButton, DARKGRAY);
        }

        DrawText("Back to Menu",
        backButton.x + buttonWidth / 2 - MeasureText("Back to Menu", 20) / 2,
        backButton.y + buttonHeight / 2 - 10, 20, RAYWHITE);
    }
}
//=========================================================================================
/* DesenharJogador: Jogador_t, Rectangle -> void
  Função para desenhar o jogador na tela.

Parâmetros:
  - jogador (Jogador_t): Estrutura contendo os dados do jogador.
  - source (Rectangle): Área da textura a ser desenhada.
Objetivo:
  Desenha a textura do jogador na tela.
*/
//=========================================================================================
void DesenhaJogador(Jogador_t jogador, Rectangle source)
{
    DrawTextureRec(jogador.tex, source, jogador.posicao, WHITE);
}
//=========================================================================================
/* PaginationControl: Scores_t* -> void
  Função para controlar a navegação entre páginas do leaderboard.

Parâmetros:
  - leaderboards (Scores_t*): Ponteiro para a estrutura contendo os dados do leaderboard.
Objetivo:
  Permite a navegação entre as páginas do leaderboard utilizando as teclas de seta esquerda e direita.
*/
//=========================================================================================
void PaginationControl(Scores_t *leaderboards)
{
  if(IsKeyPressed(KEY_RIGHT))
    {
        if(leaderboards->pagina == 4)
        {
          leaderboards->pagina = 4;
        } else
        {
          leaderboards->pagina++;
        }
  }

  if(IsKeyPressed(KEY_LEFT))
  {
        if(leaderboards->pagina == 0)
        {
          leaderboards->pagina = 0;
        }
        else
        {
          leaderboards->pagina--;
        }
  }
}
