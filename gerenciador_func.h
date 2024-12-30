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
//=========================================================================================
// Structure Update Controllers
//=========================================================================================
void PreencheMenuInicial(Cena_t *cena, Tela_t param);
void InicializaJogador(Jogador_t *jogador, int fase)
void AtualizaRecordeAtual(Record *novo, Jogador_t ref);
void AnimationMenu(Cena_t *cena, Vector2 mousePos);
int MenuInteraction(Cena_t menu, Vector2 mousePos);
int RecebeNomeJogador(Record *novoRecorde, Nome_t *dados, Jogador_t jogador, int *encerrar);
Vector2 ProcuraJogador(Fase_t mapa, int tamBloco);

int JogadorEntraNoRanking(Record novo, LevelData *fases, int n);
//=========================================================================================
// Movement and Physics
//=========================================================================================
void AtualizarJogador(Jogador_t *jogador, Fase_t mapa);
void Pulo(Jogador_t *jogador);
void Atira(Jogador_t *jogador, Projetil_t *projetil, int *numProjeteis);
void Agachar(Jogador_t *jogador);
void Mirar(Jogador_t *jogador);
void ColetarItens(Jogador_t *jogador, Fase_t *fase);
void ParallaxCounterControl(Vector2 *counter, Tela_t param);
void BulletCollision(Projetil_t *projetil, int numProjeteis, Inimigos_t *inimigo, int numInimigos, Fase_t mapa, Jogador_t *jogador);
int JogadorCollision(Jogador_t *jogador, Inimigos_t *inimigo, int numInimigos, Projetil_t *projeteisInimigos, int numProjeteisInimigos, Fase_t mapa);
//=========================================================================================
// Front-End Elements
//=========================================================================================
void DesenharJogador(Jogador_t jogador, Rectangle source);
void DesenhaScores(Scores_t leaderboards, int i);
void DesenhaMenu(Cena_t cena, int n);
void DesenhaFase(Fase_t fase, int cooldown);
void DesenhaTelaInput(Nome_t dados, Tela_t param);
void DesenhaSeletorLevel(int *selectedLevel, Tela_t param, Gerenciador_e *gerenciador);
void DesenhaFundoParallax(Texture2D background, Vector2 counter, Tela_t param);

void PaginationControl(Scores_t *leaderboards);
//=========================================================================================
// File Managers (CRUD)
//=========================================================================================
void CreateBinaryFile(const char *filename);
void ReadBinaryFile(const char *filename, LevelData levels[TAM]);
void UpdateLevelData(LevelData *levels, int level_id, Record *newTop5);
void WriteBinaryFile(const char *filename, LevelData levels[TAM]);
int ReadFileDataEx(const char *path, Fase_t *mapa);
#endif // GERENCIADOR_FUNC_H_INCLUDED
