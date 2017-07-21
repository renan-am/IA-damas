#include <stdio.h>
#include <stdlib.h>
#include "func_declarations.h"

void posicionarpedras (BOARD *tab){   //inicializa o tabuleiro, com pedras tipo 1 na parte superior e tipo 2 na parte inferior
	int linha, coluna;

	for (linha = 0; linha < LIN_MAX; linha++)
		for (coluna = 0; coluna < COL_MAX; coluna++){
			tab[POS].tipo = 0;
		}

	for (linha = 0; linha < 3; linha++)
		for (coluna = (linha+1)%2; coluna < COL_MAX; coluna += 2){	// (linha+1) % 2 garante que as casas serão alternadas, ex: 1ª linha as casas pretas começam na 2ª coluna, 2ª linha começam na 1ª coluna, etc.
			tab[POS].tipo = 1;
		}

	for (linha = 5; linha < LIN_MAX; linha++)
		for (coluna = (linha+1)%2; coluna < COL_MAX; coluna += 2){	// (linha+1) % 2 garante que as casas serão alternadas, ex: 1ª linha as casas pretas começam na 2ª coluna, 2ª linha começam na 1ª coluna, etc.
			tab[POS].tipo = 2;
		}
}

void mover (BOARD *tab, int c_origem, int l_origem, int c_destino, int l_destino){    //move pedra da posicao de origem para a posiçao destino no tabuleiro *tab
	int aux;
	aux = tab[l_origem*COL_MAX+c_origem].tipo;
	tab[l_origem*COL_MAX+c_origem].tipo = tab[l_destino*COL_MAX+c_destino].tipo;
	tab[l_destino*COL_MAX+c_destino].tipo = aux;
}

int checarSeCome (BOARD *tab, int c_origem, int l_origem, int c_alvo, int l_alvo, int tipo){    // retorna 0 se a pedra nao puder ser comida, retorna 1 se puder. se int tipo = 0, sera usado o tipo da posicao de origem
	if (tipo == 0)
		tipo = tab[l_origem*COL_MAX+c_origem].tipo;

	int c_final = 0, l_final = 0;
	c_final = 2 * c_alvo - c_origem;
	l_final = 2 * l_alvo - l_origem;

	if (tipo == tab[l_alvo*COL_MAX+c_alvo].tipo)
		return 0;
	else if (c_final < 0 || l_final < 0 || c_final >= COL_MAX || l_final >= LIN_MAX)
		return 0;
	else if (tab[l_final*COL_MAX+c_final].tipo != 0)
		return 0;
	else
		return 1;
}


void comer (int c_origem, int l_origem, int c_destino, int l_destino){
}


void imprimir (BOARD *tab){ // imprime tabuleiro e legenda das linhas e colunas
	int linha, coluna;
	
	for (linha = 0; linha < LIN_MAX+2; linha++){
		
		if (linha == LIN_MAX){  // pula uma linha para separar a legenda das colunas
				printf("\n");
				continue;
		}


		for (coluna = 0; coluna < COL_MAX; coluna++){
			if (linha == LIN_MAX+1){           // imprime legenda da coluna e ignora o resto do loop
				printf ("%d ", coluna+1);
				continue;
			}


			if (tab[POS].tipo != 0){     //imprime as pedras e substitui 0 por espaços em branco
				printf ("%d ", tab[POS].tipo);
			} else {
				printf("  ");
			}
		}
		printf("  %d\n", linha+1);
	}  
}