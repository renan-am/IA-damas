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

int protege (BOARD *tab, int c_origem, int l_origem){   //retorna numero de pedras aliadas protegidas por uma pedra nessa posição
	int tipo;
	tipo = tab[l_origem*COL_MAX+c_origem].tipo;

	if (tipo != 0)
		tipo = (tipo%2) + 1;   // converte 1 -> 2 e 2 -> 1 para checarSeCome pode funcionar.
	int count = 0;

	if (checaSeCome (tab, c_origem, l_origem, c_origem+1, l_origem+1, tipo))
		count++;
	if (checaSeCome (tab, c_origem, l_origem, c_origem-1, l_origem+1, tipo))
		count++;
	if (checaSeCome (tab, c_origem, l_origem, c_origem-1, l_origem-1, tipo))
		count++;
	if (checaSeCome (tab, c_origem, l_origem, c_origem+1, l_origem-1, tipo))
		count++;

	return count;
}





