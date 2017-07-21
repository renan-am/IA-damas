#include <stdio.h>
#include <stdlib.h>
#include <func_declarations.h>


int distancia (int l_origem, int tipo){  //retorna quantas linhas até a pedra virar damas (fim do tabuleiro)
	if (tipo == 1)
		return l_origem; 
	else if (tipo == 2)
		return (LIN_MAX - l_origem);
	else
		printf ("func distancia recebeu tipo invalido (%d)", int tipo);
		return -1;
}