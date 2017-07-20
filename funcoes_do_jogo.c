#include <stdio.h>
#include <stdlib.h>
#include "module.h"



void posicionarpedras (){
	int linha, coluna;

	for (linha = 0; linha < LIN_MAX; linha++)
		for (coluna = 0; coluna < COL_MAX; coluna++){
			tabuleiro[POS].tipo = 0;
		}

	for (linha = 0; linha < 3; linha++)
		for (coluna = (linha+1)%2; coluna < COL_MAX; coluna += 2){	// (linha+1) % 2 garante que as casas serão alternadas, ex: 1ª linha as casas pretas começam na 2ª coluna, 2ª linha começam na 1ª coluna, etc.
			tabuleiro[POS].tipo = 1;
		}

	for (linha = 5; linha < LIN_MAX; linha++)
		for (coluna = (linha+1)%2; coluna < COL_MAX; coluna += 2){	// (linha+1) % 2 garante que as casas serão alternadas, ex: 1ª linha as casas pretas começam na 2ª coluna, 2ª linha começam na 1ª coluna, etc.
			tabuleiro[POS].tipo = 2;
		}
}

void mover (int c_origem, int l_origem, int c_destino, int l_destino){
	int aux;
	aux = tabuleiro[l_origem*COL_MAX+c_origem].tipo;
	tabuleiro[l_origem*COL_MAX+c_origem].tipo = tabuleiro[l_destino*COL_MAX+c_destino].tipo;
	tabuleiro[l_destino*COL_MAX+c_destino].tipo = aux;
}

int checarSeCome (int c_origem, int l_origem, int c_alvo, int l_alvo){    // retorna 0 se a pedra nao puder ser comida, retorna 1 se puder. 
	int c_final = 0, l_final = 0;
	c_final = 2 * c_alvo - c_origem;
	l_final = 2 * l_alvo - l_origem;

	if (c_final < 0 || l_final < 0 || c_final >= COL_MAX || l_final >= LIN_MAX)
		return 0;
	else if (tabuleiro[l_final*COL_MAX+c_final].tipo != 0)
		return 0;
	else
		return 1;
}


void comer (int c_origem, int l_origem, int c_destino, int l_destino){
}


void imprimir (){ // imprime tabuleiro e legenda das linhas e colunas
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


			if (tabuleiro[POS].tipo != 0){     //imprime as pedras e substitui 0 por espaços em branco
				printf ("%d ", tabuleiro[POS].tipo);
			} else {
				printf("  ");
			}
		}
		printf("  %d\n", linha+1);
	}  
}