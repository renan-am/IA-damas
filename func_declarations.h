#pragma once   //impede arquivo ser "included" varias vezes, evitando erro de multipla definição

#include "game_functions.c"
//#include "possiblePaths.c"

void PossiblePaths(int posAtualX , int posAtualY);


void posicionarpedras (BOARD *tab);


void mover (BOARD *tab, int c_origem, int l_origem, int c_destino, int l_destino);


int checarSeCome (BOARD *tab, int c_origem, int l_origem, int c_alvo, int l_alvo);


void imprimir (BOARD *tab);