#pragma once   //impede arquivo ser "included" varias vezes, evitando erro de multipla definição


//#include "possiblePaths.c"



void posicionarpedras (BOARD *tab);    //inicializa o tabuleiro, com pedras tipo 1 na parte superior e tipo 2 na parte inferior

void mover (BOARD *tab, int c_origem, int l_origem, int c_destino, int l_destino);  //move pedra da posicao de origem para a posiçao destino no tabuleiro *tab

int checarSeCome (BOARD *tab, int c_origem, int l_origem, int c_alvo, int l_alvo, int tipo);  // retorna 0 se a pedra nao puder ser comida, retorna 1 se puder. se int tipo = 0, sera usado o tipo da posicao de origem

void imprimir (BOARD *tab);    // imprime tabuleiro e legenda das linhas e colunas

int validar (BOARD *tab, int coluna, int linha);

void remover (BOARD *tab, PATH *pedrascomidas);

int distancia (int l_origem, int tipo);   //retorna quantas linhas até a pedra virar damas (fim do tabuleiro)

int checarAcao (BOARD *tab, int coluna, int linha, PIECES **usefulPieces, DYNAMICVEC *usefulPiecesParameters);

char checarJogada (BOARD *tab, int jogador, PIECES **usefulPieces, DYNAMICVEC *usefulPiecesParameters);

void usefulPiecesFunction (int line, int column, PIECES **usefulPieces, DYNAMICVEC *usefulPiecesParameters);

BOARD *GAME (int c_origem, int l_origem, int c_destino, int l_destino, PATH *pedrascomidas);

PATH **EncontrarCaminho (BOARD *tabuleiro ,int posAtualX , int posAtualY, int type, int i);
PATH **EncontrarCaminhoDama (BOARD *tabuleiro ,int posAtualX , int posAtualY, int type, int i);

DYNAMICVEC *goodPaths(BOARD *tab, int Xposition, int Yposition, int classe , int tipo);

DYNAMICVEC *selectiveClean(DYNAMICVEC *vector);

#include "game_functions.c"
#include "funcaopracomer.c"
#include "funcaopracomerdamas.c"
