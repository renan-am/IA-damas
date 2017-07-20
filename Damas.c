#include <stdio.h>
#include <stdlib.h>
#include "module1.h"

#define COL_MAX 8
#define LIN_MAX 8

#define POS linha*COL_MAX+coluna

typedef struct {
	int tipo;
	int energia;
}	BOARD;

BOARD *tabuleiro;

int game = 1;

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


/* PODE DELETAR TUDO DENTRO DESSE COMENTÁRIO SE QUISER
int caminhoMax [1000][2];
int indCamMax = 0;

int caminhoCome (int c_origem, int l_origem, int c_alvo, int l_alvo, int caminho[1000][2], int indCam){
	BOARD *tabAux;
	tabAux = calloc (COL_MAX*LIN_MAX, sizeof(BOARD));

}

*/

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

int main (){
	tabuleiro = calloc (COL_MAX*LIN_MAX, sizeof(BOARD));
	posicionarpedras();
	
	int c_origem = 0, l_origem = 0, c_destino = 0, l_destino = 0;

	while (game == 1){

		system ("tput reset");
		imprimir();


	
			while (1 == 1){	// pede as coordenadas de ORIGEM da pedra a ser movida, em seguida checa se estao no intervalo correto e se essa coordenada representa o local de uma pedra
					while ( 1 == 1){
						printf ("Digite a coluna da pedra a ser movida: ");
						scanf ("%d", &c_origem);
						c_origem--;
						if (c_origem >= COL_MAX || c_origem < 0)
							printf ("Coluna invalida, tente novamente\n");
						else
							break;
					}

					while ( 1 == 1){
						printf ("Digite a linha da pedra a ser movida: ");
						scanf ("%d", &l_origem);
						l_origem--;
						if (l_origem >= COL_MAX || l_origem < 0)
							printf ("Linha invalida, tente novamente\n");
						else
							break;
					}

					if (tabuleiro[l_origem*COL_MAX+c_origem].tipo == 0)  // A coordenada indicada esta vazia
						printf ("Nao tem pedra em Coluna: %d, Linha: %d\nDigite uma posicao valida\n", c_origem+1, l_origem+1);
					else
						break;
			}
			while (1 == 1){	// pede as coordenadas de DESTINO da pedra a ser movida, em seguida checa se ja existe uma pedra nesse local
				while ( 1 == 1){
					printf ("Digite a coluna de destino: ");
					scanf ("%d", &c_destino);
					c_destino--;
					if (c_destino >= COL_MAX || c_destino < 0)
						printf ("Coluna invalida, tente novamente\n");
					else
						break;
				}

				while ( 1 == 1){
					printf ("Digite a linha de destino: ");
					scanf ("%d", &l_destino);
					l_destino--;
					if (l_destino >= COL_MAX || l_destino < 0)
						printf ("Coluna invalida, tente novamente\n");
					else
						break;
				}

				if (tabuleiro[l_destino*COL_MAX+c_destino].tipo != 0)  // A coordenada indicada esta ocupada, a pedra nao podera ser movida para ca
					printf ("Ja tem uma pedra en Coluna: %d, Linha: %d\nDigite uma posicao valida\n", c_origem+1, l_origem+1);
				else if ((l_destino+1)*(c_destino+1) % 2 != 0)
					printf ("Local de destino invalido. Digite uma posicao valida\n");
				else
					break;
			}

		mover (c_origem, l_origem, c_destino, l_destino);


	}
}
