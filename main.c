#include "gerenciador_header.h"
#include "gerenciador_func.h"
int main()
{
    // DECLARAÇÃO E INICIALIZAÇÃO DE VARIÁVEIS:
    Gerenciador_e telaAtual = MENU;
    Tela_t telaTam = { SCREEN_WIDTH, SCREEN_HEIGHT };
    Cena_t menuInicial = {0};
    Jogador_t jogador = {0};
    //Record_t refNull = { 0 };
    //Record_t novoRecord = { 0 };
    Vector2 parallaxControler = {0};
    int nivelSelecionado = -1;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(FPS);

    Texture2D bg [3] = {0};

    // Inicializa câmera
    Camera2D camera = {0};
    camera.offset = (Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, };
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;

    camera.target = (Vector2)
    {
        jogador.posicao.x + jogador.tamanho.x / 2,
        jogador.posicao.y + jogador.tamanho.y /2
    };

    if(jogador.pulando)
    {
        camera.target.y -= 50; //reposiciona a camera p/ cima enqunato o jogador estiver no pulando
    }

    if(jogador.mirando)
    {
        if(jogador.mirando == 2)
        {
            camera.target.y -= 100;
        }
        else if(jogador.mirando == 3)
        {
            camera.target.y += 50;
        }
    }

    // Se o arquivo não existe cria depois lê
    if(!(FileExists("records.bin")))
    {
        CreateBinaryFile("records.bin");
    }
    ReadBinaryFile("records.bin", menuInicial.scores.fases);

    // Preenchimento do menu inicial
    PreencheMenuInicial(&menuInicial, telaTam);
    menuInicial.texTitle = LoadTexture("Sprites/LOGO/metal_inf");
    menuInicial.background = LoadTexture("Sprites/LOGO/background.png");

    // Carrega fundo das fases
    for(int i=0; i<3; i++)
    {
        bg[i] = LoadTexture(TextFormat("Sprites/BACKGROUND/Mission%d.png", i+1));
    }

    Rectangle source = {0, 0, 60, 60};
    jogador.tex = LoadTexture("Sprites/PLAYER/standing.png");

    while(!WidowShouldClose() && !menuInicial.encerrarJogo)
    {
        // Atualiza câmera em relação a posição do jogador
        camera.target = jogador.posicao;
        // Atalho MENU
        if(IsKeyDown(KEY_M))
            telaAtual = MENU;
        //=========================================================================================
        // Área de atualização de dados: (Back-end)
        //=========================================================================================
        switch(telaAtual)
        {
            case MENU:
                AnimationMenu(menuInicial, GetMousePosition());
                switch(MenuInteraction(menuInicial, GetMousePosition()))
                {
                    case 1:
                        telaAtual = SELECAO;
                        break;
                    case 2:
                        //ReadBinaryFile("records.bin", menuInicial.scores.fase);
                        menuInicial.scores.desenhaScore = 1;
                        menuInicial.menuLock = 1;
                        break;
                    case 3:
                        menuInicial.encerrarJogo = 1;
                        break;
                    default:
                        break;
                }
                break;
                // PRECISA DESENHAR AS FASES EM ARQ. TXT
                    case SELECAO:
                        if(nivelSelecionado != -1)
                        {
                            ReadFileDataEx(TextFormat(""))
                        }
        }
    }
    return 0;
}
