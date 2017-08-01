#include <stdio.h>
#include <stdlib.h>
#include "func_declarations.h"

BOARD *GAME (int c_origem, int l_origem, int c_destino, int l_destino, PATH *pedrascomidas){
	static int jogoiniciou = 0;     //inicializa tabuleiro somente uma vez
	static BOARD *tabuleiro;


	if (!jogoiniciou){
		tabuleiro = calloc (COL_MAX*LIN_MAX, sizeof(BOARD));
		//posicionarpedras(tabuleiro);


		int vet[COL_MAX*LIN_MAX] =     {0, 1, 0, 1, 0, 1, 0, 1,
						0, 0, 0, 0, 1, 0, 1, 0,
						0, 0, 0, 1, 0, 0, 0, 1,
						1, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 2, 0, 1,
						2, 0, 2, 0, 2, 0, 2, 0,
						0, 2, 0, 0, 0, 0, 0, 0,
						2, 0, 1, 0, 2, 0, 2, 0,
						};

		for (int linha = 0; linha < LIN_MAX; linha++)
			for (int coluna = 0; coluna < COL_MAX; coluna++){
				tabuleiro[POS].tipo = vet[POS];
				if (vet[POS] == 2)
				tabuleiro[POS].classe = 1;
				else
				tabuleiro[POS].classe = vet[POS];
			}


		

		jogoiniciou = 1;
		system ("tput reset");
		imprimir(tabuleiro);
	}


	if (c_origem == l_origem && l_origem == c_destino && c_destino == l_destino && c_origem == 0){
		return tabuleiro;
	}

	if (validar (tabuleiro, c_origem, l_origem) < 1  || validar (tabuleiro, c_destino, l_destino) != 0){
		//printf ("*game recebeu valorimpróprio\nc_origem = %d    l_origem = %d\nc_destino = %d    l_destino = %d\n", c_origem, l_origem, c_destino, l_destino);
		return NULL;
	}

	mover (tabuleiro, c_origem, l_origem, c_destino, l_destino);
	turno = (turno%2)+1;


	if (pedrascomidas){
		remover (tabuleiro, pedrascomidas);
	}

	for (int coluna = 0; coluna < COL_MAX; coluna++){
		int linha = 0;
		if (tabuleiro[POS].tipo == 2 && tabuleiro[POS].classe == 1)
			tabuleiro[POS].classe = 2;
		linha = 7;
		if (tabuleiro[POS].tipo == 1 && tabuleiro[POS].classe == 1)
			tabuleiro[POS].classe = 2;
	}

	system ("tput reset");
	imprimir(tabuleiro);
	return tabuleiro;
}


void posicionarpedras (BOARD *tab){   //inicializa o tabuleiro, com pedras tipo 1 na parte superior e tipo 2 na parte inferior
	int linha, coluna;

	for (linha = 0; linha < LIN_MAX; linha++)
		for (coluna = 0; coluna < COL_MAX; coluna++){
			tab[POS].tipo = 0;
		}

	for (linha = 0; linha < 3; linha++)
		for (coluna = (linha+1)%2; coluna < COL_MAX; coluna += 2){	// (linha+1) % 2 garante que as casas serão alternadas, ex: 1ª linha as casas pretas começam na 2ª coluna, 2ª linha começam na 1ª coluna, etc.
			tab[POS].tipo = 1;
			tab[POS].classe = 1;
		}

	for (linha = 5; linha < LIN_MAX; linha++)
		for (coluna = (linha+1)%2; coluna < COL_MAX; coluna += 2){	// (linha+1) % 2 garante que as casas serão alternadas, ex: 1ª linha as casas pretas começam na 2ª coluna, 2ª linha começam na 1ª coluna, etc.
			tab[POS].tipo = 2;
			tab[POS].classe = 1;

		}
	for (linha = 0; linha < LIN_MAX; linha++)
			for (coluna = linha%2; coluna < COL_MAX; coluna += 2)
				tab[POS].tipo = -1;
}

void mover (BOARD *tab, int c_origem, int l_origem, int c_destino, int l_destino){    //move pedra da posicao de origem para a posiçao destino no tabuleiro *tab
	int aux;
	aux = tab[l_origem*COL_MAX+c_origem].tipo;
	tab[l_origem*COL_MAX+c_origem].tipo = tab[l_destino*COL_MAX+c_destino].tipo;
	tab[l_destino*COL_MAX+c_destino].tipo = aux;

	aux = tab[l_origem*COL_MAX+c_origem].classe;
	tab[l_origem*COL_MAX+c_origem].classe = tab[l_destino*COL_MAX+c_destino].classe;
	tab[l_destino*COL_MAX+c_destino].classe = aux;
}

int validar (BOARD *tab, int coluna, int linha){
	if (coluna < 0 || coluna >= COL_MAX || linha < 0 || linha >= LIN_MAX)
		return -2;
	else
		return tab[POS].tipo;
}

int checarSeCome (BOARD *tab, int c_origem, int l_origem, int c_alvo, int l_alvo, int tipo){    // retorna 0 se a pedra nao puder ser comida, retorna 1 se puder. se int tipo = 0, sera usado o tipo da posicao de origem
	if (tipo == 0)
		tipo = tab[l_origem*COL_MAX+c_origem].tipo;

	int c_final = 0, l_final = 0;
	c_final = 2 * c_alvo - c_origem; 
	l_final = 2 * l_alvo - l_origem; 

	if (c_final < 0 || l_final < 0)
		return 0;
	else if (tab[l_alvo*COL_MAX+c_alvo].tipo <= 0)
		return 0;
	else if (tipo == tab[l_alvo*COL_MAX+c_alvo].tipo)
		return 0;
	else if (c_final < 0 || l_final < 0 || c_final >= COL_MAX || l_final >= LIN_MAX)
		return 0;
	else if (tab[l_final*COL_MAX+c_final].tipo != 0)
		return 0;
	else
		return 1;
}


void remover (BOARD *tab, PATH *pedrascomidas){
	int i = 0;
	while (pedrascomidas[i].posXcomida != 0 && pedrascomidas[i].posYcomida != 0){
		tab[pedrascomidas[i].posYcomida * COL_MAX + pedrascomidas[i].posXcomida].tipo = 0;
		tab[pedrascomidas[i].posYcomida * COL_MAX + pedrascomidas[i].posXcomida].classe = 0;
		i++;
	}
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


			if (tab[POS].tipo > 0 && tab[POS].classe == 1){     //imprime as pedras e substitui 0 por espaços em branco
				printf ("%.1d ", tab[POS].tipo);
			} else if (tab[POS].tipo > 0 && tab[POS].classe == 2) {
				printf ("%d*", tab[POS].tipo);
			} else {
				printf("  ");
			}
		}
		if (linha == LIN_MAX+1)
			printf ("\n");
		else
			printf("  %d\n", linha+1);

	}  
}
