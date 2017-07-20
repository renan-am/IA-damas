#include <stdio.h>
#include <stdlib.h>
#include "module.h"

#define COL_MAX 8
#define LIN_MAX 8

#define POS linha*COL_MAX+coluna

BOARD *tabuleiro;

int game = 1;

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
