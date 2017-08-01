#pragma once   //impede arquivo ser "included" varias vezes, evitando erro de multipla definição

#include "game_functions.c"
//#include "possiblePaths.c"
#include "funcaopracomer.c"
#include "funcaopracomerdamas.c"


void posicionarpedras (BOARD *tab);    //inicializa o tabuleiro, com pedras tipo 1 na parte superior e tipo 2 na parte inferior


void mover (BOARD *tab, int c_origem, int l_origem, int c_destino, int l_destino);  //move pedra da posicao de origem para a posiçao destino no tabuleiro *tab


int checarSeCome (BOARD *tab, int c_origem, int l_origem, int c_alvo, int l_alvo, int tipo);  // retorna 0 se a pedra nao puder ser comida, retorna 1 se puder. se int tipo = 0, sera usado o tipo da posicao de origem


void imprimir (BOARD *tab);    // imprime tabuleiro e legenda das linhas e colunas

int validar (BOARD *tab, int coluna, int linha);


int distancia (int l_origem, int tipo);   //retorna quantas linhas até a pedra virar damas (fim do tabuleiro)

BOARD *GAME (int c_origem, int l_origem, int c_destino, int l_destino, PATH *pedrascomidas);




PATH **EncontrarCaminho (BOARD *tabuleiro ,int posAtualX , int posAtualY, int type, int i);
PATH **EncontrarCaminhoDama (BOARD *tabuleiro ,int posAtualX , int posAtualY, int type, int i);
